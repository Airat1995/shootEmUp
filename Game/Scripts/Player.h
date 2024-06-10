
#pragma once


#include "Component/Entity/Entity.h"
#include "Input/InputHandler.h"
#include "Camera/Camera.h"
#include "Render/Render/VulkanRender.h"

#include "../Assets/Mesh/MainMesh.h"
#include "../Assets/Mesh/MainMaterial.h"
#include "Component/Entity/State.h"


class Player : public Entity {
public:
    Player(InputHandler& inputHandler, Camera& camera, VulkanRender& render);

    void Update(double deltaTime) override;

    void FixedUpdate(double deltaTime) override;

    void PrerenderUpdate(double alpha) override;

protected:

    InputHandler& _inputHandler;
    Camera& _camera;
    VulkanRender& _render;
    InputContext _context;
    MainMesh* _mesh;
    glm::vec3 moveDelta;

    float _speed = 0.01f;

    State _previousState;
    State _currentState;

};
