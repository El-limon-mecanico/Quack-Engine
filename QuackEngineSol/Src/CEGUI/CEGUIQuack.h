#pragma once

#ifndef _CEGUI_QUACK_
#define _CEGUI_QUACK_

namespace ogre
{
	class OgreRenderer;
}

class CEGUIQuack
{
private:
	ogre::OgreRenderer* ogreRenderer_;
	CEGUI::System* ceguiSystem_;

public:

};

#endif // !_CEGUI_QUACK_