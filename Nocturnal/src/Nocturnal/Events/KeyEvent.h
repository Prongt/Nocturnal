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

	class NOCTURNAL_API KeyDownEvent : public KeyEvent
	{
	private:
		int RepeatCount;
		
	public:
		KeyDownEvent(const int keycode, const int repeatCount)
			: KeyEvent(keycode), RepeatCount(repeatCount) {}

		int GetRepeatCount() const { return RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyDownEvent: " << KeyCode << " (" << RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyDown)
	};

	class NOCTURNAL_API KeyUpEvent : public KeyEvent
	{
	public:
		KeyUpEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyUpEvent: " << KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyUp)
	};

	class NOCTURNAL_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}