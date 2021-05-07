#pragma once

#include "OgreQuack.h"

class ResourceMng
{
private:
	static std::unique_ptr<ResourceMng> instance_;
	Ogre::FileSystemLayer* mFSLayer_;

	void loadResources();
	//bool initRTShaderSystem();
	//void wipeRTShaderSystem();

public:
	ResourceMng();
	~ResourceMng();

	static bool Init();
	static ResourceMng* Instance();

	void setup();
};