#include "NocturnalPrecompiledHeaders.h"
#include "Time.h"

namespace Nocturnal
{
	void Time::CalculateDeltaTime(const float currentTime)
	{
		sDeltaTime = currentTime - sLastFrame;
		sLastFrame = currentTime;
	}
}
