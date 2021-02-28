#pragma once

namespace Nocturnal
{
	class Time
	{
	private:
		inline static float sDeltaTime = 0.0f;
		inline static float sLastFrame = 0.0f;
	public:
		static void CalculateDeltaTime(const float currentTime);
		static float GetDeltaTime() { return sDeltaTime; };
	};
}
