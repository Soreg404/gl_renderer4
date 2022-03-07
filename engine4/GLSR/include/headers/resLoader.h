#pragma once

namespace glr {

	namespace res {

		sShdComp loadShdComp(const glr::Window *w, const char *path, ShdType type, const char *name = "", std::vector<const char *> macros = {});

		sShader loadShader(const glr::Window *w, const char *vertexPath, const char *fragmentPath, std::vector<const char *> macros = {});
		sShader loadShader(const glr::Window *w, sShdComp vert, sShdComp frag);

		sModel loadModel(const glr::Window *w, const char *path);

		sTex loadTexture2D(const glr::Window *w, const char *path);

	}

}