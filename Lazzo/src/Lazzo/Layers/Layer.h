#pragma once
#include <Lazzo/Core.h>
#include <Lazzo/Window/Events/Event.h>

namespace Lazzo {
    class LAZZO_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}
        
        inline const std::string& GetName() const { return m_DebugName; }

    private:
        std::string m_DebugName;
    };
}
