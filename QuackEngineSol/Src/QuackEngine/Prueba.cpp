#include "Prueba.h"
#include "LuaManager.h"
#include "QuackEntity.h"
// #include "checkML.h"

Prueba::Prueba(QuackEntity* e) : Component(e)
{

}

Prueba::~Prueba()
{
}

bool Prueba::init(luabridge::LuaRef parameterTable)
{	
	if (!parameterTable.state())
		return false;
		
	readVariable<int>(parameterTable, "valor1", valor1);
	valor2 = new int();
	readVariable<int>(parameterTable, "valor2", *valor2);
	readVariable<std::string>(parameterTable, "valor3", valor3);

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

