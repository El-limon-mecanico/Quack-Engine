#include "Prueba2.h"
#include "LuaManager.h"
#include "QuackEntity.h"
#include "Rigidbody.h"
#include "QuackEnginePro.h"

Prueba2::Prueba2(QuackEntity* e) : Component(e)
{

}

Prueba2::~Prueba2()
{
	delete valor2;
}

bool Prueba2::init(luabridge::LuaRef parameterTable)
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


void Prueba2::update()
{
	transform->Rotate(Vector3D(0, 0, 90) * QuackEnginePro::Instance()->time()->deltaTime());
}
