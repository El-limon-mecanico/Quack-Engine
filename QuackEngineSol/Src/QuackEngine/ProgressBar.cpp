#include "ProgressBar.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

ProgressBar::ProgressBar(std::string name, bool active, std::pair<float, float> pos, std::pair<float, float> size, std::string style)
{
	UIElement::init(pos, size, active, name, style);
	bar_ = static_cast<CEGUI::ProgressBar*>(element_);
}

bool ProgressBar::init(luabridge::LuaRef parameterTable)
{

	UIElement::init(parameterTable);

	bool correct = true;
	float startProgress = 0;

	correct &= readVariable<float>(parameterTable, "Progress", &startProgress);

	if (!correct) return false;

	bar_ = static_cast<CEGUI::ProgressBar*>(element_);

	bar_->setProgress(startProgress);

	return true;
}

void ProgressBar::setProgress(float progress)
{
	bar_->setProgress(progress);
}

void ProgressBar::addProgress(float progress)
{
	bar_->adjustProgress(progress);
}

float ProgressBar::getProgress()
{
	return bar_->getProgress();
}
