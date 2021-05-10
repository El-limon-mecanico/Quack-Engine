//#include <iostream>
#include "CEGUIQuack.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <OgreRenderWindow.h>
#include <assert.h>
//#include <Ogre.h>
//#include <OgreRenderTarget.h>
//#include <CEGUI\ScriptModules\Lua\CEGUILua.h>

std::unique_ptr<CEGUIQuack>  CEGUIQuack::instance_;

bool CEGUIQuack::Init() {
	assert(instance_.get() == nullptr);
	instance_.reset(new CEGUIQuack());
	return instance_.get();
}

CEGUIQuack* CEGUIQuack::Instance() {
	assert(instance_.get() != nullptr);
	return instance_.get();
}

void CEGUIQuack::setUp(Ogre::RenderWindow* rWindow)
{
	ogreRenderer_ = &CEGUI::OgreRenderer::bootstrapSystem(*rWindow);
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

	//CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "_MasterRoot");
	myRoot->setUsingAutoRenderingSurface(true);	
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

	CEGUI::Window* myImageWindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", "PrettyWindow");
	myImageWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.5, 0)));
	myImageWindow->setSize(CEGUI::USize(CEGUI::UDim(0, 150), CEGUI::UDim(0, 50)));
	myImageWindow->setText("Y E S");
	//myImageWindow->setProperty("Image", "TaharezLook/full_image");
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(myImageWindow);
}

void CEGUIQuack::destroy()
{
	CEGUI::System::getSingleton().destroyGUIContext(*context_);
}

void CEGUIQuack::draw()
{
}

void CEGUIQuack::setUpResources()
{
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
}

void CEGUIQuack::loadScheme(std::string filename)
{
	CEGUI::SchemeManager::getSingleton().createFromFile(filename);
}

void CEGUIQuack::setFont(std::string filename)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont(filename);
}

CEGUI::Window* CEGUIQuack::createWidget(std::string type, std::string name)
{
	return nullptr;
}

bool CEGUIQuack::render(double deltaTime)
{
	return false;
}