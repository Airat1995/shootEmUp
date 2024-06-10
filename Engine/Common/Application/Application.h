
#pragma once
#include <SDL_events.h>

class Application {
public:

    static Application& GetInstance()
    {
        static Application instance;
        return instance;
    }

    inline bool IsReadyToExit() const noexcept {
        return _readyToExit;
    }

    inline void SetReadyToExit(bool exit) noexcept {
        _readyToExit = exit;
    }

    inline void IncreaseFrame() noexcept {
        _currentFrame++;
    }

    inline unsigned long long GetCurrentFrame() const noexcept {
        return _currentFrame;
    }
private:
    bool _readyToExit;
    unsigned long long _currentFrame = 0;
};
