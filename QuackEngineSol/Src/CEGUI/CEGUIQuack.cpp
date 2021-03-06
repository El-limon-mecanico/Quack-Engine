#include "CEGUIQuack.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <OgreRenderWindow.h>
#include <assert.h>
#include <iostream>

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

	myRoot_ = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "_MasterRoot");
	myRoot_->setUsingAutoRenderingSurface(true);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot_);

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

void CEGUIQuack::addWidget(CEGUI::Window* window)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(window);
}

void CEGUIQuack::removeWidget(CEGUI::Window* window)
{
	myRoot_->removeChild(window);
}

void CEGUIQuack::destroyWidget(CEGUI::Window* window)
{
	removeWidget(window);
	CEGUI::WindowManager::getSingleton().destroyWindow(window);
}

void CEGUIQuack::setMouseVisibility(bool visible)
{
	if(visible) CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
	else CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
}

void CEGUIQuack::resizeWindow(int width, int height)
{
	CEGUI::Sizef size = CEGUI::Sizef(width, height);
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(size);
}


bool CEGUIQuack::render(double deltaTime)
{
	return false;
}
