#include "Prueba.h"
#include "LuaManager.h"
#include "QuackEntity.h"
#include "checkML.h"

Prueba::Prueba(QuackEntity* e) : Component(e)
{

}

Prueba::~Prueba()
{

#if (!defined _DEBUG) && (defined _WIN32)
	delete valor2;		// dejar comentado para que estemos seguros de que siempre se estan viendo los memory leaks
	//std::cout << "WARNING: La basura no esta apareciendo en la salida, deberia haber al menos 4 bytes de basura\n";
#endif
}

bool Prueba::init(luabridge::LuaRef parameterTable)
{	
	valor1 = readVariable<int>(parameterTable, "valor1");
	valor2 = new int(readVariable<int>(parameterTable, "valor2"));
	valor3 = readVariable<std::string>(parameterTable, "valor3");

	std::cout << "\nEstas son las variables que has puesto desde lua: \n";
	std::cout << valor1 << "\n";
	std::cout << *valor2 << "\n";
	std::cout << valor3 << "\n";

	return true;
}

void Prueba::update()
{
	//std::cout << " Update de Prueba\n";
}

void Prueba::onCollisionEnter(QuackEntity* other)
{
	std::cout << "Yo " << entity_->name() << " acabo de chocar con " << other->name() << "\n\n";
}

void Prueba::onCollisionStay(QuackEntity* other)
{
	//std::cout << "Yo " << entity_->name() << " sigo chocando con " << other->name() << "\n\n";
}

void Prueba::onCollisionExit(QuackEntity* other)
{
	std::cout << "Yo " << entity_->name() << " he dejado de chocar con " << other->name() << "\n\n";
}

