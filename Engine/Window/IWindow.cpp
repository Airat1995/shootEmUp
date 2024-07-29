#include "IWindow.h"
#include <utility>

namespace Engine::Window
{
    IWindow::IWindow(int width, int height, string name, WindowType windowType, IRender* render)
    {
        IWindow::SetHeight(height);
        IWindow::SetWidth(width);
        _name = std::move(name);
        _renderSystem = render;
        _windowType = windowType;;
    }

    void IWindow::SetWidth(int width)
    {
        if(width == _width)
            return;
        if (width < MinWidth)
            width = MinWidth;
        _width = width;
    }

    void IWindow::SetHeight(int height)
    {
        if (height == _height)
            return;
        if (height < MinHeight)
            height = MinHeight;
        _height = height;

    }

    void IWindow::SetName(string name)
    {
        _name = std::move(name);
    }
}