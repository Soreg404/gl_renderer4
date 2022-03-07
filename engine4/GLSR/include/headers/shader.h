#pragma once

namespace glr {

	enum class ShdType { VERTEX, FRAGMENT };


	namespace shader {

		struct ShdComp {

			ShdComp() = default;
			ShdComp(std::string src, ShdType type);
			~ShdComp();

			std::string source;
			ShdType type = ShdType::VERTEX;

			int compile();
			int recompile();
			
			inline GLuint getId() const { return id; }
			inline ShdType getType() const { return type; }

		private:
			GLuint id = 0;
		};

	}

	typedef Ref<shader::ShdComp> sShdComp;

	class Shader {

		GLuint pid = 0;

		std::array<GLuint, 2> sids = { 0 };

		bool linked = false;

	public:

		Shader() = default;
		~Shader();

		void attach(const shader::ShdComp &shd);
		inline void attach(sShdComp c) { attach(*c.get()); }
		int link();
		void clear();

		inline Shader &operator+(const sShdComp &a) { attach(a); return *this; }
		inline Shader &operator+=(const sShdComp &a) { attach(a); return *this; }

		void use() const;

		// uniformy

		void setFloat(const char *name, glm::vec1 v) const;
		void setFloat(const char *name, glm::vec2 v) const;
		void setFloat(const char *name, glm::vec3 v) const;
		void setFloat(const char *name, glm::vec4 v) const;

		void setMat(const char *name, glm::mat3 v) const;
		void setMat(const char *name, glm::mat4 v) const;

		void setCamera(const glr::Movable &mov, const glr::Camera &cam) const;
		void setModel(const glr::Movable &mov) const;

	};

	typedef Ref<Shader> sShader;

}