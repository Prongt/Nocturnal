#pragma once
#include "Event.h"


namespace Nocturnal {

	class NOCTURNAL_API KeyEvent : public Event
	{

	protected:
		KeyEvent(const int keycode)
			: KeyCode(keycode) {}

		int KeyCode;
	public:
		int GetKeyCode() const { return KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	class NOCTURNAL_API KeyPressedEvent : public KeyEvent
	{
	private:
		int RepeatCount;
		
	public:
		KeyPressedEvent(const int keycode, const int repeatCount)
			: KeyEvent(keycode), RepeatCount(repeatCount) {}

		int GetRepeatCount() const { return RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << KeyCode << " (" << RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class NOCTURNAL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}