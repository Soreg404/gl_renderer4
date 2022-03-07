#include "GLSR/include/glsr.h"

glr::model::Buffer::Buffer(void *d, size_t b, unsigned c, unsigned s): data(d), bytes(b), count(c), stride(s) {}
glr::model::Buffer::Buffer(const Buffer &o): bytes(o.bytes), count(o.count), stride(o.stride) {
	data = new char[bytes];
	memcpy_s(data, bytes, o.data, o.bytes);
}
glr::model::Buffer::~Buffer() {
	if(data) delete[]data;
}

void glr::Mesh::setBuffer(unsigned buff, Uniq<model::Buffer> b) {
	switch(buff) {
	case GLR_VERTEX_BUFFER:
		vertex = std::move(b);
		break;
	case GLR_INDEX_BUFFER:
		index = std::move(b);
		break;
	}
}

glr::Mesh::Mesh(const Mesh &c): vertex(getUniq<model::Buffer>(*c.vertex.get())), index(getUniq<model::Buffer>(*c.index.get())) {}

glr::Mesh::~Mesh() {
	unload();
}

void glr::Mesh::recalcVAAs() {
	if(!VAO || !VBO || !vertex) return;
	bind();
	int maxVAA = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVAA);
	__int64 offset = 0;
	for(int i = 0; i < maxVAA; i++) glDisableVertexAttribArray(i);
	for(int i = 0; i < vAttributes.size(); i++) {
		model::VAA curr = vAttributes.at(i);
		glVertexAttribPointer(curr.index, curr.size, curr.type, curr.normalized, vertex->stride, reinterpret_cast<void *>(offset));
		glEnableVertexAttribArray(curr.index);
		offset += curr.byteSize;
	}
}

void glr::Mesh::bind() {
	if(!VAO) return;
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void glr::Mesh::load() {
	if(!vertex) { GLRLOG("tried to load mesh without vertex data");  return; }
	if(VAO) { GLRLOG("tried to load already loaded mesh"); return; }

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, &VBO);

	recalcVAAs();
	glBufferData(GL_ARRAY_BUFFER, vertex->bytes, vertex->data, GL_STATIC_DRAW);
	if(index) glBufferData(GL_ELEMENT_ARRAY_BUFFER, index->bytes, index->data, GL_STATIC_DRAW);
}

void glr::Mesh::unload() {
	if(VAO) glDeleteVertexArrays(1, &VAO);
	if(VBO) glDeleteBuffers(1, &VBO);
	if(EBO) glDeleteBuffers(1, &EBO);
}

void glr::Mesh::draw() {
	if(!VAO) { GLRLOG("attempted to draw not loaded mesh"); return; }
	bind();
	if(!index)
		glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertex->count));
	else
		glDrawElements(GL_TRIANGLES, index->count, GL_UNSIGNED_INT, 0);
}

void glr::Model::draw(const glr::Movable &m) {
	glr::Renderer *cr = glr::Renderer::getCurrentRenderer();
	for(auto o = objects.begin(); o != objects.end(); o++) {
		for(auto slot = o->slots.begin(); slot != o->slots.end(); slot++) {
			slot->s->setCamera(*cr->p.mov.get(), *cr->p.cam.get());
			slot->s->setModel(m);
			slot->s->use();
			slot->m->draw();
		}
	}
}

void glr::Model::load() {
	for(auto o = objects.begin(); o != objects.end(); o++) {
		for(auto s = o->slots.begin(); s != o->slots.end(); s++) {
			s->m->load();
		}
	}
}

glr::Ref<glr::Model> glr::Model::copy() const {
	Ref<Model> ret = getRef<Model>();
	ret->objects = objects;
	return ret;
}

glr::model::Object::Slot *glr::Model::at(size_t o, size_t s) {
	if(model::Object *ob = at(o)) {
		if(s < ob->slots.size()) return &ob->slots.at(s);
	}
	return nullptr;
}

glr::model::Object *glr::Model::at(size_t o) {
	if(o < objects.size()) return &objects.at(o);
	return nullptr;
}

