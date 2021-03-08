#pragma once
#include "Core.h"
#include "InputCodes.h"

namespace Nocturnal
{
	class NOCTURNAL_API Input
	{
	private:
		static Input* sInstance;

	protected:
		virtual bool IsKeyDownImplementation(const int keycode) = 0;
		virtual bool IsMouseDownImplementation(const int keycode) = 0;
		virtual float GetMouseXImplementation() = 0;
		virtual float GetMouseYImplementation() = 0;
		virtual std::tuple<float, float> GetMousePositionImplementation() = 0;
	public:
		/**
		 * \return returns true if key is pressed or held
		 */
		static bool IsKeyDown(const KeyCode keycode) { return sInstance->IsKeyDownImplementation(static_cast<int>(keycode)); }
		/**
		 * \return returns true if key is not pressed or held
		 */
		static bool IsKeyUp(const KeyCode keycode) { return !sInstance->IsKeyDownImplementation(static_cast<int>(keycode));}

		static bool IsMouseDown(const MouseCode mouseCode) { return sInstance->IsMouseDownImplementation(static_cast<int>(mouseCode)); }
		static bool IsMouseDown(const int mouseCode) { return sInstance->IsMouseDownImplementation(mouseCode); }
		static bool IsMouseUp(const MouseCode mouseCode) { return !sInstance->IsMouseDownImplementation(static_cast<int>(mouseCode)); }
		static bool IsMouseUp(const int mouseCode) { return !sInstance->IsMouseDownImplementation(mouseCode); }

		static bool IsButtonDown() { NOC_LOG_NOT_IMPLEMENTED(); return false; }
		static bool IsButtonUp() { NOC_LOG_NOT_IMPLEMENTED(); return false; }

		static std::tuple<float, float> GetMousePosition() { return sInstance->GetMousePositionImplementation(); }
		static float GetMouseX() { return sInstance->GetMouseXImplementation(); }
		static float GetMouseY() { return sInstance->GetMouseYImplementation(); }
		static float GetScrollDelta(bool getVertical = true) { NOC_LOG_NOT_IMPLEMENTED(); return 0; }
	};
}
