#include "glsr.h"

#include "stb_image/stb_image.h"

struct TDim {
    int width, height, nChannels;
};

unsigned char *getTexture(const char *path, TDim *dim) {
    stbi_set_flip_vertically_on_load(true);
    return stbi_load(path, &dim->width, &dim->height, &dim->nChannels, 0);
}

glr::sTex glr::res::loadTexture2D(const glr::Window *w, const char *path) {

    sTex ret = getRef<glr::Texture>();

    TDim dim;
    unsigned char *data = getTexture(path, &dim);
    if(!data) { GLRLOG("error loading texture %s", path); return ret; }

    ret->setData(data, dim.width, dim.height, dim.nChannels);

    if(w) {
        glfwMakeContextCurrent(w->getContext());
        ret->load();
    }

    return ret;

}
