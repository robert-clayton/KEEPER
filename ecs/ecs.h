#pragma once

#include <bitset>
#include <queue>
#include <assert.h>
#include <set>
#include <memory>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "../vector2d.h"

using Entity = std::uint_fast32_t;
const Entity MAX_ENTITIES = 1000000;
using ComponentType = std::uint_fast8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

struct Transform
{
    Vector2D position;
    Vector2D scale;
};

class EntityManager
{
public:
    EntityManager()
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            availableEntities.push(entity);
        }
    }

    Entity CreateEntity()
    {
        assert(livingEntityCount < MAX_ENTITIES && "Too many entities exist.");
        Entity id = availableEntities.front();
        availableEntities.pop();
        ++livingEntityCount;
        return id;
    }

    void DestroyEntity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        signatures[entity].reset();
        availableEntities.push(entity);
        --livingEntityCount;
    }

    void SetSignature(Entity entity, Signature signature)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        signatures[entity] = signature;
    }

    Signature GetSignature(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        return signatures[entity];
    }
private:
    std::queue<Entity> availableEntities{};
    std::array<Signature, MAX_ENTITIES> signatures{};
    std::uint_fast32_t livingEntityCount{};
};

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
    void InsertData(Entity entity, T component)
    {
        assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to the same entity more than once.");
        // Put new entry at end and update the maps
        std::size_t newIndex = size;
        entityToIndexMap[entity] = newIndex;
        indexToEntityMap[newIndex] = entity;
        componentArray[newIndex] = component;
        ++size;
    }

    void RemoveData(Entity entity)
    {
        assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non-existent component.");
        // Copy element at end into deleted element's place to maintain density
        std::size_t indexOfRemovedEntity = entityToIndexMap[entity];
        std::size_t indexOfLastElement = size - 1;
        componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];
        // Update map to point to moved spot
        Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
        entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        entityToIndexMap.erase(entity);
        indexToEntityMap.erase(indexOfLastElement);

        --size;
    }

    T& GetData(Entity entity)
    {
        assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");
        // Return a reference to the entity's component
        return componentArray[entityToIndexMap[entity]];
    }

    void EntityDestroyed(Entity entity) override
    {
        // Remove entity components if it existed
        if (entityToIndexMap.find(entity) != entityToIndexMap.end())
        {
            RemoveData(entity);
        }
    }
private:
    std::array<T, MAX_ENTITIES> componentArray;
    std::unordered_map<Entity, std::size_t> entityToIndexMap;
    std::unordered_map<size_t, Entity> indexToEntityMap;
    std::size_t size;
};

class ComponentManager
{
public:
    template<typename T>
    void RegisterComponent()
    {
        const char* typeName = typeid(T).name();
        assert(componentTypes.find(typeName) == componentTypes.end() && "Registering component type more than once.");

        // Add this component type to the component type map
        componentTypes.insert({typeName, nextComponentType});

        // Create a ComponentArray pointer and add it to the component arrays map
        componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

        // Increment the value so that the next component registered will be different
        ++nextComponentType;
    }

    template<typename T>
    ComponentType GetComponentType()
    {
        const char* typeName = typeid(T).name();

        assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

        // Return this component's type - used for creating signatures
        return componentTypes[typeName];
    }

    template<typename T>
    void AddComponent(Entity entity, T component)
    {
        // Add a component to the array for an entity
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template<typename T>
    void RemoveComponent(Entity entity)
    {
        // Remove a component from the array for an entity
        GetComponentArray<T>()->RemoveData(entity);
    }

    template<typename T>
    T& GetComponent(Entity entity)
    {
        // Get a reference to a component from the array for an entity
        return GetComponentArray<T>()->GetData(entity);
    }

    void EntityDestroyed(Entity entity)
    {
        // Notify each component array that an entity has been destroyed
        // If it has a component for that entity, it will remove it
        for (auto const& pair : componentArrays)
        {
            auto const& component = pair.second;
            component->EntityDestroyed(entity);
        }
    }



private:
    std::unordered_map<const char*, ComponentType> componentTypes;
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays;
    ComponentType nextComponentType{};

    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray()
    {
        const char* typeName = typeid(T).name();

        assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }
};

class System
{
public:
    std::set<Entity> entities;
};

class SystemManager
{
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        assert(systems.find(typeName) == systems.end() && "Registering system more than once.");

        // Create a pointer to the system and return it so it can be used externally
        auto system = std::make_shared<T>();
        systems.insert({typeName, system});
        return system;
    }

    template<typename T>
    void SetSignature(Signature signature)
    {
        const char* typeName = typeid(T).name();

        assert(systems.find(typeName) != systems.end() && "System used before registered.");

        // Set the signature for this system
        signatures.insert({typeName, signature});
    }

    void EntityDestroyed(Entity entity)
    {
        // Erase a destroyed entity from all system lists
        // entities is a set so no check needed
        for (auto const& pair : systems)
        {
            auto const& system = pair.second;
            system->entities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature)
    {
        // Notify each system that an entity's signature changed
        for (auto const& pair : systems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = signatures[type];

            // Entity signature matches system signature - insert into set
            if ((entitySignature & systemSignature) == systemSignature)
            {
                system->entities.insert(entity);
            }
            // Entity signature does not match system signature - erase from set
            else
            {
                system->entities.erase(entity);
            }
        }
    }

private:
    std::unordered_map<const char*, Signature> signatures{};
    std::unordered_map<const char*, std::shared_ptr<System>> systems{};
};

class Coordinator
{
public:
    void Init()
    {
        // Create pointers to each manager
        componentManager = make_unique<ComponentManager>();
        entityManager = make_unique<EntityManager>();
        systemManager = make_unique<SystemManager>();
    }

    Entity CreateEntity()
    {
        return entityManager->CreateEntity();
    }

    void DestroyEntity(Entity entity)
    {
        entityManager->DestroyEntity(entity);
        componentManager->EntityDestroyed(entity);
        systemManager->EntityDestroyed(entity);
    }
    // Component
    template<typename T>
    void RegisterComponent()
    {
        componentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component)
    {
        componentManager->AddComponent<T>(entity, component);

        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->GetComponentType<T>(), true);
        entityManager->SetSignature(entity, signature);
        systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void RemoveComponent(Entity entity)
    {
        componentManager->RemoveComponent<T>(entity);
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->GetComponentType<T>(), false);
        entityManager->SetSignature(entity, signature);
        systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& GetComponent(Entity entity)
    {
        return componentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType GetComponentType()
    {
        return componentManager->GetComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        return systemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature signature)
    {
        systemManager->SetSignature<T>(signature);
    }

    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

private:
    std::unique_ptr<ComponentManager> componentManager;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<SystemManager> systemManager;
};
