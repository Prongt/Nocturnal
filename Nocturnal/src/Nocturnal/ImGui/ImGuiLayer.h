#pragma once
#include "Nocturnal/Layer.h"
#include "Nocturnal/Application.h"


namespace Nocturnal
{
	class NOCTURNAL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;
		void OnEvent(Event& event) override;

		void Begin();
		void End();
	};
}
