#pragma once

#include <queue>

#include "InputContext.h"
#include "Common/System/UpdatableSystem.h"
#include "InputMap.h"

class InputHandler : UpdatableSystem {
private:

    std::queue<InputContext*> _allInputMaps;
    InputContext* _activeInput = nullptr;
public:

    void Update(double deltaTime) override;

    void Subscribe(InputContext* inputMap);

    static void ClearAllInputs(InputContext* inputContext);

    void Unsubscribe();
};

