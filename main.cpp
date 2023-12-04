#include <iostream>
#include <SDL2/SDL.h>

#include "Camera/TPCamera.h"
#include "Engine/Window/SDLWindow.h"
#include "Engine/Render/Render/VulkanRender.h"
#include "Engine/Asset/Mesh/Mesh.h"
#include "Input/InputHandler.h"

int main() {
    IRender* render = new VulkanRender();
    IWindow* window = new SDLWindow(800, 600, "shootEmUp", WindowType::Windowed, render);

    InputHandler inputHandler;
    InputMap mapForward("forwardKey", KeyCode::W);
    InputMap mapBackward("backwardKey", KeyCode::S);
    InputMap mapLeft("leftKey", KeyCode::A);
    InputMap mapRight("rightKey", KeyCode::D);
    InputMap mapUp("upKey", KeyCode::E);
    InputMap mapDown("downKey", KeyCode::Q);

    InputContext context;
    context.AddInputMap(&mapForward);
    context.AddInputMap(&mapBackward);
    context.AddInputMap(&mapLeft);
    context.AddInputMap(&mapRight);
    inputHandler.Subscribe(&context);

    VertexData vertexInfo;
    vertexInfo.position = vec4(1, 0, 10, 1);
    BaseVertexDescriptor baseVertex(vertexInfo);

    VertexData vertexInfo2;
    vertexInfo2.position = vec4(1, 1, 10, 1);
    BaseVertexDescriptor baseVertex2(vertexInfo2);

    VertexData vertexInfo3;
    vertexInfo3.position = vec4(0, 0, 10, 1);
    BaseVertexDescriptor baseVertex3(vertexInfo3);

    vector vertecies {
        baseVertex,
        baseVertex2,
        baseVertex3
    };

    map<ShaderType, IShader> shaders;
    std::string vertLocation("/Users/airat/Projects/shootEmUp/base.vert.spv");
    std::string name("main");
    IShader vertexBase(vertLocation, name);

    std::string fragLocation("/Users/airat/Projects/shootEmUp/base.frag.spv");
    IShader fragBase(fragLocation, name);

    shaders.emplace(ShaderType::Vertex, vertexBase);
    shaders.emplace(ShaderType::Fragment, fragBase);
    auto* material = new IMaterial(shaders, Opaque);
    TPCamera camera(10.0f);
    camera.SetPerspective(90, 1.66f, 0.1, 10000);
    BaseBuffer uniformBuffer(BufferUsageFlag::UniformBuffer, BufferSharingMode::Exclusive, &camera.GetCameraObject(), BufferStageFlag::Vertex, 0);

    auto mesh = new Mesh<BaseVertexDescriptor, VertexData>(vertecies, material);
    mesh->Material()->AddBuffer(&uniformBuffer);

    render->AddMesh(mesh);

    bool isEnabled = true;
    chrono::time_point<chrono::steady_clock> start;
    while (isEnabled)
    {
       std::chrono::duration<double, std::milli> deltaTime = std::chrono::duration<double, std::milli>(
            std::chrono::steady_clock::now() - start
        );
        start = std::chrono::steady_clock::now();

        printf("%f\n", deltaTime.count());

        window->Update();
        inputHandler.Update(deltaTime.count());
        render->DrawFrame();
        if(mapBackward.State() == InputMapState::KeyDown && mapForward.State() == InputMapState::KeyDown)
            isEnabled = false;

        vec3 delta(0);
        if(mapBackward.State() == InputMapState::Pressed)
        {
            delta += vec3(0.0f, 0.0f, 0.1f);
        }
        if(mapForward.State() == InputMapState::Pressed)
        {
            delta += vec3(0.0f, 0.0f, -0.1f);
        }
        if(mapLeft.State() == InputMapState::Pressed)
        {
            delta += vec3(0.1f, 0.0f, 0.0f);
        }
        if(mapRight.State() == InputMapState::Pressed)
        {
            delta += vec3(-0.1f, 0.0f, 0.0f);
        }
        if(mapUp.State() == InputMapState::Pressed)
        {
            delta += vec3(0.0f, 0.1f, 0.0f);
        }
        if(mapDown.State() == InputMapState::Pressed)
        {
            delta += vec3(0.0f, -0.1f, 0.0f);
        }

        camera.Move(delta);

    }
    return 0;
}
