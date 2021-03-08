#pragma once
#include "NocturnalPrecompiledHeaders.h"
#include "Nocturnal/Core.h"


namespace Nocturnal
{
	//Events in Nocturnal are blocking
	//As soon as an event occurs the entire application is stopped
	//and the event is processed
	
	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyHeld,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
								virtual EventType GetEventType() const override { return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category;}

	class NOCTURNAL_API Event
	{
	public:
		bool EventHasBeenHandled = false;

		inline bool IsInCategory(const EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFunction = std::function<bool(T&)>;
	
	private:
		Event& mEventInstance;
	public:
		EventDispatcher(Event& event) : mEventInstance(event) {}
		
		template<typename T>
		bool Dispatch(EventFunction<T> function)
		{
			if (mEventInstance.GetEventType() == T::GetStaticType())
			{
				mEventInstance.EventHasBeenHandled = function(*static_cast<T*>(&mEventInstance));
				return true;
			}

			return false;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.ToString();
	}
}
