#include "Prueba.h"
#include "LuaManager.h"
#include "QuackEntity.h"
#include "Rigidbody.h"
#include "QuackEnginePro.h"
#include "SceneMng.h"
#include "QuackUI.h"
#include "InputManager.h"
#include "CEGUIQuack.h"

Prueba::Prueba(QuackEntity* e) : Component(e)
{

}

Prueba::~Prueba()
{
	delete valor2;
}

bool Prueba::init(luabridge::LuaRef parameterTable)
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

void PruebaCallBack() {
	std::string carga = "Scenes/scene2.lua";
	SceneMng::Instance()->loadScene(carga, "scene2");
}

void Prueba::start()
{
	InputManager::Instance()->captureMouse();
	InputManager::Instance()->setMouseVisibility(false);
	CallBacks::instance()->addMethod("PruebaCallBack", PruebaCallBack);
	//transform->lookAt({ 0,0,0 });
}

void Prueba::fixedUpdate()
{
	//std::cout << transform->rotation() << "\n";
	//entity_->getComponent<Rigidbody>()->addTorque({ 0,1,0 });
}

void Prueba::update()
{
	//if (entity_->getComponent<Rigidbody>())
	//	entity_->getComponent<Rigidbody>()->setAngularVelocity({ 0,1,0 });
	//if (InputManager::Instance()->getKey(SDL_SCANCODE_SPACE))
	//	std::cout << "Espacio mantenido\n";
	//if (InputManager::Instance()->getKeyDown(SDL_SCANCODE_L)) {
	//	std::cout << InputManager::Instance()->getMousePositionRelative().x << " , " << InputManager::Instance()->getMousePositionRelative().y << "\n";
	//}

	//Vector3D rot = { 0,InputManager::Instance()->getMouseAxis(Horizontal) ,InputManager::Instance()->getMouseAxis(Vertical) };

	//std::cout << "Horizontal: " << InputManager::Instance()->getMouseAxis(Horizontal) << " Vertical: " << InputManager::Instance()->getMouseAxis(Vertical) << "\n";

	//transform->Rotate(rot, true);

	//std::cout << "Horizontal: " << InputManager::Instance()->getMousePositionAbsolute().x << " Vertical: " << InputManager::Instance()->getMousePositionAbsolute().y <<"\n";

	//if (InputManager::Instance()->getKeyUp(SDL_SCANCODE_L)) {
	//	std::cout << "Espacio arriba\n";
	//}
	//scalealgo += QuackEnginePro::Instance()->time()->deltaTime();

	//transform->setScale({ abs(sin(scalealgo)),abs(sin(scalealgo)),abs(sin(scalealgo)) });
	/*transform->Translate(Vector3D(0, -1, 0) * QuackEnginePro::Instance()->time()->deltaTime());
	transform->Rotate(Vector3D(45, 0, 90) * QuackEnginePro::Instance()->time()->deltaTime());*/
	//if (transform->globalPosition().y < -10) {
	//	//transform->Rotate(Vector3D(0, 45, 0));
	//	transform->Translate(Vector3D(0, 10, 0), true);
	//	if (entity_->getComponent<Rigidbody>())
	//		entity_->getComponent<Rigidbody>()->clearForce();
	//}
	//std::cout << " Update de Prueba\n";

}

void Prueba::onCollisionEnter(QuackEntity* other, Vector3D point)
{
	//entity_->getComponent<Rigidbody>()->addForce(Vector3D(0, 10, 0), IMPULSE);

	/*std::string carga = "Scenes/" + valor3 + ".lua";
	SceneMng::Instance()->loadScene(carga, valor3);*/
	/*if (entity_->getComponent<Button>())
	{
		entity_->getComponent<Button>()->setText("AAA");
		entity_->getComponent<Button>()->setButtonEnable(true);
		entity_->getComponent<Button>()->setCallBackFunction("PruebaCallBack");
	}
	if (entity_->getComponent<Text>())
		entity_->getComponent<Text>()->setText("Me golpie con algo");
	if (entity_->getComponent<Image>())
		entity_->getComponent<Image>()->changeImage("virgolini");*/
	QuackEnginePro::Instance()->setFullScreen(true);
	std::cout << "Yo " << entity_->name() << " acabo de chocar con " << other->name() << "\n\n";
}

void Prueba::onCollisionEnter(QuackEntity* other, Vector3D point, Vector3D normal)
{
	std::cout <<entity_->name() << " con " << other->name() << " normal "<< normal << " en el punto " << point <<"\n";
}

void Prueba::onCollisionStay(QuackEntity* other, Vector3D point)
{
	//std::cout << "Yo " << entity_->name() << " sigo chocando con " << other->name() << "\n\n";
}

void Prueba::onCollisionExit(QuackEntity* other, Vector3D point)
{
	std::cout << "Yo " << entity_->name() << " he dejado de chocar con " << other->name() << "\n\n";
}

void Prueba::onTriggerEnter(QuackEntity* other, Vector3D point)
{
	std::cout << "Yo " << entity_->name() << " acabo de triggerear con " << other->name() << "\n\n";
}

void Prueba::onTriggerStay(QuackEntity* other, Vector3D point)
{
	std::cout << "Yo " << entity_->name() << " sigo triggereando con " << other->name() << "\n\n";
}

void Prueba::onTriggerExit(QuackEntity* other, Vector3D point)
{
	std::cout << "Yo " << entity_->name() << " he dejado de triggerear con " << other->name() << "\n\n";
}

