//
// Created by Айрат Насыров on 05.08.2024.
//

#include "World.h"

Engine::Physics::World::World::World(glm::vec3 min, glm::vec3 max, glm::vec3 cellSize) : min(min), max(max), cellSize(cellSize)
{
    float xSize = max.x - min.x;
    float ySize = max.y - min.y;
    float zSize = max.z - min.z;

    int xCount = xSize/cellSize.x;
    int yCount = ySize/cellSize.y;
    int zCount = zSize/cellSize.z;

    for (int xIndex = 0; xIndex < xCount; xIndex++)
    {
        for (int yIndex = 0; yIndex < yCount; yIndex++)
        {
            for (int zIndex = 0; zIndex < zCount; zIndex++)
            {
                glm::vec3 cellMin {min.x + (cellSize.x * (float)xIndex), min.y + (cellSize.y * (float)yIndex), min.z + (cellSize.z * (float)zIndex) };
                glm::vec3 cellMax {min.x + (cellSize.x * (float)xIndex) + cellSize.x, min.y + (cellSize.y * (float)yIndex) + cellSize.y, min.z + (cellSize.z * (float)zIndex) + cellSize.z };
                Cell cell {cellMin, cellMax};
                _cells.push_back(cell);
            }
        }
    }

    _threadsCount = std::thread::hardware_concurrency();
    if(_cells.size() < _threadsCount)
    {
        _threadsCount = _cells.size();
    }

    _countPerThreads = _cells.size() / _threadsCount;
}

Engine::Physics::World::World::~World()
{
    _colliders.clear();
    _collisionGraph.Clear();
}

void Engine::Physics::World::World::AddCollider(Engine::Physics::Collider::Collider *collider)
{
    _colliders.push_back(collider);
}

void Engine::Physics::World::World::Update(double deltaTime)
{
}

void Engine::Physics::World::World::ClearGraph()
{
    _collisionGraph.Clear();
    for (auto& cell : _cells)
    {
        cell.Clear();
    }
}
