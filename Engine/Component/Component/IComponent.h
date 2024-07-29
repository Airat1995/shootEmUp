#pragma once

namespace Engine::Component::Component
{
    class IComponent {
    public:

        IComponent() {
            AssignId();
        }

        IComponent(IComponent &&moveObj) noexcept {
            std::swap(_enabled, moveObj._enabled);
            std::swap(_id, moveObj._id);
        }

        IComponent(const IComponent &copy) {
            AssignId();
            _enabled = copy._enabled;
        }

        IComponent &operator=(const IComponent &copy) {
            AssignId();
            _enabled = copy._enabled;
            return *this;
        }

        IComponent &operator=(IComponent &&moveObj) noexcept {
            std::swap(_enabled, moveObj._enabled);
            std::swap(_id, moveObj._id);
            return *this;
        }

        virtual ~IComponent() = default;

        [[nodiscard]] inline long long GetId() const noexcept {
            return _id;
        }

        virtual void SetEnabled(bool enabled) {
            _enabled = enabled;
        }

        [[nodiscard]] bool GetEnabled() const noexcept {
            return _enabled;
        }

        virtual void Update(double deltaTime) {

        }

        virtual void FixedUpdate(double deltaTime) {
        }

        virtual void Destroy() {
        }

    private:

        void AssignId() {
            static long long id = 0;
            _id = id++;
        }

        long long _id = 0;

        bool _enabled = false;
    };
}