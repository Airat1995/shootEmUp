#include "InputHandler.h"
#include "SDL2/SDL_events.h"

namespace Engine::Input
{
    void InputHandler::Update(double deltaTime) {
        accumulator += deltaTime;
        if(accumulator < updateFrameRate)
            return;
        
        accumulator = 0.0;
        SDL_Event event;
        SDL_PollEvent(&event);

        if (_activeInput == nullptr || !_activeInput->IsActive())
            return;

        _activeInput->Update(deltaTime, event);
    }

    void InputHandler::Subscribe(InputContext *inputMap) {
        _allInputMaps.push(inputMap);
        _activeInput = inputMap;
    }

    void InputHandler::UnsubscribeLast() {
        ClearAllInputs(_activeInput);
        _allInputMaps.pop();
        _activeInput = _allInputMaps.front();
    }

    void InputHandler::UnsubscribeAll() {
        for (int inputIndex = 0; inputIndex < _allInputMaps.size(); ++inputIndex) {
            ClearAllInputs(_activeInput);
            _allInputMaps.pop();
        }
        _activeInput = nullptr;
    }

    void InputHandler::ClearAllInputs(InputContext* inputContext) {
        // for (size_t inputIndex = 0; inputIndex < inputContext->_currentInputMapCount; ++inputIndex)
        //     inputContext->inputMaps[inputIndex].state = InputMapState::NotPressed;
    }
}
