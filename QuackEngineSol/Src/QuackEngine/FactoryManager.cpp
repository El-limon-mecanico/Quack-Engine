#include "FactoryManager.h"

bool FactoryManager::add(const std::string& name, ComponentFactory* f)
{
	return hashTable_.insert({ name, f }).second;
}

Component* FactoryManager::create(const std::string& name)
{
	ComponentFactory* f = hashTable_.at(name);

	if (f != nullptr) {
		return f->create();
	}
	else {
		std::cout << "No se ha podido crear el componente " << name << '\n';
		return nullptr;
	}
}
