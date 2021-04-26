#pragma once
#include <string>
#include <vector>
#include "QuackEntity.h"

class Scene
{
private:
	std::vector<QuackEntity*> entities_;

	bool createEntity(const std::string& fileName);

public:
	Scene(const std::string& file, const std::string& name);
	~Scene();

	void update();
};
