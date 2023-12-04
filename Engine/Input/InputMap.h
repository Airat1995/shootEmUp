#pragma once

#include <string>
#include "KeyCode.h"
#include "InputState.h"

class InputMap
{
    friend class InputHandler;
private:
    static uint64_t _idIndexer;

    InputMapState state;

public:
    uint64_t id;
    std::string mapName;
    KeyCode keyCode;

    InputMap();

    InputMap(std::string mapName, KeyCode keyCode);

    // copy constructor
    InputMap(const InputMap &src) = default;

    // move constructor
    InputMap(InputMap &&src) noexcept = default;

    ~InputMap() = default;

    [[nodiscard]] bool IsEnabled() const;

    bool operator==(InputMap const& e) const noexcept;

    bool operator!=(InputMap const& e) const noexcept;

    [[nodiscard]] bool IsCodeSame(uint64_t code) const noexcept;

    [[nodiscard]] InputMapState State() const noexcept;

    InputMap& operator=(InputMap otherMap);
};