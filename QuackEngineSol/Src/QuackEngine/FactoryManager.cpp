#include "FactoryManager.h"

std::unique_ptr<FactoryManager> FactoryManager::instance_;

FactoryManager::FactoryManager()
{
}

Component* FactoryManager::create(const std::string& name)
{
	return hashTable_[name]();
}

