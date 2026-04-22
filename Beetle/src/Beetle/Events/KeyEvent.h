#pragma once

#include "Event.h"

#include <sstream>

namespace Beetle {

	class KeyEvent : public Event
	{
	public: 
		inline int GetKeyCode() const { return m_KeyCode; }
		inline int GetModifiers() const { return m_Modifiers; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode, int modifiers)
			: m_KeyCode(keycode), m_Modifiers(modifiers) {}

		int m_KeyCode;
		int m_Modifiers;
	};

	class  KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount, int modifiers)
			: KeyEvent(keycode, modifiers), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class  KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode, int modifiers) : KeyEvent(keycode, modifiers) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEven: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class  KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode, 0) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}