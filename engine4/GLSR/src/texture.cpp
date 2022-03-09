#include "glsr.h"

#include "stb_image/stb_image.h"

void glr::Texture::setData(unsigned char *ptr, int _w, int _h, int _nc) {
	if(!ptr) return;
	clearData();
	data = ptr;
	w = _w;
	h = _h;
	nc = _nc;
}

void glr::Texture::clearData() {
	if(data) stbi_image_free(data);
	w = h = nc = 0;
}

void glr::Texture::load(bool cl) {
	if(tid) { GLRLOG("attempted to load already loaded texture"); return; }
	if(!data) { GLRLOG("attempted to load empty texture"); return; }
	glGenTextures(1, &tid);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	if(cl) clearData();

}

void glr::Texture::unload() {
	if(data) stbi_image_free(data);
}

void glr::Texture::bind(GLenum index) {
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, tid);
}

glr::Texture::~Texture() { unload(); }
