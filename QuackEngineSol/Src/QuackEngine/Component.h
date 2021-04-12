#pragma once
#pragma once
#include<iostream>
class Entity;

class Component {
	protected:
		Entity* entity_;

	public:
		Component(Entity* e = nullptr) :
			entity_(e) {
		}

		virtual ~Component() {
		}

		inline void setEntity(Entity* e) {
			entity_ = e;
		}

		inline Entity* getEntity() {
			return entity_;
		}

		virtual void init() {
		}

		virtual void update() {
		}

		virtual void render() {
		}

};