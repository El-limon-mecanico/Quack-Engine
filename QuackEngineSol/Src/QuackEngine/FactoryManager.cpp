#include "FactoryManager.h"
#include "QuackCamera.h"
#include "Light.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "Prueba.h"
#include "Prueba2.h"
#include "Transform.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"

std::unique_ptr<FactoryManager> FactoryManager::instance_;

FactoryManager::FactoryManager()
{
}

FactoryManager* FactoryManager::Init()
{
	assert(instance_.get() == nullptr);
	instance_.reset(new FactoryManager());
	instance_.get()->initEngineFactories();
	return instance_.get();
}

void FactoryManager::initEngineFactories()
{
	FactoryManager::instance()->add<MeshRenderer>();
	FactoryManager::instance()->add<Rigidbody>();
	FactoryManager::instance()->add<Prueba>();
	FactoryManager::instance()->add<Prueba2>();
	FactoryManager::instance()->add<Transform>();
	FactoryManager::instance()->add<QuackCamera>();
	FactoryManager::instance()->add<Light>();
	FactoryManager::instance()->add<Button>();
	FactoryManager::instance()->add<Text>();
	FactoryManager::instance()->add<Image>();
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
