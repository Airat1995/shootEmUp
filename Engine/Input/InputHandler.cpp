#include "InputHandler.h"
#include "SDL2/SDL_events.h"

void InputHandler::Update(double deltaTime)
{
    if(!_activeInput->IsActive() || _activeInput == nullptr)
    {
        return;
    }
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    for (size_t inputIndex = 0; inputIndex < _activeInput->_currentInputMapCount; ++inputIndex)
    {
        if(InputMap* keyMap = _activeInput->inputMaps[inputIndex]; keyboardState[static_cast<int>(keyMap->keyCode)])
        {
            if(keyMap->state != InputMapState::KeyDown)
            {
                keyMap->state = InputMapState::KeyDown;
            }
            else
            {
                keyMap->state = InputMapState::Pressed;
            }
        }
        else
        {
            if(keyMap->state == InputMapState::KeyDown || keyMap->state == InputMapState::Pressed)
            {
                keyMap->state = InputMapState::KeyUp;
            }
            else
            {
                keyMap->state = InputMapState::NotPressed;
            }
        }
    }
}

void InputHandler::Subscribe(InputContext *inputMap)
{
    _allInputMaps.push(inputMap);
    ClearAllInputs(_activeInput);
    _activeInput = inputMap;
}

void InputHandler::ClearAllInputs(InputContext* inputContext)
{
    if(inputContext == nullptr)
        return;
    for (size_t inputIndex = 0; inputIndex < inputContext->_currentInputMapCount; ++inputIndex)
        inputContext->inputMaps[inputIndex]->state = InputMapState::NotPressed;
}

void InputHandler::Unsubscribe()
{
    ClearAllInputs(_activeInput);
    _activeInput = _allInputMaps.front();
    _allInputMaps.pop();
}