#pragma once

namespace glr {

	namespace texture {
	}

	class Texture {

		int w = 0, h = 0, nc = 0;

		GLuint tid;

		unsigned char *data = nullptr;

	public:

		void setData(unsigned char *ptr, int w, int h, int nc);
		void clearData();

		void load(bool clearAfterLoad = false);
		void unload();

		void bind(unsigned index = 0);

		~Texture();

	};


	typedef Ref<Texture> sTex;

}