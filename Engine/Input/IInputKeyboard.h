#pragma once
#include <SDL_events.h>


#include "InputState.h"
#include "KeyCode.h"

namespace Engine::Input
{
    class IInputKeyboard
    {
    protected:
        static uint64_t _idIndexer;
        uint64_t _id;

    public:

        explicit IInputKeyboard(uint64_t id)
        {
            _id = id;
        }

        virtual ~IInputKeyboard() = default;

        [[nodiscard]] virtual bool IsEnabled() const noexcept = 0;

        [[nodiscard]] virtual bool IsCodeSame(KeyCode code) const noexcept = 0;

        [[nodiscard]] virtual InputMapState State() const noexcept = 0;

        virtual void Update(const SDL_Event &event) = 0;

        virtual bool IsIdSame(IInputKeyboard * inputKeyboard)
        {
            return _id == inputKeyboard->_id;
        }
    };
}