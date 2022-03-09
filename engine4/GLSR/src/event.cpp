#include "glsr.h"

std::list<glr::Event *> keyEvent;
std::list<glr::Event *> curPosEvent;
std::list<glr::Event *> mouseClickEvent;


glr::Event::~Event() {
	evtRemove(T::KEY);
	evtRemove(T::CURPOS);
	evtRemove(T::MOUSECLICK);
}

#pragma warning (disable:100)
void glr::Event::evtKeyInput(Window *w, int key, int action) {}
void glr::Event::evtCurPos(Window *w, double xpos, double ypos) {}
void glr::Event::evtMouseClick(Window *w, int button, int action, int mods) {}
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
	case T::MOUSECLICK:
		mouseClickEvent.push_back(this);
		_mouseClickEvent = std::prev(mouseClickEvent.end());
		isMouseClickEvent = true;
		break;
	}
}

void glr::Event::evtRemove(glr::Event::T e) {
	switch(e) {
	case T::KEY: if(isKeyEvent) keyEvent.erase(_keyEvent); isKeyEvent = false; break;
	case T::CURPOS: if(isCurPosEvent) curPosEvent.erase(_curPosEvent); isCurPosEvent = false; break;
	case T::MOUSECLICK: if(isMouseClickEvent) mouseClickEvent.erase(_mouseClickEvent); isMouseClickEvent = false; break;
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

void glr::Event::callbackMouseClick(GLFWwindow *w, int button, int action, int mods) {
	for(std::list<glr::Event *>::iterator it = mouseClickEvent.begin(); it != mouseClickEvent.end(); it++)
		(*it)->evtMouseClick(reinterpret_cast<glr::Window *>(glfwGetWindowUserPointer(w)), button, action, mods);
}