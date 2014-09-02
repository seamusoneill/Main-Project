/*! Header for main project file */
#ifndef __RepeatProject_h_
#define __RepeatProject_h_

#include "BaseApplication.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif


class RepeatProject : public BaseApplication
{
public:
    RepeatProject(void);
    virtual ~RepeatProject(void);

protected:
    virtual void createScene(void);
	void createGamePanel();
};

#endif // #ifndef __RepeatProject_h_
