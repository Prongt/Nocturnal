#pragma once
#include "Core.h"
#include "InputCodes.h"

namespace Nocturnal
{
	class NOCTURNAL_API Input
	{
	private:
		static Input* Instance;

	protected:
		virtual bool IsKeyDownImplementation(const int keycode) = 0;
		virtual bool IsMouseDownImplementation(const int keycode) = 0;
		virtual float GetMouseXImplementation() = 0;
		virtual float GetMouseYImplementation() = 0;
		virtual std::tuple<float, float> GetMousePositionImplementation() = 0;
	public:
		/**
		 * \return returns true if key was pressed this frame
		 */
		static bool IsKeyDown(const KeyCode keycode) { return Instance->IsKeyDownImplementation(static_cast<int>(keycode)); }
		static bool IsMouseDown(const int keycode) { return Instance->IsMouseDownImplementation(keycode); }
		static std::tuple<float, float> GetMousePosition() { return Instance->GetMousePositionImplementation(); }
		static float GetMouseX() { return Instance->GetMouseXImplementation(); };
		static float GetMouseY() { return Instance->GetMouseYImplementation(); };
	};
}