#pragma once
#include "Nocturnal/Input.h"

namespace Nocturnal
{
	class WindowsInput : public Input
	{
	private:
		static auto* GetGLFWWindow();
	protected:
		bool IsKeyDownImplementation(int keycode) override;
		bool IsMouseDownImplementation(int button) override;
		std::tuple<float, float> GetMousePositionImplementation() override;
		float GetMouseXImplementation() override;
		float GetMouseYImplementation() override;
	};
}
