#include "controllersystem.h"
#include "components.h"
#include "../game.h"
#include "../map.h"
#include <iostream>
#include <vector>
#include <mutex>

std::mutex mtx;

template<typename T>
std::vector<std::vector<T>> ChunkVectorToSize(const std::vector<T>& source, size_t chunkSize)
{
    std::vector<std::vector<T>> result;
    result.reserve((source.size() + chunkSize - 1) / chunkSize);

    auto start = source.begin();
    auto end = source.end();

    while (start != end) {
        auto next = std::distance(start, end) >= chunkSize
            ? start + chunkSize
            : end;

        result.emplace_back(start, next);
        start = next;
    }

    return result;
}

template<typename T>
std::vector<std::vector<T>> SplitVectorToNChunks(const std::vector<T>& vec, size_t n)
{
    std::vector<std::vector<T>> outVec;

    size_t length = vec.size() / n;
    size_t remain = vec.size() % n;

    size_t begin = 0;
    size_t end = 0;

    for (size_t i = 0; i < std::min(n, vec.size()); ++i)
    {
        end += (remain > 0) ? (length + !!(remain--)) : length;
        outVec.push_back(std::vector<T>(vec.begin() + begin, vec.begin() + end));
        begin = end;
    }
    return outVec;
}

void SController::Update(const float deltaSeconds)
{
    const auto& chunkedEntities = SplitVectorToNChunks(
        std::vector<Entity>{entities.begin(), entities.end()}, 
        std::thread::hardware_concurrency()
    );
    for (const auto& entityVec : chunkedEntities)
        futures.push_back(Game::threadPool.enqueue([&] { DoMovement(entityVec, deltaSeconds); }));
    for (auto& fut : futures)
        fut.get();
    futures.clear();
}

const void SController::DoMovement(const std::vector<Entity>& entityVec, const float deltaSeconds)
{
    for (const auto& entity : entityVec)
    {
        auto& transform = coordinator.GetComponent<CTransform>(entity);
        auto& aiController = coordinator.GetComponent<CAIController>(entity);
        auto& stats = coordinator.GetComponent<CStats>(entity);

        if (!aiController.bIsMoving)
        {
            // Get new path if needed
            if (aiController.movePath.empty())
                if (!Game::map->FindPath(aiController.movePath, transform.tile, Game::map->GetRandomTile()))
                    return;

            // Get next tile in path and start moving to it
            mtx.lock();
            coordinator.GetComponent<CTile>(transform.tile).entities.erase(entity);
            transform.tile = aiController.movePath.front();
            aiController.movePath.erase(aiController.movePath.begin());
            coordinator.GetComponent<CTile>(transform.tile).entities.emplace(entity);
            mtx.unlock();
            aiController.moveDirection = transform.position.DirectionTo(
                coordinator.GetComponent<CTransform>(transform.tile).position);

            aiController.bIsMoving = true;
        }
        if (transform.position.DistanceTo(coordinator.GetComponent<CTransform>(transform.tile).position) < stats.speed * deltaSeconds)
        {
            aiController.bIsMoving = false;
            aiController.moveDirection.Zero();
            transform.position = coordinator.GetComponent<CTransform>(transform.tile).position;
        }
        else
        {
            transform.position += aiController.moveDirection * stats.speed * deltaSeconds;
            transform.bIsDirty = true;
        }
    }
}

void SController::DoMovement(const Entity entity, const float deltaSeconds)
{
    auto& transform = coordinator.GetComponent<CTransform>(entity);
    auto& aiController = coordinator.GetComponent<CAIController>(entity);
    auto& stats = coordinator.GetComponent<CStats>(entity);

    if (!aiController.bIsMoving)
    {
        // Get new path if needed
        if (aiController.movePath.empty())
            if (!Game::map->FindPath(aiController.movePath, transform.tile, Game::map->GetRandomTile()))
                return;

        // Get next tile in path and start moving to it
        mtx.lock();
        coordinator.GetComponent<CTile>(transform.tile).entities.erase(entity);
        transform.tile = aiController.movePath.front();
        aiController.movePath.erase(aiController.movePath.begin());
        coordinator.GetComponent<CTile>(transform.tile).entities.emplace(entity);
        mtx.unlock();
        aiController.moveDirection = transform.position.DirectionTo(
            coordinator.GetComponent<CTransform>(transform.tile).position);

        aiController.bIsMoving = true;
    }
    if (transform.position.DistanceTo(coordinator.GetComponent<CTransform>(transform.tile).position) < stats.speed * deltaSeconds)
    {
        aiController.bIsMoving = false;
        aiController.moveDirection.Zero();
        transform.position = coordinator.GetComponent<CTransform>(transform.tile).position;
    }
    else
    {
        transform.position += aiController.moveDirection * stats.speed * deltaSeconds;
        transform.bIsDirty = true;
    }
}
