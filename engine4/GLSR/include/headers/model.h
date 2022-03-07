#pragma once

#define GLR_VERTEX_BUFFER 1
#define GLR_INDEX_BUFFER 2

namespace glr {

	namespace model {

		struct VAA {
			GLuint index = 0;
			GLint size = 3;
			GLenum type = GL_FLOAT;
			GLboolean normalized = false;
			GLuint byteSize = size * sizeof(float);
		};

		struct Buffer {

			void *data = nullptr;
			size_t bytes = 0;
			unsigned count = 0;
			unsigned stride = 0;
			Buffer(void *data = nullptr, size_t bytes = 0, unsigned count = 0, unsigned stride = 0);
			Buffer(const Buffer &other);
			~Buffer();

		};

	}

	class Mesh {

		GLuint VAO = 0;
		GLuint VBO = 0, EBO = 0;

		Uniq<model::Buffer> vertex, index;

	public:

		void setBuffer(unsigned buff, Uniq<model::Buffer>);

		Mesh() = default;
		Mesh(const Mesh &copy); // delete vao, vbo, ebo
		~Mesh();

		std::vector<model::VAA> vAttributes;
		void recalcVAAs();

		void bind();
		void load();
		void unload();

		void draw();

	};
	typedef Ref<Mesh> sMesh;

	namespace model {

		struct Object {
			struct Slot {
				sShader s;
				sMesh m;
			};
			std::vector<Slot> slots;
			inline Slot *operator[](size_t s) { return s < slots.size() ? &slots.at(s) : nullptr; }
		};
	}

	class Model {

	public:

		std::vector<model::Object> objects;

		void draw(const Movable &m);

		void load();

		Model() = default;

		inline model::Object &operator[](int o) { return objects.at(o); }

		model::Object::Slot *at(size_t object, size_t slot);
		model::Object *at(size_t object);

		Ref<Model> copy() const;

	};

	typedef Ref<Model> sModel;


}