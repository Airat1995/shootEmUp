#pragma once

class UpdatableSystem {
public:
    virtual ~UpdatableSystem() = default;

    virtual void Update(double deltaTime) = 0;
};