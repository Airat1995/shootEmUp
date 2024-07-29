
#include "InputMap.h"

#include <iostream>

namespace Engine::Input
{
    InputMap::InputMap() : IInputKeyboard(0), state(InputMapState::Inactive), keyCode(KeyCode::UNKNOWN)
    {
    }

    InputMap::InputMap(std::string mapName, const KeyCode keyCode) :
        IInputKeyboard(++_idIndexer), state(InputMapState::Inactive), mapName(std::move(mapName)), keyCode(keyCode)
    {
    }

    bool InputMap::IsEnabled() const noexcept
    {
        return state != InputMapState::Inactive;
    }

    bool InputMap::IsCodeSame(KeyCode code) const noexcept
    {
        return keyCode == code;
    }

    InputMapState InputMap::State() const noexcept { return state; }

    void InputMap::Update(const SDL_Event &event)
    {
        if (keyCode != SDLScanCodeToKeyCode(event.key.keysym.scancode))
        {
            if(state == InputMapState::KeyUp)
                state = InputMapState::NotPressed;

            if(state == InputMapState::KeyDown)
                state = InputMapState::Pressed;
            return;
        }

        if (event.key.state == SDL_PRESSED)
        {
            if(state == InputMapState::KeyDown || event.key.repeat > 0)
                state = InputMapState::Pressed;
            else if(state != InputMapState::Pressed)
                state = InputMapState::KeyDown;
        }
        else if (event.key.state == SDL_RELEASED)
            if(state == InputMapState::KeyUp)
                state = InputMapState::NotPressed;
            else
                state = InputMapState::KeyUp;
    }

    InputMap &InputMap::operator=(InputMap otherMap)
    {
        std::swap(_id, otherMap._id);
        std::swap(mapName, otherMap.mapName);
        std::swap(keyCode, otherMap.keyCode);
        std::swap(state, otherMap.state);
        return *this;
    }

    bool InputMap::operator!=(const InputMap &e) const noexcept { return _id != e._id; }

    bool InputMap::operator==(const InputMap &e) const noexcept { return _id == e._id; }
}