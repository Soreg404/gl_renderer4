#include "glsr.h"

std::list<glr::Event *> keyEvent;
std::list<glr::Event *> curPosEvent;


glr::Event::~Event() {
	evtRemove(T::KEY);
	evtRemove(T::CURPOS);
}

#pragma warning (disable:100)
void glr::Event::evtKeyInput(Window *w, int key, int action) {}
void glr::Event::evtCurPos(Window *w, double xpos, double ypos) {}
#pragma warning (default:100)

void glr::Event::evtListen(glr::Event::T e) {
	switch(e) {
	case T::KEY:
		keyEvent.push_back(this);
		_keyEvent = std::prev(keyEvent.end());
		isKeyEvent = true;
		break;
	case T::CURPOS:
		curPosEvent.push_back(this);
		_curPosEvent = std::prev(curPosEvent.end());
		isCurPosEvent = true;
		break;
	}
}

void glr::Event::evtRemove(glr::Event::T e) {
	switch(e) {
	case T::KEY: if(isKeyEvent) keyEvent.erase(_keyEvent); isKeyEvent = false; break;
	case T::CURPOS: if(isCurPosEvent) curPosEvent.erase(_curPosEvent); isCurPosEvent = false; break;
	}
}


void glr::Event::callbackKeyInput(GLFWwindow *w, int key, int scancode, int action, int mods) {
	for(std::list<glr::Event *>::iterator it = keyEvent.begin(); it != keyEvent.end(); it++)
		(*it)->evtKeyInput(reinterpret_cast<glr::Window *>(glfwGetWindowUserPointer(w)), key, action);
}

void glr::Event::callbackCursorPos(GLFWwindow *w, double x, double y) {
	for(std::list<glr::Event *>::iterator it = curPosEvent.begin(); it != curPosEvent.end(); it++)
		(*it)->evtCurPos(reinterpret_cast<glr::Window *>(glfwGetWindowUserPointer(w)), x, y);
}