#include "FactoryManager.h"

std::unique_ptr<FactoryManager> FactoryManager::instance_;

FactoryManager::FactoryManager()
{
}

Component* FactoryManager::create(const std::string& name)
{
	auto it = hashTable_.find(name);
	if(it == hashTable_.end())
	{
		std::cout << "ERROR: NO SE HA PODIDO LEER EL COMPONENTE: " << name << "\n";
		std::cout << "ha petado a posta, no me pegueis por favor\n";
		throw;// "No se ha encontrado un componente";
	}
	else return hashTable_[name]();
}
