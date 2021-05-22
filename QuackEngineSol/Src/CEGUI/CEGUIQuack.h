#ifndef _CEGUI_QUACK_
#define _CEGUI_QUACK_

#include <functional>
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
	class SchemeManager;
	class FontManager;
	class EventArgs;
}

class CEGUIQuack
{
private:

	static std::unique_ptr<CEGUIQuack> instance_;

	CEGUI::OgreRenderer* ogreRenderer_ = nullptr;
	
	CEGUI::System* ceguiSystem_ = nullptr;
	CEGUI::WindowManager* windowManager_ = nullptr;
	CEGUI::SchemeManager* scheme_manager_ = nullptr;
	CEGUI::FontManager* fontManager_ = nullptr;

	
	CEGUI::Window* myRoot_ = nullptr;
	CEGUI::GUIContext* context_ = nullptr;

	void setUpResources();
	
	
public:
	
	static bool Init();

	static CEGUIQuack* Instance();

	CEGUIQuack() {};
	~CEGUIQuack() {};

	void setUp(Ogre::RenderWindow* rWindow);
	void destroy();

	bool render(double d);
	void loadScheme(std::string filename);
	void setFont(std::string filename);
	
	CEGUI::Window* createWidget(std::string type, std::string name, std::pair<float, float> pos = { 0,0 }, std::pair<float, float> size = {100,100});
	
	void removeWidget(CEGUI::Window* window);
	
	void setMouseVisibility(bool visible);

	void resizeWindow(int width, int height);
};

#endif // !_CEGUI_QUACK_