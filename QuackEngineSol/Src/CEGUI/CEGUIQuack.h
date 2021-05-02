#ifndef _CEGUI_QUACK_
#define _CEGUI_QUACK_

#include <string>
#include <memory>

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
	class WindowManager;
}

class CEGUIQuack
{
private:

	static std::unique_ptr<CEGUIQuack> instance_;

	CEGUI::OgreRenderer* ogreRenderer_ = nullptr;
	CEGUI::System* ceguiSystem_ = nullptr;
	CEGUI::Window* window_ = nullptr;
	CEGUI::WindowManager* windowManager_ = nullptr;
	CEGUI::GUIContext* context_ = nullptr;

	void setUpResources();

	//std::map<std::string, FMOD::Sound*> sounds_;
	//std::map<std::string, FMOD::DSP*> dsp_;
public:
	
	static bool Init();

	static CEGUIQuack* Instance();

	CEGUIQuack() {};
	~CEGUIQuack() {};

	void setUp(Ogre::RenderTarget* target);
	void destroy();

	bool render(double d);
	void draw();
	void loadScheme(std::string filename);
	void setFont(std::string filename);
	CEGUI::Window* createWidget(std::string type, std::string name = "");
};

#endif // !_CEGUI_QUACK_