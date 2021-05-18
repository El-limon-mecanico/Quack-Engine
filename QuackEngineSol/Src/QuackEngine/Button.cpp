#include "Button.h"
#include <CEGUIQuack.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "CallBacks.h"

Button::~Button()
{

}

bool Button::init(luabridge::LuaRef parameterTable)
{
	LuaRef pos = readVariable<LuaRef>(parameterTable, "Position");
	LuaRef size = readVariable<LuaRef>(parameterTable, "Size");

	button_ = CEGUIQuack::Instance()->createWidget(readVariable<std::string>(parameterTable, "Style"),
		readVariable<std::string>(parameterTable, "Name"));

	setPosition(pos[1], pos[2]);

	setSize(size[1], size[2]);

	setText(readVariable<std::string>(parameterTable, "Text"));

	setCallBackFunction(CallBacks::instance()->getMethod(readVariable<std::string>(parameterTable, "CallBackFunction")));

	active_ = readVariable<bool>(parameterTable, "Active");
	visible_ = readVariable<bool>(parameterTable, "Visible");

	return true;
}

void Button::onEnable()
{
	button_->setVisible(visible_);
	button_->setEnabled(active_);
}

void Button::onDisable()
{
	button_->setVisible(false);
	button_->setEnabled(false);
}

void Button::setActive(bool active)
{
	button_->setEnabled(active);
}

void Button::setText(std::string text)
{
	button_->setText(text);
}

void Button::setTextFont(std::string font)
{
	button_->setFont(font);
}

void Button::setCallBackFunction(std::string callBackName)
{
	setCallBackFunction(CallBacks::instance()->getMethod(callBackName));
}

void Button::setCallBackFunction(std::function<void()> callBack)
{
	button_->removeAllEvents();
	button_->subscribeEvent(CEGUI::PushButton::EventClicked, callBack);
}

void Button::setSize(float x, float y)
{
	size_ = { x,y };
	CEGUI::UDim x_ = CEGUI::UDim(0, x);
	CEGUI::UDim y_ = CEGUI::UDim(0, y);
	button_->setSize({ x_,y_ });
}

void Button::setPosition(float x, float y)
{
	position_ = { x,y };
	CEGUI::UDim x_ = CEGUI::UDim(x, 0);
	CEGUI::UDim y_ = CEGUI::UDim(y, 0);

	button_->setPosition({ x_,y_ });
}
