#pragma once

namespace glr {

	class Entity {
		friend class Renderer;

	protected:

		virtual void draw();
		virtual ~Entity() = 0;

	public:


	};


	class BasicEntity : public Entity {

	protected:

		virtual void draw() override;

	public:

		glr::sMov mov;

		glr::sModel model;

		BasicEntity();

	};

}