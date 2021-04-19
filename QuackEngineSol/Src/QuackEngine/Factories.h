#pragma once
#include "ComponentFactory.h"
#include "Prueba.h"
#include "Render.h"
#include "LuaManager.h"

class PruebaFactory: public ComponentFactory
{
public:
	PruebaFactory(){}
	virtual ~PruebaFactory(){}

	virtual Component* create();
};

class RenderFactory : public ComponentFactory
{
public:
	RenderFactory(){}
	virtual ~RenderFactory(){}

	virtual Component* create();
};