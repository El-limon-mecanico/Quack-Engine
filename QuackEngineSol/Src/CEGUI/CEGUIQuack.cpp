//#include <iostream>
#include "CEGUIQuack.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <CEGUI/RenderTarget.h>
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

void CEGUIQuack::setUp(Ogre::RenderTarget* target)
{
	if (ogreRenderer_ == nullptr)
	{
		ogreRenderer_ = &CEGUI::OgreRenderer::bootstrapSystem(*target);
		setUpResources();
	}

	ceguiSystem_ = &CEGUI::System::getSingleton();
	context_ = &ceguiSystem_->createGUIContext(ogreRenderer_->getDefaultRenderTarget());
	windowManager_ = &CEGUI::WindowManager::getSingleton();
	window_ = windowManager_->createWindow("DefaultWindow", "root");
	ceguiSystem_->getDefaultGUIContext().setRootWindow(window_);
	//context_->setRootWindow(window_);
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
	//window_->addChild(newWindow);
	newWindow->setText("Betis");
	return newWindow;
}

bool CEGUIQuack::render(double deltaTime)
{
	ceguiSystem_->getDefaultGUIContext().injectTimePulse(deltaTime);
	ceguiSystem_->renderAllGUIContexts();

	return false;
}