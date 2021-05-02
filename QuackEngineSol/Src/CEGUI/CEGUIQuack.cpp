//#include <iostream>
#include "CEGUIQuack.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <CEGUI/RenderTarget.h>
//#include <Ogre.h>
//#include <OgreRenderTarget.h>
//#include <CEGUI\ScriptModules\Lua\CEGUILua.h>

void CEGUIQuack::init(Ogre::RenderTarget* target)
{
	if (ogreRenderer_ == nullptr)
	{
		ogreRenderer_ = &CEGUI::OgreRenderer::bootstrapSystem(*target);
		setUpResources();
	}

	context_ = &CEGUI::System::getSingleton().createGUIContext(ogreRenderer_->getDefaultRenderTarget());
	window_ = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	context_->setRootWindow(window_);
}

void CEGUIQuack::destroy()
{
	CEGUI::System::getSingleton().destroyGUIContext(*context_);
}

void CEGUIQuack::draw()
{
	ogreRenderer_->beginRendering();
	context_->draw();
	ogreRenderer_->endRendering();
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
	CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	window_->addChild(newWindow);
	newWindow->setText("Betis");
	return newWindow;
}