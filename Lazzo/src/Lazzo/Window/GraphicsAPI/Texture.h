#pragma once
#include <memory>
#include <string>

namespace Lazzo::Graphics {
    class Texture {
    public:
        virtual ~Texture() = default;
        virtual void Bind(unsigned int slot = 0) const = 0;
        virtual void UnBind() const = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;
        virtual const std::string& GetPath() const = 0;
        // True when the underlying file decoded successfully. False when the
        // fallback pixel was uploaded because loading failed.
        virtual bool IsValid() const = 0;

        // OpenGL is the only backend currently supported by this factory.
        static std::unique_ptr<Texture> Create(const std::string& path);
        static std::unique_ptr<Texture> CreateFromMemory(const void* data, int dataSize, const std::string& debugName = "");
    };
}
