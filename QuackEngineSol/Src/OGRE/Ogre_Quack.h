#ifndef _OGRE_QUACK_
#define _OGRE_QUACK_

#include <Ogre.h>

class SDL_Window;

using namespace Ogre;

class Ogre_Quack {
private:

	Root* mRoot_;

	SceneManager* mSM_;

	RenderWindow* window_;

	SDL_Window* sdlWindow_;

	int screen_width_ = 1000;

	int screen_height_ = 1000;

	void setupWindow();

public:

	Ogre_Quack() {}

	~Ogre_Quack() {}

	RenderWindow* getWindow() { return window_; }

	Root* createRoot();

	void setupRoot();


};
#endif // !_OGRE_QUACK_
