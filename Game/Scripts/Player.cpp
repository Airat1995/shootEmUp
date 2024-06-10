
#include "Player.h"
#include "Common/Application/Application.h"

Player::Player(InputHandler& inputHandler, Camera& camera, VulkanRender& render) : _inputHandler(inputHandler), _camera(camera), _render(render) {


    BaseBuffer uniformBuffer(BufferUsageFlag::UniformBuffer, BufferSharingMode::Exclusive, &camera.GetCameraObject(),
                             BufferStageFlag::Vertex, 1);

    MainMaterial mainMaterial{};
    mainMaterial.AddBuffer(&uniformBuffer);

    _mesh = MainMesh::Parse("/Users/airat/Projects/shootEmUp/Game/Assets/Obj/monkey.obj", &mainMaterial);

    render.AddMesh(_mesh);

    _context = {};
    inputHandler.Subscribe(&_context);

    _currentState.position = vec3(0.0);
    _currentState.scale = vec3(0.0);
    _previousState  = _currentState;
}

void Player::Update(double deltaTime) {
    Entity::Update(deltaTime);

    moveDelta = glm::vec3(0);
    if (_context.GetState(KeyCode::W) == InputMapState::Pressed)
        moveDelta = vec3(0.0f, 0.0f, .1f);
    if (_context.GetState(KeyCode::S) == InputMapState::Pressed)
        moveDelta = vec3(0.0f, 0.0f, -.1f);

    if(_context.GetState(KeyCode::ESCAPE) == InputMapState::Pressed)
    {
        Application::GetInstance().SetReadyToExit(true);
    }
}

void Player::FixedUpdate(double deltaTime) {
    Entity::FixedUpdate(deltaTime);
    _previousState.position = _currentState.position;
    _currentState.position += moveDelta;
}

void Player::PrerenderUpdate(double alpha) {
    Entity::PrerenderUpdate(alpha);
    vec3 renderPosition = _currentState.position * static_cast<float>(alpha) + _previousState.position * static_cast<float>(1 - alpha);
    _mesh->SetPosition(renderPosition);
}