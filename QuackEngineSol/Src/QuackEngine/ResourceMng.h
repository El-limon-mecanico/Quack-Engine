#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include "OgreQuack.h"

class QUACK_ENGINE_PRO_API ResourceMng
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