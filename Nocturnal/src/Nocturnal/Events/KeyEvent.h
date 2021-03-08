#pragma once
#include "Event.h"


namespace Nocturnal {

	class NOCTURNAL_API KeyEvent : public Event
	{

	protected:
		KeyEvent(const int keycode)
			: mKeyCode(keycode) {}

		int mKeyCode;
	public:
		int GetKeyCode() const { return mKeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	class NOCTURNAL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class NOCTURNAL_API KeyHeldEvent : public KeyEvent
	{
	private:
		int mRepeatCount;
		
	public:
		KeyHeldEvent(const int keycode, const int repeatCount)
			: KeyEvent(keycode), mRepeatCount(repeatCount) {}

		int GetRepeatCount() const { return mRepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyHeld: " << mKeyCode << " (" << mRepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyHeld)
	};

	class NOCTURNAL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class NOCTURNAL_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}