//#include <iostream>
#include "CEGUIQuack.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <OgreRenderWindow.h>
#include <assert.h>
#include <iostream>
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
	CEGUI::SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");

	//CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "_MasterRoot");
	myRoot->setUsingAutoRenderingSurface(true);	
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

	setUpResources();
}

void CEGUIQuack::destroy()
{
	CEGUI::System::getSingleton().destroyGUIContext(*context_);
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

CEGUI::Window* CEGUIQuack::createWidget(std::string type, std::string name, std::pair<float, float> pos, std::pair<float, float> size)
{
	CEGUI::Window* myImageWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	myImageWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(pos.first, 0.0), CEGUI::UDim(pos.second, 0.0)));
	myImageWindow->setSize(CEGUI::USize(CEGUI::UDim(0.0, size.first), CEGUI::UDim(0.0, size.second)));
	//myImageWindow->setProperty("Image", "TaharezLook/full_image");
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(myImageWindow);

	return myImageWindow;
}

void CEGUIQuack::createButton(std::string name, std::string text, std::pair<float, float> pos, std::pair<float, float> size)
{
	CEGUI::Window* newWidget = nullptr;
	try	{ newWidget = createWidget("WindowsLook/Button", name, pos, size);	}
	catch (std::exception e) { std::cout << "No se ha podido crear el boton: " << name << "\n"; }
	
	newWidget->setText(text);
}

void CEGUIQuack::createText(std::string name, std::string text, std::pair<float, float> pos, std::pair<float, float> size)
{
	CEGUI::Window* newWidget = nullptr;
	try { newWidget = createWidget("WindowsLook/StaticText", name, pos, size); }
	catch (std::exception e) { std::cout << "No se ha podido crear el texto: " << name << "\n"; }

	newWidget->setProperty("Text", text);
}

void CEGUIQuack::createImage(std::string name, std::string image, std::pair<float, float> pos, std::pair<float, float> size)
{
	CEGUI::Window* newWidget = nullptr;
	try { newWidget = createWidget("WindowsLook/StaticImage", name, pos, size); }
	catch (std::exception e) { std::cout << "No se ha podido crear la imagen: " << name << "\n"; }

	CEGUI::ImageManager::getSingleton().addFromImageFile(name, image);
	newWidget->setProperty("Image", name);
}


bool CEGUIQuack::render(double deltaTime)
{
	return false;
}
