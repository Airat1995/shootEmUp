#define TINYOBJLOADER_IMPLEMENTATION

#include <cmath>

#include "Camera/Camera.h"
#include "Engine/Component/Entity/Entity.h"
#include "Engine/Window/SDLWindow.h"
#include "Engine/Render/Render/VulkanRender.h"
#include "Engine/Asset/Mesh/Mesh.h"
#include "Game/Assets/Mesh/MainMaterial.h"
#include "Input/InputHandler.h"
#include "Game/Assets/Mesh/MainMesh.h"
#include "Engine/Common/Application/Application.h"

#include "Game/Scripts/Player.h"


int main()
{
    VulkanRender render {};
    SDLWindow window {800, 600, "shootEmUp", WindowType::Windowed, &render};
    InputHandler inputHandler;

    vector<Entity*> entities;

    Camera camera(1.0f);
    camera.SetPerspective(60, 800.0f/600.0f, 0.1, 100);
    vec3 initialPos = glm::vec3(0.0f, 0.0f, -10.0f);
    camera.SetPosition(initialPos);


    Player player {inputHandler, camera, render};

    entities.push_back(&player);


    double time = 0.0;
    double targetFrameTime = 8.0f;
    chrono::time_point<chrono::steady_clock> start = std::chrono::steady_clock::now();
    double updateDelta = 0.0;
    double accumulator = 0.0;

    unsigned long long previousFrame = -1;
    unsigned long long currentFrame = Application::GetInstance().GetCurrentFrame();

    while (!Application::GetInstance().IsReadyToExit())
    {
        Application::GetInstance().IncreaseFrame();
        auto newTime = std::chrono::steady_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(
            newTime - start
            ).count();

        inputHandler.Update(deltaTime);
        window.Update();

        start = newTime;
        accumulator += deltaTime;

        for (auto entity : entities) 
        {
            entity->Update(deltaTime);
        }

        while (accumulator >= targetFrameTime)
        {
            for (auto entity : entities) 
            {
                entity->FixedUpdate(targetFrameTime);
            }
            time += targetFrameTime;
            accumulator -= targetFrameTime;
        }

        double alpha = accumulator / targetFrameTime;
        for (auto entity : entities) 
        {
            entity->PrerenderUpdate(alpha);
        }
        render.DrawFrame();

    }
    return 0;
}
