#pragma once
#include "ComponentFactory.h"

class FactoryManager {
private:
	std::unordered_map<std::string, ComponentFactory*> hashTable_;

public:
	FactoryManager() {}
	~FactoryManager() {}

	bool add(const std::string& name, ComponentFactory* f);
	Component* create(const std::string& name);
};