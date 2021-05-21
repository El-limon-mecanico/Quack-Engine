#include "Prueba2.h"
#include "LuaManager.h"
#include "QuackEntity.h"
#include "Rigidbody.h"
#include "QuackEnginePro.h"
#include "QuackUI.h"

Prueba2::Prueba2(QuackEntity* e) : Component(e)
{

}

Prueba2::~Prueba2()
{
	delete valor2;
}

bool Prueba2::init(luabridge::LuaRef parameterTable)
{
	bool correct = true;
	correct &= readVariable<int>(parameterTable, "valor1", &valor1);
	correct &= readVariable<int>(parameterTable, "valor2", valor2);
	correct &= readVariable<std::string>(parameterTable, "valor3", &valor3);

	if (!correct) return false;

	std::cout << "\nEstas son las variables que has puesto desde lua: \n";
	std::cout << valor1 << "\n";
	std::cout << *valor2 << "\n";
	std::cout << valor3 << "\n";

	return true;
}


void Prueba2::update()
{
	//algo += QuackEnginePro::Instance()->time()->deltaTime();
	//if (entity_->getComponent<Text>())
	//	entity_->getComponent<Text>()->setText(std::to_string(algo));
}
