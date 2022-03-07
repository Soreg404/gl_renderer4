#include "GLSR/include/glsr.h"
#include <fstream>

void _logGLErrors(const char *f, int l) {
	int err = 0;
	while((err = glGetError()) != GL_NO_ERROR) {
		printf("\n[%s] %i: OpenGL error: %i", f, l, err);
	}
}

void glr::util::getFileCStr(char *&data, size_t &size, const char *path) {

	struct stat st;
	stat(path, &st);
	size = st.st_size;

	std::ifstream file(path, std::ios::binary);
	if(!file.good()) GLRLOG("couldnt load file: %s", path);

	data = new char[size + 1];

	file.read(data, size);
	data[size] = 0;

}
