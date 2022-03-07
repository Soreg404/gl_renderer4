#pragma once

#include <memory>
#include <string>
#include <array>
#include <vector>
#include <list>


#ifndef GLR_NO_LOG
#include <iostream>
#define GLRLOG(x, ...) printf("\n[" __FILE__ "] %li: " x, __LINE__, __VA_ARGS__);
void _logGLErrors(const char *f, int l);
#define GLERR _logGLErrors(__FILE__, __LINE__)
#else
#define GLRLOG(x, ...)
#define GLERR
#endif


namespace glr {
	namespace util {
		void getFileCStr(char *&data, size_t &size, const char *path);
	}

	class Window;
	class Renderer;

	struct Movable;
	struct Camera;

}



#include "vendor.h"

#include "headers/event.h"

#include "headers/resource.h"

#include "headers/texture.h"
#include "headers/shader.h"
#include "headers/model.h"

#include "headers/movable.h"
#include "headers/camera.h"


#include "headers/entity.h"

#include "headers/renderer.h"
#include "headers/window.h"

#include "headers/resLoader.h"