#pragma once

#include <SDL_events.h>
#include <string>

#include "IInputKeyboard.h"
#include "InputState.h"
#include "KeyCode.h"

namespace Engine::Input
{
    class InputMap : public IInputKeyboard
    {
        friend class InputHandler;

        InputMapState state;

    public:
        std::string mapName;
        KeyCode keyCode;

        InputMap();

        InputMap(std::string mapName, KeyCode keyCode);

        // copy constructor
        InputMap(const InputMap &src) = default;

        // move constructor
        InputMap(InputMap &&src) noexcept = default;

        ~InputMap() override = default;

        [[nodiscard]] bool IsEnabled() const noexcept override;

        [[nodiscard]] bool IsCodeSame(KeyCode code) const noexcept override;

        [[nodiscard]] InputMapState State() const noexcept override;

        void Update(const SDL_Event &event) override;

        bool operator==(InputMap const &e) const noexcept;

        bool operator!=(InputMap const &e) const noexcept;

        InputMap &operator=(InputMap otherMap);
    };
}