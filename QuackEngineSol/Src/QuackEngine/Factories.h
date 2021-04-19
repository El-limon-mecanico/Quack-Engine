#pragma once
#include "ComponentFactory.h"
#include "Prueba.h"
#include "RenderComponent.h"
#include "LuaManager.h"

class PruebaFactory: public ComponentFactory
{
public:
	PruebaFactory(){}
	virtual ~PruebaFactory(){}

	virtual Component* create();
};

class RenderComponentFactory : public ComponentFactory
{
public:
	RenderComponentFactory(){}
	virtual ~RenderComponentFactory(){}

	virtual Component* create();
};