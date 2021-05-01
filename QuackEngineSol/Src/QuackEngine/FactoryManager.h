#pragma once
#include <memory>
#include <assert.h>
#include "Component.h"
#include "checkML.h"

class FactoryManager {

public:

	FactoryManager(FactoryManager&) = delete;
	FactoryManager& operator = (FactoryManager&) = delete;

	virtual ~FactoryManager() {}

	static  FactoryManager* init();

	static FactoryManager* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	template<typename T>
	void add() {
		hashTable_[T::GetName()] = &FactoryManager::createComponent<T>;
	}

	Component* create(const std::string& name);

protected:
	static std::unique_ptr<FactoryManager> instance_;

private:
	template<typename T>
	static Component* createComponent() {
		return new T();
	}

	std::map<std::string, Component*(*)()> hashTable_;

	FactoryManager();
};