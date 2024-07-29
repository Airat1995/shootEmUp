#pragma once
namespace Engine::Render::Buffer
{
    enum RenderQueue {
        PreOpaque = 0,
        Opaque = 1,
        Transparent = 2,
        Overlay = 3
    };
}