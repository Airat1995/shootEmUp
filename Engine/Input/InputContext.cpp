#include "InputContext.h"

namespace Engine::Input
{
    InputContext::InputContext()
    {
        _isActive = true;
        _currentInputMapCount = 0;
    }

    bool InputContext::IsActive() const noexcept { return _isActive; }

    void InputContext::Update(double deltaTime, const SDL_Event& event) noexcept
    {
        for (int index = 0; index < _currentInputMapCount; index++)
        {
            inputMaps[index]->Update(event);
        }
    }

    void InputContext::AddInputMap(IInputKeyboard *inputKeyboard)
    {
        inputMaps[_currentInputMapCount] = inputKeyboard;
        _currentInputMapCount++;
    }

    void InputContext::RemoveInputMap(IInputKeyboard *inputKeyboard)
    {
        size_t foundIndex = -1;
        for (size_t index = 0; index < _currentInputMapCount; ++index)
        {
            if (foundIndex == -1)
            {
                if (inputMaps[index]->IsIdSame(inputKeyboard))
                {
                    foundIndex = index;
                }
                continue;
            }
            inputMaps[index - 1] = inputMaps[index];
        }
    }

    InputMapState InputContext::GetState(KeyCode keycode)
    {

        for (size_t index = 0; index < _currentInputMapCount; ++index)
        {
            if (inputMaps[index]->IsCodeSame(keycode))
            {
                return inputMaps[index]->State();
            }
        }

        return InputMapState::NotPressed;
    }

    void InputContext::SetEnabled(const bool enabled) { _isActive = enabled; }
}