#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include <memory>
#include <assert.h>
#include "Component.h"
#include "checkML.h"

class QUACK_ENGINE_PRO_API FactoryManager {

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

	std::map<std::string, Component* (*)()> hashTable_;

	FactoryManager();
};