#include "OgreQuack.h"
#include "RTShaderSystem/OgreShaderGenerator.h"
#include <Ogre.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#include <assert.h>
#include <iostream>

std::unique_ptr<OgreQuack>  OgreQuack::instance_;

// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES
bool OgreQuack::Init() {
	assert(instance_.get() == nullptr);
	instance_.reset(new OgreQuack());
	return instance_.get();
}


OgreQuack* OgreQuack::Instance() {
	assert(instance_.get() != nullptr);
	return instance_.get();
}

OgreQuack::~OgreQuack() {
	delete window_;		window_ = nullptr;
	delete mSM_;		mSM_	= nullptr;
	delete sdlWindow_;	sdlWindow_ = nullptr;
	delete mRoot_;		mRoot_	= nullptr;
	delete mFSLayer_;	mFSLayer_ = nullptr;
}


void OgreQuack::createRoot()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	mRoot_ = new Root();
}

void OgreQuack::setupRoot()
{
	mRoot_->showConfigDialog(NULL);

	mRoot_->initialise(false);

	setupWindow();

	mSM_ = mRoot_->createSceneManager();

	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
		shadergen->addSceneManager(mSM_);
	}

	//Ogre::Camera* mCamera;

	//mCamera = mSM_->createCamera("MainCam");

	//mCamera->setNearClipDistance(1);
	//mCamera->setFarClipDistance(100000);
	//mCamera->setAutoAspectRatio(true);


	//Ogre::SceneNode* mNodeCamera = mSM_->getRootSceneNode()->createChildSceneNode();
	//mNodeCamera->attachObject(mCamera);

	//mNodeCamera->setPosition(1000, 1000, 1000);
	//mNodeCamera->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	//Ogre::Viewport* vp = window_->addViewport(mCamera);

	//vp->setBackgroundColour(Ogre::ColourValue(1, 1, 0));

	//mCamera->setAspectRatio(
	//	Ogre::Real(vp->getActualWidth()) /
	//	Ogre::Real(vp->getActualHeight()));

	mSM_->setAmbientLight(Ogre::ColourValue(.2, .2, .2));

	Light* luz = mSM_->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1, 1, 1);

	SceneNode* mLightNode = mSM_->getRootSceneNode()->createChildSceneNode("nLuz");

	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(1, -1, -1));  //vec3.normalise();
}

void OgreQuack::loadResources()
{
	mFSLayer_ = new Ogre::FileSystemLayer("./Assets/"); //subdir temporal

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

void OgreQuack::setupWindow()
{
	if (!SDL_WasInit(SDL_INIT_VIDEO))
		SDL_InitSubSystem(SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI; //SDL_WINDOW_RESIZABLE

	sdlWindow_ = SDL_CreateWindow("ventana to guapa", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width_, screen_height_, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (SDL_GetWindowWMInfo(sdlWindow_, &wmInfo) == SDL_FALSE) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Couldn't get WM Info! (SDL2)",
			"BaseApplication::setup");
	}

	Ogre::NameValuePairList params;

	params["vsync"] = true;

	params["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	window_ = mRoot_->createRenderWindow("ventana to guapa", screen_width_, screen_height_, false, &params);

	SDL_SetWindowGrab(sdlWindow_, SDL_bool(false));
	SDL_ShowCursor(false);
}