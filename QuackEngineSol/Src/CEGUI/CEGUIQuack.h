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

	
	CEGUI::Window* window_ = nullptr;
	CEGUI::GUIContext* context_ = nullptr;

	void setUpResources();
	CEGUI::Window* createWidget(std::string type, std::string name, std::pair<float, float> pos, std::pair<float, float> size);
	
	
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
	
	void createButton(std::string name, std::string text, std::pair<float, float> pos, std::pair<float, float> size, std::function<void()>func);
	void createText(std::string name, std::string text, std::pair<float, float> pos, std::pair<float, float> size);
	void createImage(std::string name, std::string image, std::pair<float, float> pos, std::pair<float, float> size);
	
};

#endif // !_CEGUI_QUACK_