#include "GLSR/include/glsr.h"

glr::Window::Window(int W, int H, const char *title) { setSize(W, H); setTitle(title); }

glr::Window::~Window() { shouldClose(true); glfwDestroyWindow(context); }

void glr::Window::create() {
	if(context) { GLRLOG("window already exists"); return; }
	context = glfwCreateWindow(wW, wH, title, nullptr, nullptr);
	if(!context) { GLRLOG("couldn't create window"); return; }
	glfwMakeContextCurrent(context);
	glfwSetWindowUserPointer(context, this);

	glfwSetKeyCallback(context, Event::callbackKeyInput);
	glfwSetCursorPosCallback(context, Event::callbackCursorPos);
	glfwSetMouseButtonCallback(context, Event::callbackMouseClick);

	if(glewInit() != GLEW_OK) { GLRLOG("error initializing glew"); shouldClose(true); return; }
	glViewport(0, 0, wW, wH);
	glClearColor(.3f, .3f, .3f, 1.f);
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	lastTimestamp = glfwGetTime();
}

bool glr::Window::shouldClose() const {
	if(context) return glfwWindowShouldClose(context);
	else return true;
}

void glr::Window::shouldClose(bool setShouldClose) {
	if(!context) return;
	glfwSetWindowShouldClose(context, setShouldClose);
}


void glr::Window::frame() {
	double currTimestamp = glfwGetTime();
	frameTime = currTimestamp - lastTimestamp;
	lastTimestamp = currTimestamp;

	glfwMakeContextCurrent(context);
	glfwPollEvents();
	glfwSwapBuffers(context);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::dvec2 glr::Window::curpos() const {
	glm::dvec2 ret;
	glfwGetCursorPos(context, &ret.x, &ret.y);
	return { (ret.x - wWh) / wWh, -(ret.y - wHh) / wHh };
}

void glr::Window::setSize(int W, int H) {
	wW = W; wWh = W / 2;
	wH = H; wHh = H / 2;
}

void glr::Window::setTitle(const char *title) {
	this->title = title;
}
