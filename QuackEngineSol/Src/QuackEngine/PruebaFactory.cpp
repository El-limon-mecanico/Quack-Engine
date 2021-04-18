#include "PruebaFactory.h"

Component* PruebaFactory::create()
{
	Prueba* prueba = new Prueba(); //"asi de triste"
	return prueba;
}

Component* RenderComponentFactory::create()
{
	RenderComponent* f = new RenderComponent();
	return f;
}
