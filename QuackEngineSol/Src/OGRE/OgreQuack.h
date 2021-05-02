#ifndef _OGRE_QUACK_
#define _OGRE_QUACK_

#include <memory>

namespace Ogre {
	class Root;
	class SceneManager;
	class RenderWindow;
	class FileSystemLayer;
}

class SDL_Window;

using namespace Ogre;

class OgreQuack {
private:

	static std::unique_ptr<OgreQuack> instance_;

	Ogre::Root* mRoot_;

	Ogre::SceneManager* mSM_;

	Ogre::RenderWindow* window_;

	Ogre::FileSystemLayer* mFSLayer_;

	SDL_Window* sdlWindow_;

	int screen_width_ = 1000;

	int screen_height_ = 1000;

	void setupWindow();

public:

	static bool Init();

	// devuelve puntero al singleton
	static OgreQuack* Instance();

	OgreQuack() {}

	~OgreQuack();

	Ogre::RenderWindow* getWindow() { return window_; }

	Ogre::SceneManager* getSceneManager() { return mSM_; }

	Ogre::Root* getRoot() { return mRoot_; }
	
	SDL_Window* getSdlWindow() { return sdlWindow_; }

	void createRoot();

	void setupRoot();

	void loadResources();
};
#endif // !_OGRE_QUACK_
