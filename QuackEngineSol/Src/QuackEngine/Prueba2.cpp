#include "Prueba2.h"
#include "LuaManager.h"
#include "QuackEntity.h"
#include "Rigidbody.h"
#include "QuackEnginePro.h"
#include "QuackUI.h"
#include "SceneMng.h"
#include "InputManager.h"
#include "AudioSource.h"

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

void pruebaPop() {
	//SceneMng::Instance()->popCurrentScene();
	//SceneMng::Instance()->pushNewScene("Scenes/scene1.lua", "scene1");
	SceneMng::Instance()->popCurrentScene();
}

void Prueba2::start()
{
	if (entity_->getComponent<Button>())
		entity_->getComponent<Button>()->setCallBackFunction(pruebaPop);
	if (entity_->getComponent<AudioSource>())
		entity_->getComponent<AudioSource>()->play();
}


void Prueba2::update()
{
	//SceneMng::Instance()->popCurrentScene();
	Vector3D rot = { -InputManager::Instance()->getMouseAxis(Vertical),-InputManager::Instance()->getMouseAxis(Horizontal) ,0 };

	//std::cout << "Horizontal: " << InputManager::Instance()->getMouseAxis(Horizontal) << " Vertical: " << InputManager::Instance()->getMouseAxis(Vertical) << "\n";

	transform->Rotate({ rot.x,rot.y,0 });
	
	Vector3D mov = Vector3D(InputManager::Instance()->getAxis(Horizontal), 0, -InputManager::Instance()->getAxis(Vertical));
	if (InputManager::Instance()->getKey(SDL_SCANCODE_SPACE)) mov.y = 1;
	if (InputManager::Instance()->getKey(SDL_SCANCODE_LSHIFT)) mov.y = -1;
	

	transform->Translate(mov * QuackEnginePro::Instance()->time()->deltaTime() * 5);

	//algo += QuackEnginePro::Instance()->time_()->deltaTime();
	//if (entity_->getComponent<Text>())
	//	entity_->getComponent<Text>()->setText(std::to_string(algo));
}
