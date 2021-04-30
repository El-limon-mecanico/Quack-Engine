//#include <iostream>
#include "CEGUIQuack.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <CEGUI/RenderTarget.h>
#include <Ogre.h>
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
	CEGUI::DefaultResourceProvider* resourceProvider = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
	//resourceProvider->setResourceGroupDirectory("imagesets", "Assets/UI/imagesets/");
	//resourceProvider->setResourceGroupDirectory("schemes", "Assets/UI/schemes/");
	//resourceProvider->setResourceGroupDirectory("fonts", "Assets/UI/fonts/");
	//resourceProvider->setResourceGroupDirectory("layouts", "Assets/UI/layouts/");
	//resourceProvider->setResourceGroupDirectory("looknfeels", "Assets/UI/looknfeels/");

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("layouts");
	CEGUI::WindowManager::setDefaultResourceGroup("looknfeels");
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
	return newWindow;
}