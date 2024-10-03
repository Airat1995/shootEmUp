#pragma once

namespace Engine::Assets::Resource
{
    static constexpr float inf = std::numeric_limits<float>::infinity();
    using ResourceId = std::atomic_uint32_t;
    static constexpr ResourceId null = -1;
    static ResourceId base = -1;

    class IResource
    {
    public:
        IResource() : _id(base.fetch_add(1, std::memory_order_relaxed) + 1) {}

        IResource(const IResource& copy)
            : IResource()
        {
        }

        virtual IResource& operator=(const IResource& copy)
        {
            if (this == &copy)
                return *this;
            IResource temp(copy);
            return *this;
        }

        IResource(IResource&& move) noexcept
            : _id(move._id)
        {
        }

        virtual IResource& operator=(IResource&& move) noexcept
        {
            IResource temp(std::move(move));
            return temp;
        }

        uint32_t GetResourceId() const noexcept { return _id; }

    private:
        uint32_t _id;
    };
}