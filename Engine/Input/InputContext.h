#pragma once

#include <array>
#include <cstdint>

#include "InputMap.h"

namespace
{
    static constexpr uint8_t MAX_INPUT_MAP_PER_CONTEXT = 254;
}

namespace Engine::Input
{
    class InputContext
    {
        friend class InputHandler;

    public:
        InputContext();

        [[nodiscard]] bool IsActive() const noexcept;

        void Update(double deltaTime, const SDL_Event& event) noexcept;

        void AddInputMap(IInputKeyboard *inputKeyboard);

        void RemoveInputMap(IInputKeyboard *inputKeyboard);

        void SetEnabled(bool enabled);

        InputMapState GetState(KeyCode keycode);

        std::array<IInputKeyboard*, MAX_INPUT_MAP_PER_CONTEXT> inputMaps = {};

    private:
        bool _isActive;
        int8_t _currentInputMapCount;
    };
}