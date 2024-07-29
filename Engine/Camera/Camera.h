#pragma once

#include <utility>
#include "ICamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine::Camera
{
    class Camera : public ICamera<CameraObject> {
    public:
        Camera(float cameraSpeed) {
            _speed = cameraSpeed;
        }

        Camera(const Camera &other)
                : ICamera(other) {
        }

        Camera(Camera &&other) noexcept
                : ICamera(std::move(other)) {
        }

        ~Camera() {
        }

        Camera &operator=(const Camera &other) {
            if (this == &other)
                return *this;
            ICamera::operator=(other);
            return *this;
        }

        Camera &operator=(Camera &&other) noexcept {
            if (this == &other)
                return *this;
            ICamera::operator=(std::move(other));
            return *this;
        }

        void SetPosition(glm::vec3 &position) override {
            _position = position;
            UpdateViewMatrix();
        }

        void SetRotation(glm::vec3 &rotation) override {
            _rotation = rotation;
            UpdateViewMatrix();
        }

        void Rotate(glm::vec3 &delta) override {
            _rotation += delta;
            UpdateViewMatrix();
        }

        void Move(glm::vec3 &delta) override {
            _position += delta * _speed;
            UpdateViewMatrix();
        }

        void SetPerspective(float fov, float aspect, float zNear, float zFar) override {
            _fov = fov;
            _aspect = aspect;
            _zNear = zNear;
            _zFar = zFar;
            UpdateProjectionMatrix();
        }

        void SetAspect(float aspect) override {
            _aspect = aspect;
            UpdateProjectionMatrix();
        }

        glm::mat4 GetViewModel() {
            glm::mat4 viewModel = _cameraObject._view * _cameraObject._model;
            return viewModel;
        }

        glm::mat4 GetView() {
            return _cameraObject._view;
        }

        float GetNear() override {
            return _zNear;
        }

        float GetFar() override {
            return _zFar;
        }

        glm::vec3 GetPosition() override {
            return _position;
        }

        CameraObject &GetCameraObject() override {
            return _cameraObject;
        }

    private:

        CameraObject _cameraObject;

        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec4 _viewPos;

        float _fov;
        float _zNear;
        float _zFar;
        float _aspect;
        float _speed;

        void UpdateViewMatrix() {
            glm::mat4 currentMatrix = _cameraObject._view;

            glm::mat4 rotM = glm::mat4(1.0f);
            glm::mat4 transM;

            rotM = glm::rotate(rotM, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            rotM = glm::rotate(rotM, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            rotM = glm::rotate(rotM, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

            glm::vec3 translation = _position;
            transM = glm::translate(glm::mat4(1.0f), translation);

            _cameraObject._view = rotM * transM;

            _viewPos = glm::vec4(_position, 0.0f) * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);
        }

        void UpdateProjectionMatrix() {
            _cameraObject._proj = glm::perspective(glm::radians(_fov), _aspect, _zNear, _zFar);
        }
    };
}