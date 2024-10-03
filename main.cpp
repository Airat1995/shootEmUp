#define TINYOBJLOADER_IMPLEMENTATION

#include <cmath>

#include "Camera/Camera.h"
#include "Engine/Asset/Mesh/Mesh.h"
#include "Engine/Common/Application/Application.h"
#include "Engine/Component/Entity/Entity.h"
#include "Engine/Render/Render/VulkanRender.h"
#include "Engine/Window/SDLWindow.h"
#include "Engine/Physics/World/World.h"
#include "Game/Assets/Mesh/MainMaterial.h"
#include "Game/Assets/Mesh/MainMesh.h"
#include "Input/InputHandler.h"

#include "Game/Scripts/Player.h"

using namespace Engine::Shared::RenderAsset;

int main()
{
    Engine::Window::VulkanRender render{};
    Engine::Window::SDLWindow window{1920, 1080, "shootEmUp", Engine::Window::WindowType::Windowed, &render};
    Engine::Input::InputHandler inputHandler;
    Engine::Physics::World::World world {glm::vec3(-5, -5, -5), glm::vec3(5, 5, 5), glm::vec3(1,1,1)};

    std::vector<Engine::Component::Entity::Entity*> entities;

    Engine::Camera::Camera camera(1.0f);
    camera.SetPerspective(60, 1920.0f / 1080.0f, 0.1, 100);
    auto initialPos = glm::vec3(0.0f, 0.0f, -50.0f);
    camera.SetPosition(initialPos);

    auto* uniformBuffer = new Engine::Render::Buffer::BaseBuffer(BufferUsageFlag::UniformBuffer, BufferSharingMode::Exclusive, &camera.GetCameraObject(),
                                 BufferStageFlag::Vertex, 1);

    auto* mainMaterial = new Game::Scripts::MainMaterial();
    mainMaterial->AddBuffer(uniformBuffer);

     Engine::Component::Component::Transform boxTransform {};
     Engine::Physics::Collider::BoxCollider staticBox {boxTransform, glm::vec3(-.5, -.5,-.5), glm::vec3(.5, .5,.5) };
     boxTransform.SetPosition(glm::vec3(0,0, -3));

     world.AddCollider(&staticBox);

     for (int x = 0; x < 10; ++x) {
         for (int y = 0; y < 10; ++y) {
             for (int z = 0; z < 10; ++z) {
                 Game::Scripts::Player *player = new Game::Scripts::Player(inputHandler, camera, render, world, mainMaterial);
                 player->SetPosition(glm::vec3{-5 + x, -5 + y, -5 + z });

                 entities.push_back(player);
             }
         }
     }

    double time = 0.0;
    double targetFrameTime = 16.0f;
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    double updateDelta = 0.0;
    double accumulator = 0.0;

    unsigned long long previousFrame = -1;
    unsigned long long currentFrame = Engine::Common::Application::Application::GetInstance().GetCurrentFrame();

    while (! Engine::Common::Application::Application::GetInstance().IsReadyToExit())
    {
        Engine::Common::Application::Application::GetInstance().IncreaseFrame();
        auto newTime = std::chrono::steady_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(newTime - start).count();
        printf("Frame Time: %f\n", deltaTime);

        window.Update();
        inputHandler.Update(deltaTime);
        world.Update(deltaTime);

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

        world.ClearGraph();
    }
    return 0;
}
