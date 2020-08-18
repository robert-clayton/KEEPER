# KEEPER

### An Undertaking of a Turn-Based Combat World Simulation

# TODO
- [x] Worker threads that await jobs in the ECS
    - [ ] Fix race condition relating to coordinator entities
- [ ] Add awareness of nearby entities to entities with CAIController
- [ ] Boid alg and some sort of CFlock struct to store relevant data
- [ ] Create node system to chunkify world map for A* pathfinding

## v0.0.2 - A* Pathfinding
![A* took way too long](./docs/res/0.0.2.gif)

## v0.0.1 - Basic ECS and Tiles
![Early version of KEEPER](./docs/res/0.0.1.gif)
