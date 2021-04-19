#include "Factories.h"

Component* PruebaFactory::create()
{
	Prueba* prueba = new Prueba(); //"asi de triste"
	return prueba;
}

Component* RenderFactory::create()
{
	Render* f = new Render();
	return f;
}
