#pragma once
#include "ComponentFactory.h"
#include "Prueba.h"
#include "LuaManager.h"

class PruebaFactory: public ComponentFactory
{
public:
	PruebaFactory(){}
	virtual ~PruebaFactory(){}

	virtual Component* create();
};

