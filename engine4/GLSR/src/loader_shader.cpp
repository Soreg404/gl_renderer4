#include "GLSR/include/glsr.h"

glr::sShdComp glr::res::loadShdComp(const glr::Window *w, const char *path, ShdType type, const char *name, std::vector<const char *> macros) {

	sShdComp ret = getRef<glr::shader::ShdComp>();

	ret->type = type;

	char *filecontent = nullptr;
	size_t fSize = 0;
	util::getFileCStr(filecontent, fSize, path);
	if(fSize) {
		ret->source = filecontent;
		delete[]filecontent;
		if(w) {
			glfwMakeContextCurrent(w->getContext());
			ret->compile();
		}
	} else {
		GLRLOG("error loading ShdComp");
		return ret;
	}

	return ret;

}

glr::sShader glr::res::loadShader(const glr::Window *w, const char *vertexPath, const char *fragmentPath, std::vector<const char *> macros) {

	sShdComp vComp = loadShdComp(w, vertexPath, ShdType::VERTEX, "", macros);
	sShdComp fComp = loadShdComp(w, fragmentPath, ShdType::FRAGMENT, "", macros);

	return loadShader(w, vComp, fComp);

}

glr::sShader glr::res::loadShader(const glr::Window *w, sShdComp vert, sShdComp frag) {
	glfwMakeContextCurrent(w->getContext());
	sShader ret = getRef<Shader>();
	ret->attach(vert);
	ret->attach(frag);
	ret->link();
	return ret;
}

