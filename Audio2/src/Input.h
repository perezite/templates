#pragma once

namespace sb
{
	class Input
	{
	public:
		static void update();

		static bool hasQuitEvent() { return m_hasQuitEvent; }

		static bool isMouseGoingDown() { return m_mouseGoingDown; }

		static bool isTouchGoingDown() { return m_touchGoingDown; }

	private:
		static bool m_hasQuitEvent;

		static bool m_mouseGoingDown;

		static bool m_touchGoingDown;
	};
}
