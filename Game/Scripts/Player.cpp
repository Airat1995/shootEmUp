
#include "Player.h"
#include "Common/Application/Application.h"

namespace Game::Scripts
{
    Player::Player(InputHandler &inputHandler, Camera &camera, IRender &render) :
        _inputHandler(inputHandler), _camera(camera), _render(render), moveDelta(vec3(0))
    {
        uniformBuffer = new BaseBuffer(BufferUsageFlag::UniformBuffer, BufferSharingMode::Exclusive, &camera.GetCameraObject(),
                                 BufferStageFlag::Vertex, 1);

        _mainMaterial = new MainMaterial();
        _mainMaterial->AddBuffer(uniformBuffer);

        _mesh = MainMesh::Parse("/Users/airat/Projects/shootEmUp/Game/Assets/Obj/monkey.obj", _mainMaterial);

        render.AddMesh(_mesh);

        _context = {};
        forwardInput = new InputMap("forward", KeyCode::W);
        backwardInput = new InputMap("backward", KeyCode::S);
        removeInput = new InputMap("remove", KeyCode::D);
        addInput = new InputMap("add", KeyCode::A);

        moveInput = new InputSOCD("movement", KeyCode::W, KeyCode::S);
        _context.AddInputMap(moveInput);
        _context.AddInputMap(removeInput);
        _context.AddInputMap(addInput);

        exitGameInput = new InputMap("exit", KeyCode::ESCAPE);
        _context.AddInputMap(exitGameInput);
        inputHandler.Subscribe(&_context);
        _transform = new Transform();
    }

    void Player::Update(double deltaTime)
    {
        Entity::Update(deltaTime);

        moveDelta = glm::vec3(0);
        moveDelta = vec3(.0f, .0f, .1f * moveInput->Value());

        if(exitGameInput->State() == InputMapState::Pressed || exitGameInput->State() == InputMapState::KeyDown)
        {
            Engine::Common::Application::Application::GetInstance().SetReadyToExit(true);
        }

        if(removeInput->State() == InputMapState::Pressed)
        {
            _render.RemoveMesh(_mesh);
        }

        if(addInput->State() == InputMapState::Pressed)
        {
            _render.AddMesh(_mesh);
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