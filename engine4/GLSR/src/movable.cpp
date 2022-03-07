#include "glsr.h"

glr::Movable::Movable(): pos(0), rotation(0), scale(1), f({ 0, 0, -1 }), t({ 0, 0, -1 }) {}

glm::mat4 glr::Movable::getTransform() const {
	glm::mat4 transl = glm::translate(glm::mat4(1.f), pos);
	glm::mat4 rotatx = glm::rotate(glm::mat4(1.f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
	glm::mat4 rotaty = glm::rotate(glm::mat4(1.f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
	glm::mat4 rotatz = glm::rotate(glm::mat4(1.f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
	glm::mat4 scal = glm::scale(glm::mat4(1.f), scale);
	return transl * ((rotatx * rotaty * rotatz) * scal);
}
glm::mat3 glr::Movable::getNormalMatrix(glm::mat4 transform) const {
	return glm::mat3(glm::transpose(glm::inverse(transform)));
}

glm::mat4 glr::Movable::getView() const {
	//return glm::lookAt(pos, dir(), glm::vec3(0, 1, 0));
	return glm::lookAt(pos, lookLock ? t : pos + f, glm::vec3(0, 1, 0));
}


glm::vec3 glr::Movable::dir(bool normalize) const {
	if(lookLock) {
		glm::vec3 d = pos - t;
		if(d != glm::vec3(0))
			return normalize ? glm::normalize(d) : d;
	}
	return f;
}
void glr::Movable::facing(glm::vec3 newFacing) { f = glm::normalize(newFacing); }
void glr::Movable::target(glm::vec3 newTarget) { t = newTarget; }


glm::vec3 glr::Movable::left() const {
	return glm::normalize(glm::cross(glm::vec3(0, 1, 0), dir(false)));
}
glm::vec3 glr::Movable::up() const {
	glm::vec3 d = dir(false);
	return glm::normalize(glm::cross(d, glm::cross(glm::vec3(0, 1, 0), d)));
}