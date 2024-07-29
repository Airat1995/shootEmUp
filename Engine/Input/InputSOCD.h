#pragma once
#include <queue>
#include <string>

#include "IInputKeyboard.h"
#include "InputMap.h"

namespace Engine::Input
{
    class InputSOCD : public IInputKeyboard{
        friend class InputHandler;

        InputMapState _state;
        int8_t _value{};

        InputMap* _positive;
        InputMap* _negative;

        InputMap* _lastInput;
        InputMap* _currentInput;

    public:
        std::string mapName;
        KeyCode positiveKeyCode;
        KeyCode negativeKeyCode;

        InputSOCD();

        InputSOCD(std::string mapName, KeyCode positiveKeyCode, KeyCode negativeKeyCode);

        ~InputSOCD() override = default;

        [[nodiscard]] bool IsEnabled() const noexcept override;

        [[nodiscard]] bool IsCodeSame(KeyCode code) const noexcept override;

        [[nodiscard]] InputMapState State() const noexcept override;

        [[nodiscard]] int8_t Value() const noexcept;

        void Update(const SDL_Event &event) override;

        InputSOCD &operator=(InputSOCD otherMap);

        bool operator!=(const InputSOCD &e) const noexcept;

        bool operator==(const InputSOCD &e) const noexcept;
    };
}