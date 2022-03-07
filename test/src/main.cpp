#include "glsr.h"

using namespace glr::res;

struct Obj: public glr::Event, glr::Entity {

	void evtKeyInput(int key, int action) override {
		if(key == GLFW_KEY_S && action) {
			usedShd++;
			if(usedShd > 2) usedShd = 0;
		}
	}

	int usedShd = 0;

	glr::sMov mov;

	std::array<glr::sShader, 3> shd;

	glr::sTex tex;
	glr::sModel mod;

	Obj(): mov(makeMovable()), mod(makeModel()) {
		evtListen(Event::T::KEY);
	}

	void draw() override {
		glr::Renderer *cr = glr::Renderer::getCurrentRenderer();

		shd[usedShd]->use();
		shd[usedShd]->setCamera(*cr->p.mov.get(), *cr->p.cam.get());

		shd[usedShd]->setModel(*mov.get());

		tex->bind(0);

		mod->draw();

	}

};

int main() {


	if(!glfwInit()) {
		GLRLOG("glfw error");
		return 1;
	}

	glr::Window w(1200, 800, "test");
	w.create();

	glr::Renderer rnd = w.createRenderer();

	glr::sShdComp vComp = loadShdComp(&w, "res/shaders/pos.vert", glr::ShdType::VERTEX);

	glr::sShdComp fComp = loadShdComp(&w, "res/shaders/color.frag", glr::ShdType::FRAGMENT);

	glr::sShdComp texComp = loadShdComp(&w, "res/shaders/texture.frag", glr::ShdType::FRAGMENT);

	glr::sShdComp diffuseComp = loadShdComp(&w, "res/shaders/diff.frag", glr::ShdType::FRAGMENT);
	
	glr::sShader shd1 = makeShader();
	shd1->attach(fComp);
	shd1->attach(vComp);
	shd1->link();

	glr::sShader diff = makeShader();
	diff->attach(vComp);
	diff->attach(diffuseComp);
	diff->link();

	glr::sShader textureShd = makeShader();
	textureShd->attach(vComp);
	textureShd->attach(texComp);
	textureShd->link();

	glr::sMesh m2 = loadMesh(&w, "res/models/torus.obj");

	glr::sTex t1 = glr::res::loadTexture2D(&w, "res/textures/frogz.png");

	Obj o;
	o.mov->pos.z = -14;
	o.shd[0] = shd1;
	o.shd[1] = diff;
	o.shd[2] = textureShd;
	o.mod->meshes.push_back(m2);
	o.tex = t1;

	float rt = 0;
	while(!w.shouldClose()) {


		o.mov->rotation += glm::vec3(.01, .08, .1);
		o.mov->scale = glm::vec3(sin(rt) * 3 + 4 + sin(4 * rt));
		rt += .02;
		rnd.draw(&o);

		w.frame();
	}

	return 0;
}