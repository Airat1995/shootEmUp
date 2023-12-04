
#include "InputMap.h"

uint64_t InputMap::_idIndexer = 0;

InputMap::InputMap(): state(InputMapState::Inactive), id(0), keyCode(KeyCode::UNKNOWN)
{
}

InputMap::InputMap(std::string mapName, const KeyCode keyCode) :
        id(++_idIndexer), state(InputMapState::Inactive), mapName(std::move(mapName)), keyCode(keyCode)
{
}

bool InputMap::IsEnabled() const
{
    return state != InputMapState::Inactive;
}

bool InputMap::IsCodeSame(const uint64_t code) const noexcept
{
    return static_cast<uint64_t>(keyCode) == code;
}

InputMapState InputMap::State() const noexcept
{
    return state;
}

InputMap& InputMap::operator=(InputMap otherMap)
{
    std::swap(id, otherMap.id);
    std::swap(mapName, otherMap.mapName);
    std::swap(keyCode, otherMap.keyCode);
    return *this;
}

bool InputMap::operator!=(const InputMap &e) const noexcept
{
    return id != e.id;
}

bool InputMap::operator==(const InputMap &e) const noexcept
{
    return id == e.id;
}
