#pragma once
#include "Nocturnal/Layer.h"


namespace Nocturnal
{
	class NOCTURNAL_API ImGuiLayer : public Layer
	{
	private:
		float DeltaTime = 0;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	};
}
