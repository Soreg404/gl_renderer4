#pragma once

namespace glr {


	class Event {
		static void callbackKeyInput(GLFWwindow *w, int key, int scancode, int action, int mods);
		static void callbackCursorPos(GLFWwindow *w, double xpos, double ypos);
		static void callbackMouseClick(GLFWwindow *window, int button, int action, int mods);
		friend class glr::Window;

		std::list<Event *>::iterator _keyEvent;
		bool isKeyEvent = false;

		std::list<Event *>::iterator _curPosEvent;
		bool isCurPosEvent = false;

		std::list<Event *>::iterator _mouseClickEvent;
		bool isMouseClickEvent = false;

	public:

		Event() = default;

	protected:

		enum class T: int { KEY = 1, CURPOS, MOUSECLICK };

		virtual void evtKeyInput(Window *w, int key, int action);
		virtual void evtCurPos(Window *w, double xpos, double ypos);
		virtual void evtMouseClick(Window *window, int button, int action, int mods);

		void evtListen(T eventName);
		void evtRemove(T eventName);

		virtual ~Event() = 0;

	};


}