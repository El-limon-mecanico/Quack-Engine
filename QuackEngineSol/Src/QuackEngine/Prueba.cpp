#include "Prueba.h"
#include "LuaManager.h"
#include "QuackEntity.h"
#include "Rigidbody.h"

Prueba::Prueba(QuackEntity* e) : Component(e)
{

}

Prueba::~Prueba()
{
	delete valor2;
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

void Prueba::start()
{
	if (entity_->getComponent<Rigidbody>()) {
		entity_->getComponent<Rigidbody>()->setGravity(Vector3D());
	}
}

void Prueba::fixedUpdate()
{
	std::cout << transform->rotation().x() << " " << transform->rotation().y() << " " << transform->rotation().z() << "\n";
	//entity_->getComponent<Rigidbody>()->addTorque({ 0,1,0 });
}

void Prueba::update()
{
	transform->Translate(Vector3D(0, -0.1, 0),true);
	if (transform->position.y() < -10) {
		transform->Rotate(Vector3D(0, 45, 0));
		transform->Translate(Vector3D(0, 10, 0), true);
		//entity_->getComponent<Rigidbody>()->clearForce();
	}
	//std::cout << " Update de Prueba\n";
	
}

void Prueba::onCollisionEnter(QuackEntity* other, Vector3D point)
{
	//entity_->getComponent<Rigidbody>()->addForce(Vector3D(0, 10, 0), IMPULSE);
	std::cout << "Yo " << entity_->name() << " acabo de chocar con " << other->name() << "\n\n";
}

void Prueba::onCollisionStay(QuackEntity* other, Vector3D point)
{
	//std::cout << "Yo " << entity_->name() << " sigo chocando con " << other->name() << "\n\n";
}

void Prueba::onCollisionExit(QuackEntity* other, Vector3D point)
{
	std::cout << "Yo " << entity_->name() << " he dejado de chocar con " << other->name() << "\n\n";
}

