#pragma once
#include "Events/Event.h"
#include "Nocturnal/Core.h"

namespace Nocturnal
{
	class NOCTURNAL_API Layer
	{
	protected:
		std::string mLayerName;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(const float deltaTime){}
		virtual void OnEvent(Event& event){}
		virtual void OnImGuiRender(){}
		

		const std::string& GetName() const { return mLayerName; }
	};
}
