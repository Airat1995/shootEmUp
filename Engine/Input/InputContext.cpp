#include "InputContext.h"

InputContext::InputContext()
{
    _isActive = true;
    _currentInputMapCount = 0;
}

bool InputContext::IsActive() const noexcept
{
    return _isActive;
}

void InputContext::AddInputMap(InputMap* inputMap)
{
    inputMaps[_currentInputMapCount] = inputMap;
    _currentInputMapCount++;
}

void InputContext::RemoveInputMap(const uint64_t id)
{
    size_t foundIndex = -1;
    for (size_t index = 0; index < _currentInputMapCount; ++index)
    {
        if(foundIndex == -1)
        {
            if(inputMaps[index]->IsCodeSame(id))
            {
                foundIndex = index;
            }
            continue;
        }
        inputMaps[index-1] = inputMaps[index];
    }
}

void InputContext::SetEnabled(const bool enabled)
{
    _isActive = enabled;
}