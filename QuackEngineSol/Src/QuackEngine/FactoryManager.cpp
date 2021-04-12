#include "FactoryManager.h"

std::unique_ptr<FactoryManager> FactoryManager::instance_;

FactoryManager::FactoryManager()
{
}


bool FactoryManager::add(const std::string& name, ComponentFactory* f)
{
	try
	{
		return hashTable_.insert({ name, f }).second;
	}
	catch (std::exception e)
	{
		std::cout << "ERROR: algo ha ido mal al insertar la factoria del componente " << name << " a la tabla hash\n";
	}
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

