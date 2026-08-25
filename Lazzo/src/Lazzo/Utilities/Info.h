#pragma once
#include "Lazzo/Window/GraphicsAPI/GraphicsAPI.h"

namespace Lazzo::Utilities {
    class Info {
    private:
        Info() = default;
        ~Info() = default;
        friend class Window;
        GraphicAPI m_GraphicBackend{ GraphicAPI::OpenGL };
    public:
        static Info& GetInstance() {
            static Info obj;
            return obj;
        }
        GraphicAPI GetGraphicBackend() const {
            return m_GraphicBackend;
        }

    };
}
