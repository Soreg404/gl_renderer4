#pragma once

namespace glr {


	class Event {
		static void callbackKeyInput(GLFWwindow *w, int key, int scancode, int action, int mods);
		static void callbackCursorPos(GLFWwindow *w, double xpos, double ypos);
		friend class glr::Window;

		std::list<Event *>::iterator _keyEvent;
		bool isKeyEvent = false;

		std::list<Event *>::iterator _curPosEvent;
		bool isCurPosEvent = false;

	public:

		Event() = default;

	protected:

		enum class T: int { KEY = 1, CURPOS };

		virtual void evtKeyInput(Window *w, int key, int action);
		virtual void evtCurPos(Window *w, double xpos, double ypos);

		void evtListen(T eventName);
		void evtRemove(T eventName);

		virtual ~Event() = 0;

	};


}