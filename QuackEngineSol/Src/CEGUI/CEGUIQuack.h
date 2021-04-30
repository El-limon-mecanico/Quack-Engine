#pragma once

#ifndef _CEGUI_QUACK_
#define _CEGUI_QUACK_

#include <string>

namespace Ogre {
	class RenderWindow;
	class RenderTarget;
	class Root;
}

namespace CEGUI 
{
	class OgreRenderer;
	class System;
	class Window;
	class GUIContext;
}

class CEGUIQuack
{
private:
	CEGUI::OgreRenderer* ogreRenderer_ = nullptr;
	CEGUI::System* ceguiSystem_ = nullptr;
	CEGUI::Window* window_ = nullptr;
	CEGUI::GUIContext* context_ = nullptr;

	void setUpResources();

	//std::map<std::string, FMOD::Sound*> sounds_;
	//std::map<std::string, FMOD::DSP*> dsp_;
public:
	
	CEGUIQuack(Ogre::RenderTarget* t) { init(t); };
	~CEGUIQuack() {};

	void init(Ogre::RenderTarget* target);
	void destroy();

	void draw();
	void loadScheme(std::string filename);
	void setFont(std::string filename);
	CEGUI::Window* createWidget(std::string type, std::string name = "");
};

#endif // !_CEGUI_QUACK_