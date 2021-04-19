#pragma once
#include "ComponentFactory.h"
#include "Render.h"
#include <memory>
#include <assert.h>

class FactoryManager {

public:
	
	FactoryManager(FactoryManager&) = delete;
	FactoryManager& operator = (FactoryManager&) = delete;
	  
	virtual ~FactoryManager(){}

	static  FactoryManager* init()
	{
		assert(instance_.get() == nullptr);
		instance_.reset(new FactoryManager());
		return instance_.get();
	}

	static FactoryManager* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}
	
	bool add(const std::string& name, ComponentFactory* f);

	template<typename T>
	T* create(const std::string& name) {

		if (hashTable_.at(name)) {
			return new T();
		}
		else {
			std::cout << "No se ha podido crear el componente " << name << '\n';
			return nullptr;
		}
	}
	//TODO crear otra template que no use strings, cambiar la hashtable a <string, Component>

	Component* create(const std::string& name);

protected:
	static std::unique_ptr<FactoryManager> instance_;

private:
	std::unordered_map<std::string, ComponentFactory*> hashTable_;

	FactoryManager();
};