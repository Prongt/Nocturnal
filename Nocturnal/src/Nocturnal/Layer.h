#pragma once
#include "Events/Event.h"
#include "Nocturnal/Core.h"

namespace Nocturnal
{
	class NOCTURNAL_API Layer
	{
	protected:
		std::string LayerName;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(){}
		virtual void OnEvent(Event& event){}

		const std::string& GetName() const { return LayerName; }
	};
}
