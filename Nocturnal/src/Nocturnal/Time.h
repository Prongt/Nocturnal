#pragma once
#include "Renderer/RenderCommand.h"

namespace Nocturnal
{
	class Time
	{
	private:
		inline static float sDeltaTime = 0.0f;
		inline static float sLastFrame = 0.0f;
	public:
		inline static void CalculateDeltaTime(const float currentTime) { sDeltaTime = currentTime - sLastFrame; sLastFrame = currentTime; }
		inline static float GetDeltaTime() { return sDeltaTime; }
		inline static float GetTime() { return RenderCommand::GetRenderApi()->GetTime(); }
	};
}
