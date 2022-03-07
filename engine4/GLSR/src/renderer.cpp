#include "glsr.h"

glr::Renderer *glr::Renderer::currentRenderer = nullptr;

glr::Renderer::Renderer(glr::Window *w): w(w) {
	p.cam = getRef<Camera>();
	p.mov = getRef<Movable>();
}

int glr::Renderer::draw(glr::Entity *const e) {
	
	currentRenderer = this;
	glfwMakeContextCurrent(w->getContext());
	e->draw();

	return 1;

}

glm::vec3 glr::Renderer::curToWorld(glm::dvec2 v) const { return curToWorld(v.x, v.y); }
glm::vec3 glr::Renderer::curToWorld(double x, double y) const {
	double an = -sin(p.cam->fov / 2);
	
	return glm::normalize(glm::vec3{ x *an, y *an, -1 });
}