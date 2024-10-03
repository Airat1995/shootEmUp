#pragma once

#include <queue>

#include "InputContext.h"
#include "Common/System/UpdatableSystem.h"
#include "InputMap.h"

namespace Engine::Input
{
    class InputHandler : Common::System::UpdatableSystem {
    public:

        void Update(double deltaTime) override;

        void Subscribe(InputContext *inputMap);

        void UnsubscribeLast();

        void UnsubscribeAll();

    private:

        void ClearAllInputs(InputContext* inputContext);

        std::queue<InputContext *> _allInputMaps;
        InputContext *_activeInput = nullptr;
        double accumulator = 0.0;
        
        //minimum time should be left before next update
        static constexpr double updateFrameRate = 4.0f;
    };
}
