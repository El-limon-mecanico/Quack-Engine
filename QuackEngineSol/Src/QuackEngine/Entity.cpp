#include "Entity.h"
Entity::~Entity() {
	for (auto c : components_) {
		delete c;
	}
}

//Comentamos el Update y Render de Samir porque lo haremos diferente pero ykse
	/*void Entity::update() {
		std::size_t n = components_.size();
		for (auto i = 0u; i < n; i++) {
			components_[i]->update();
		}
	}

	void Entity::render() {
		std::size_t n = components_.size();
		for (auto i = 0u; i < n; i++) {
			components_[i]->render();
		}
	}*/