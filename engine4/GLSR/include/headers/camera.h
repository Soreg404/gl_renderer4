#pragma once

namespace glr {
	struct Camera {

		int perspective = 1;
		float fov = 45.f, zNear = .1f, zFar = 100.f;

		glm::mat4 getView(const glr::Movable &mov) const;
		glm::mat4 getProj() const;

	};

	typedef Ref<Camera> sCam;

}