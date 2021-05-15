#include "ResourceMng.h"
#include <Ogre.h>
#include <iostream>
#include "OgreFileSystemLayer.h"

std::unique_ptr<ResourceMng> ResourceMng::instance_;

void ResourceMng::loadResources()
{
	Ogre::ConfigFile cf;

	Ogre::String resourcesPath = mFSLayer_->getConfigFilePath("resources.cfg");
	try {
		cf.load(resourcesPath);
	}
	catch (std::exception& e) {
		std::cout << "ERROR: no existe el archivo de recursos " << resourcesPath << ". No se han cargado algunos recursos.\n";
		return;
	}

	std::string mSolutionPath = resourcesPath;
	mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);
	mFSLayer_->setHomePath(mSolutionPath); //subdir definitivo
	mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);

	Ogre::String sec, type, arch;
	// go through all specified resource groups
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	arch = genLocs.front().archive->getName();
	type = genLocs.front().archive->getType();

	// Add locations for supported shader languages
	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
	}

	std::string mRTShaderLibPath_ = arch + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath_ + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath_ + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath_ + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath_ + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath_ + "/HLSL", type, sec);
	}

	// load located resources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

ResourceMng::ResourceMng(std::string assetsPath)
{
	mFSLayer_ = new Ogre::FileSystemLayer(assetsPath); //subdir temporal porque me obliga a poner uno
}

ResourceMng::~ResourceMng()
{
	delete mFSLayer_;	mFSLayer_ = nullptr;
}

bool ResourceMng::Init(std::string assetsPath)
{
	assert(instance_.get() == nullptr);
	instance_.reset(new ResourceMng(assetsPath));
	return instance_.get();
}

ResourceMng* ResourceMng::Instance()
{
	assert(instance_.get() != nullptr);
	return instance_.get();
}

void ResourceMng::setup()
{
	loadResources();
	//meter lo de lo shader por si acaso
}