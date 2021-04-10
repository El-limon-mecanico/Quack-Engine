#pragma once
#include "Component.h"

class ComponentFactory {
public:
	ComponentFactory() {}
	virtual ~ComponentFactory() {}

	virtual Component* create() = 0;
};