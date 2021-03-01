#pragma once
#include "Event.h"

namespace Nocturnal {

	class NOCTURNAL_API MouseMovedEvent : public Event
	{
	private:
		float mMouseX, mMouseY;
	public:
		MouseMovedEvent(const float mouseX, const float mouseY)
			: mMouseX(mouseX), mMouseY(mouseY) {}

		MouseMovedEvent(const double mouseX, const double mouseY)
			: mMouseX(static_cast<float>(mouseX)), mMouseY(static_cast<float>(mouseY)) {}

		float GetX() const { return mMouseX; }
		float GetY() const { return mMouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: X:" << mMouseX << ", Y:" << mMouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	
	};

	class NOCTURNAL_API MouseScrolledEvent : public Event
	{
	private:
		float mXOffset, mYOffset;
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: mXOffset(xOffset), mYOffset(yOffset) {}

		MouseScrolledEvent(const double xOffset, const double yOffset)
			: mXOffset(static_cast<float>(xOffset)), mYOffset(static_cast<float>(yOffset)) {}

		float GetXOffset() const { return mXOffset; }
		float GetYOffset() const { return mYOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: X:" << GetXOffset() << ", Y:" << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class NOCTURNAL_API MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(const int button)
			: mButton(button) {}

		int mButton;
	public:
		int GetMouseButton() const { return mButton; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class NOCTURNAL_API MouseButtonDownEvent : public MouseButtonEvent
	{
	public:
		MouseButtonDownEvent(const int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonDownEvent: " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class NOCTURNAL_API MouseButtonUpEvent : public MouseButtonEvent
	{
	public:
		MouseButtonUpEvent(const int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonUpEvent: " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}