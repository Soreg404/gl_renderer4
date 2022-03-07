#include "glsr.h"

void glr::Entity::draw() {}

glr::Entity::~Entity() {}

glr::BasicEntity::BasicEntity() : mov(getRef<Movable>()), model(getRef<Model>()) {}

void glr::BasicEntity::draw() {

	model->draw(*mov.get());

}
