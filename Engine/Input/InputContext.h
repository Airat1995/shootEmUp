#pragma once
#include <cstdint>

#include "InputMap.h"

class InputContext
{
    friend class InputHandler;
private:
    static constexpr uint8_t MAX_INPUT_MAP_PER_CONTEXT = 254;

    static uint64_t _idIndexer;
    bool _isActive;
    int8_t _currentInputMapCount;

    void SetEnabled(bool enabled);

public:

    InputContext();

    [[nodiscard]] bool IsActive() const noexcept;

    void AddInputMap(InputMap* inputMap);
    void RemoveInputMap(uint64_t id);

    std::array<InputMap*, MAX_INPUT_MAP_PER_CONTEXT> inputMaps = {};
};
