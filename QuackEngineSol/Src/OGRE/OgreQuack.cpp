#include "OgreQuack.h"
#include "RTShaderSystem/OgreShaderGenerator.h"
#include <Ogre.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#include <assert.h>
#include <iostream>
#include <Windows.h>

using namespace Ogre;

std::unique_ptr<OgreQuack>  OgreQuack::instance_;

// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES (no, no?)
bool OgreQuack::Init(std::string name) {
	assert(instance_.get() == nullptr);
	instance_.reset(new OgreQuack(name));
	return instance_.get();
}


OgreQuack* OgreQuack::Instance() {
	assert(instance_.get() != nullptr);
	return instance_.get();
}

OgreQuack::~OgreQuack() {
	delete window_;		window_ = nullptr;
	delete mSM_;		mSM_ = nullptr;
	delete sdlWindow_;	sdlWindow_ = nullptr;
	delete mRoot_;		mRoot_ = nullptr;
}

void OgreQuack::setupRoot()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	mRoot_ = new Root();

	mRoot_->showConfigDialog(NULL);

	mRoot_->initialise(false);

	setupWindow();

	mSM_ = mRoot_->createSceneManager();

	mSM_->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
		shadergen->addSceneManager(mSM_);
	}

	setAmbientLight(.2, .2, .2);
}

void OgreQuack::setupWindow()
{
	RECT rect;
	HWND hd = GetDesktopWindow();
	GetClientRect(hd, &rect);
	screen_width_ = (rect.right - rect.left) * 0.75;
	screen_height_ = (rect.bottom - rect.top) * 0.75;

	if (!SDL_WasInit(SDL_INIT_VIDEO))
		SDL_InitSubSystem(SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI; //SDL_WINDOW_RESIZABLE

	sdlWindow_ = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width_, screen_height_, flags);

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

	window_ = mRoot_->createRenderWindow(name_.c_str(), screen_width_, screen_height_, false, &params);

	SDL_SetWindowGrab(sdlWindow_, SDL_bool(false));
	SDL_ShowCursor(false);
}

Light* OgreQuack::createLigth(LightTypes type)
{
	Light* light = mSM_->createLight();
	light->setType((Light::LightTypes)type);

	return light;
}

void OgreQuack::setAmbientLight(float x, float y, float z)
{
	mSM_->setAmbientLight(Ogre::ColourValue(x, y, z));
}

int OgreQuack::getWindowH() {
	return window_->getHeight();
}

int OgreQuack::getWindowW() {

	return window_->getWidth();
}

void OgreQuack::setFullScreen(bool set)
{
	float newWidth, newHeight;
	if (set) {
		RECT rect;
		HWND hd = GetDesktopWindow();
		GetClientRect(hd, &rect);
		int zoom = GetDpiForWindow(hd);
		double dpi = 0;
		switch (zoom) {
		case 96:
			dpi = 1;
			std::cout << "100%" << std::endl;
			break;
		case 120:
			dpi = 1.25;
			std::cout << "125%" << std::endl;
			break;
		case 144:
			dpi = 1.5;
			std::cout << "150%" << std::endl;
			break;
		case 192:
			dpi = 2;
			std::cout << "200%" << std::endl;
			break;
		default:
			std::cout << "error" << std::endl;
			break;
		}
		newWidth = (rect.right - rect.left) * dpi;
		newHeight = (rect.bottom - rect.top) * dpi;
	}
	else {
		newWidth = screen_width_;
		newHeight = screen_height_;
	}
	std::cout << newWidth << " " << newHeight << std::endl;
	SDL_SetWindowSize(sdlWindow_, newWidth, newHeight);
	SDL_SetWindowFullscreen(sdlWindow_, set ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE);
	window_->windowMovedOrResized();
}

void OgreQuack::setResolution(int width, int height)
{
	screen_width_ = width;
	screen_height_ = height;
	SDL_SetWindowSize(sdlWindow_, width, height);
	window_->windowMovedOrResized();
}
