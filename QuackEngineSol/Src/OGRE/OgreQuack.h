#ifndef _OGRE_QUACK_
#define _OGRE_QUACK_

#include <memory>
#include <string>

namespace Ogre {
	class Root;
	class SceneManager;
	class SceneNode;
	class RenderWindow;
	class FileSystemLayer;
	class Light;
	enum LightTypes;
}

class SDL_Window;

class OgreQuack {
private:

	static std::unique_ptr<OgreQuack> instance_;

	Ogre::Root* mRoot_;

	Ogre::SceneManager* mSM_;

	Ogre::RenderWindow* window_;

	SDL_Window* sdlWindow_;

	std::string name_;

	int screen_width_ = 1920;

	int screen_height_ = 1080;

	void setupWindow();

	void setupRoot();

public:

	static bool Init(std::string name);

	// devuelve puntero al singleton
	static OgreQuack* Instance();

	OgreQuack(std::string name) : name_(name) {
		setupRoot();
	}

	~OgreQuack();

	Ogre::RenderWindow* getWindow() { return window_; }

	Ogre::SceneManager* getSceneManager() { return mSM_; }

	Ogre::Root* getRoot() { return mRoot_; }

	SDL_Window* getSdlWindow() { return sdlWindow_; }

	Ogre::Light* createLigth(Ogre::LightTypes type = (Ogre::LightTypes)0);

	void setAmbientLight(float x, float y, float z);

	int getWindowH();
	int getWindowW();

	void setFullScreen(bool set);

	void setResolution(int width, int height);
};
#endif // !_OGRE_QUACK_
