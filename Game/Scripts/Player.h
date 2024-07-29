
#pragma once


#include "Camera/Camera.h"
#include "Component/Entity/Entity.h"
#include "Input/InputHandler.h"
#include "Render/Render/VulkanRender.h"

#include "../../Engine/Component/Component/State.h"
#include "../Assets/Mesh/MainMaterial.h"
#include "../Assets/Mesh/MainMesh.h"
#include "Component/Component/Transform.h"
#include "Input/InputSOCD.h"


namespace Game::Scripts
{
    using namespace Engine::Component::Entity;
    using namespace Engine::Input;
    using namespace Engine::Camera;
    using namespace Engine::Render::Render;
    using namespace Assets::Mesh;

    class Player : public Entity
    {
    public:
        Player(InputHandler &inputHandler, Camera &camera, Engine::Render::Render::IRender &render);

        void Update(double deltaTime) override;

        void FixedUpdate(double deltaTime) override;

        void PrerenderUpdate(double alpha) override;

    protected:
        InputHandler &_inputHandler;
        IBuffer *uniformBuffer;
        Camera &_camera;
        IRender &_render;
        InputContext _context;
        MainMesh *_mesh;
        MainMaterial *_mainMaterial;
        Transform *_transform;
        glm::vec3 moveDelta;

        InputMap *forwardInput;
        InputMap *backwardInput;
        InputMap *removeInput;
        InputMap *addInput;
        InputMap *exitGameInput;

        InputSOCD *moveInput;

        float _speed = 0.01f;
    };
} // namespace Game::Scripts
