#pragma once

namespace glr {

	struct Movable {
		Movable();

		glm::vec3 pos, rotation, scale;

		glm::mat4 getTransform() const;
		glm::mat3 getNormalMatrix(glm::mat4 transform) const;

		glm::mat4 getView() const;


		bool lookLock = false;

		inline glm::vec3 facing() const { return f; }
		inline glm::vec3 target() const { return t; };
		void facing(glm::vec3 newFacing), target(glm::vec3 newTarget);

		glm::vec3 dir(bool normalize = true) const;

		glm::vec3 left() const;
		glm::vec3 up() const;

	private:
		glm::vec3 f, t;

	};

	typedef Ref<Movable> sMov;


}