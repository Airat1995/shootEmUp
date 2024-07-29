#pragma once
#include "Render/Render/IRender.h"
#include <string>

namespace Engine::Window
{
    using namespace std;
    using namespace Engine::Render::Render;

    enum class WindowType;

    class IWindow
    {
    public:
        explicit IWindow(int width, int height, string name, WindowType windowType, IRender* render);

        virtual ~IWindow() = default;

        virtual void SetWidth(int width);

        virtual void SetHeight(int height);

        virtual void SetName(string name);

        virtual void Update() = 0;

    protected:
        int _width;
        int _height;
        string _name;
        WindowType _windowType;

    private:
        IRender* _renderSystem;

        const int MinWidth = 720;
        const int MinHeight = 1280;
    };

    enum class WindowType
    {
        Fullscreen,
        Borderless,
        Windowed
    };
}
