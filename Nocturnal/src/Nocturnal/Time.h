#pragma once
#include "Application.h"
#include "Renderer/RenderCommand.h"

namespace Nocturnal
{
	class Time
	{
	private:
		inline static float sDeltaTime = 0.0f;
		inline static float sLastFrame = 0.0f;
		inline static float sTime;
	protected:
		friend class Application;//Application is friend to allow it to update the time
		inline static void UpdateTime() { sTime = RenderCommand::GetRenderApi()->GetTime(); sDeltaTime = sTime - sLastFrame; sLastFrame = sTime; }
	public:
		inline static float GetDeltaTime() { return sDeltaTime; }
		inline static float GetTime() { return sTime; }
		inline static float GetTimeInMilliseconds() { return sTime * 1000.0f; }
	};
}
