
#pragma once


#include "Camera/Camera.h"
#include "Component/Entity/Entity.h"
#include "Input/InputHandler.h"
#include "Render/Render/VulkanRender.h"

#include "../../Engine/Component/Component/State.h"
#include "../Assets/Mesh/MainMaterial.h"
#include "../Assets/Mesh/MainMesh.h"
#include "Component/Component/Transform.h"
#include "Physics/World/World.h"
#include "Physics/Colliders/BoxCollider.h"
#include "Physics/Colliders/SphereCollider.h"
#include "Input/InputSOCD.h"


namespace Game::Scripts
{
    using namespace Engine::Physics;
    using namespace Engine::Component::Entity;
    using namespace Engine::Input;
    using namespace Engine::Camera;
    using namespace Engine::Render::Render;
    using namespace Assets::Mesh;

    class Player : public Entity
    {
    public:
        Player(InputHandler &inputHandler, Camera &camera, Engine::Render::Render::IRender &render, Engine::Physics::World::World &world, MainMaterial* material);

        void Update(double deltaTime) override;

        void FixedUpdate(double deltaTime) override;

        void PrerenderUpdate(double alpha) override;

        inline void SetPosition(glm::vec3 position)
        {
            _transform->SetPosition(position);
        }

    protected:
        InputHandler &_inputHandler;
        IBuffer *uniformBuffer;
        Camera &_camera;
        IRender &_render;
        Engine::Physics::World::World &_world;
        InputContext _context;
        MainMesh *_mesh;
        MainMaterial *_mainMaterial;
        Transform *_transform;
        Collider::BoxCollider *_boxCollider;
        Collider::SphereCollider *_sphereCollider;
        glm::vec3 moveDelta;

        InputMap *exitGameInput;

        InputSOCD *moveForwardInput;
        InputSOCD *moveLeftInput;
        InputSOCD *moveUpInput;

        float _speed = 0.01f;
        int _meshCount = 0;
    };
} // namespace Game::Scripts
