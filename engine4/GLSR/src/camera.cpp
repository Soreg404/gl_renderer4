#include "glsr.h"

glm::mat4 glr::Camera::getView(const glr::Movable &mov) const {
	return glm::lookAt(mov.pos, (mov.lookLock ? mov.target() : mov.pos + mov.facing()), glm::vec3(0, 1, 0));
}

glm::mat4 glr::Camera::getProj() const {
	Window *w = Renderer::getCurrentRenderer()->getWindow();
	return
		perspective ?
		static_cast<glm::mat4>(glm::perspective(glm::radians(fov), static_cast<float>(w->getW()) / static_cast<float>(w->getH()), zNear, zFar)) :
		static_cast<glm::mat4>(glm::ortho(0, w->getW(), 0, w->getH()));
}
