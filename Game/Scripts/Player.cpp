
#include "Player.h"
#include "Common/Application/Application.h"

namespace Game::Scripts
{
    Player::Player(InputHandler &inputHandler, Camera &camera, IRender &render, Engine::Physics::World::World &world, MainMaterial* material) :
        _inputHandler(inputHandler), _camera(camera), _render(render), _world(world), moveDelta(vec3(0)), _mainMaterial(material)
    {

        _mesh = MainMesh::Parse("/Users/airat/Projects/shootEmUp/Game/Assets/Obj/cube.obj", _mainMaterial);
        _mesh->SetStatic(true);

        render.AddMesh(_mesh);

        _context = {};

        moveForwardInput = new InputSOCD("movementForward", KeyCode::W, KeyCode::S);
        moveLeftInput = new InputSOCD("movementLeft", KeyCode::D, KeyCode::A);
        moveUpInput = new InputSOCD("movementRight", KeyCode::Q, KeyCode::E);

        _context.AddInputMap(moveForwardInput);
        _context.AddInputMap(moveLeftInput);
        _context.AddInputMap(moveUpInput);

        exitGameInput = new InputMap("exit", KeyCode::ESCAPE);
        _context.AddInputMap(exitGameInput);
        inputHandler.Subscribe(&_context);
        _transform = new Transform();

        _boxCollider = new Engine::Physics::Collider::BoxCollider(*_transform, {-.5, -.5, -.5}, {.5, .5, .5});
        _sphereCollider = new Engine::Physics::Collider::SphereCollider(*_transform, 1);
    }

    void Player::Update(double deltaTime)
    {
        Entity::Update(deltaTime);

        moveDelta = glm::vec3(0);
        moveDelta = vec3(.1f * moveLeftInput->Value(), .1f * moveUpInput->Value(), .1f * moveForwardInput->Value());

        if(exitGameInput->State() == InputMapState::Pressed || exitGameInput->State() == InputMapState::KeyDown)
        {
            Engine::Common::Application::Application::GetInstance().SetReadyToExit(true);
        }
    }

    void Player::FixedUpdate(const double deltaTime)
    {
        Entity::FixedUpdate(deltaTime);
        _transform->AddPosition(moveDelta);
    }

    void Player::PrerenderUpdate(const double alpha)
    {
        Entity::PrerenderUpdate(alpha);
        vec3 renderPosition = _transform->GetInterpolatedPosition(alpha);
        _mesh->SetPosition(renderPosition);
    }
}
