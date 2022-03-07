#pragma once

namespace glr {

	class Renderer {

		friend class glr::Window;
		glr::Window *w;
		Renderer(glr::Window *w);



	public:
		static Renderer *currentRenderer;

		struct Props {

			sCam cam;
			sMov mov;

		} p;

		inline static Renderer *getCurrentRenderer() { return currentRenderer; }
		inline glr::Window *getWindow() { return w; }
		inline glr::Window *getWindow() const { return w; }

		int draw(Entity *const e);

		glm::vec3 curToWorld(glm::dvec2 cur) const;
		glm::vec3 curToWorld(double x, double y) const;

	};
}