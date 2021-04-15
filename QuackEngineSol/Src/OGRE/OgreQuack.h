#ifndef _OGRE_QUACK_
#define _OGRE_QUACK_


namespace Ogre {
	class Root;
	class SceneManager;
	class RenderWindow;
}

class SDL_Window;

using namespace Ogre;

class OgreQuack {
private:

	Ogre::Root* mRoot_;

	Ogre::SceneManager* mSM_;

	Ogre::RenderWindow* window_;

	SDL_Window* sdlWindow_;

	int screen_width_ = 1000;

	int screen_height_ = 1000;

	void setupWindow();

public:

	OgreQuack() {}

	~OgreQuack() {}

	Ogre::RenderWindow* getWindow() { return window_; }

	Ogre::SceneManager* getSceneManager() { return mSM_; }

	Ogre::Root* getRoot() { return mRoot_; }
	
	SDL_Window* getSdlWindow() { return sdlWindow_; }

	void createRoot();

	void setupRoot();


};
#endif // !_OGRE_QUACK_
