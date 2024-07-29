#pragma once

#include <cstdint>
namespace Engine::Input
{
    enum class InputMapState : uint8_t
    {
        Inactive,
        NotPressed,
        KeyDown,
        Pressed,
        KeyUp
    };
}