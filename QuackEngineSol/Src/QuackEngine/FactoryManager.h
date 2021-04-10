#pragma once
#include "ComponentFactory.h"

class FactoryManager {
private:
	//TODO cambiar a una tabla de lua
	std::unordered_map<std::string, ComponentFactory*> hashTable_;

public:
	FactoryManager() {}
	~FactoryManager() {}

	bool add(const std::string& name, ComponentFactory* f); //TODO manejar error
	Component* create(const std::string& name);
};