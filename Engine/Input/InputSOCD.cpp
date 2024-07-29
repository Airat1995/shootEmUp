//
// Created by Айрат Насыров on 17.06.2024.
//

#include "InputSOCD.h"

namespace Engine::Input
{
    InputSOCD::InputSOCD() :
        IInputKeyboard(0), _state(InputMapState::Inactive), _positive(nullptr), _negative(nullptr), _lastInput(nullptr),
        _currentInput(nullptr), positiveKeyCode(KeyCode::UNKNOWN), negativeKeyCode(KeyCode::UNKNOWN)
    {
    }

    InputSOCD::InputSOCD(std::string mapName, KeyCode positiveKeyCode, KeyCode negativeKeyCode) :
        IInputKeyboard(++_idIndexer), _state(InputMapState::Inactive), _value(0), _lastInput(nullptr),
        _currentInput(nullptr), mapName(std::move(mapName)), positiveKeyCode(positiveKeyCode),
        negativeKeyCode(negativeKeyCode)
    {
        std::string positiveMapName = mapName + "positive";
        std::string negativeMapName = mapName + "negative";
        _positive = new InputMap(positiveMapName, positiveKeyCode);
        _negative = new InputMap(negativeMapName, negativeKeyCode);
    }

    void InputSOCD::Update(const SDL_Event &event)
    {
        _positive->Update(event);
        _negative->Update(event);

        if(_positive->State() == InputMapState::KeyDown && _currentInput != _positive)
        {
            _lastInput = _currentInput;
            _currentInput = _positive;
        }

        if(_negative->State() == InputMapState::KeyDown && _currentInput != _negative)
        {
            _lastInput = _currentInput;
            _currentInput = _negative;
        }

        if(_currentInput != nullptr)
        {
            if(_currentInput->State() == InputMapState::KeyUp || _currentInput->State() == InputMapState::NotPressed)
            {
                if(_lastInput != nullptr && (_lastInput->State() != InputMapState::KeyUp && _lastInput->State() != InputMapState::NotPressed))
                {
                    _currentInput = _lastInput;
                    _lastInput = nullptr;
                }
                else
                {
                    _currentInput = nullptr;
                    _lastInput = nullptr;
                }
            }
        }

        if(_currentInput == _positive)
        {
            _value = 1;
        }
        else if(_currentInput == _negative)
        {
            _value = -1;
        }
        else
        {
            _value = 0;
        }
    }

    bool InputSOCD::IsEnabled() const noexcept
    {
        return _state != InputMapState::Inactive;
    }

    bool InputSOCD::IsCodeSame(const KeyCode code) const noexcept
    {
        return positiveKeyCode == code || negativeKeyCode == code;
    }

    InputMapState InputSOCD::State() const noexcept
    {
        return _state; }

    int8_t InputSOCD::Value() const noexcept
    {
        return _value;
    }

    InputSOCD &InputSOCD::operator=(InputSOCD otherMap)
    {
        std::swap(_id, otherMap._id);
        std::swap(mapName, otherMap.mapName);
        std::swap(_state, otherMap._state);
        std::swap(_value, otherMap._value);
        std::swap(positiveKeyCode, otherMap.positiveKeyCode);
        std::swap(negativeKeyCode, otherMap.negativeKeyCode);
        return *this;
    }

    bool InputSOCD::operator!=(const InputSOCD &e) const noexcept { return _id != e._id; }

    bool InputSOCD::operator==(const InputSOCD &e) const noexcept { return _id == e._id; }
}