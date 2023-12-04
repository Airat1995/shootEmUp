#pragma once

#include <cstdint>

enum class InputMapState : uint8_t
{
    Inactive,
    NotPressed,
    KeyDown,
    Pressed,
    KeyUp
};