#include "MovingObject.h"
#ifndef __Ball_h_
#define __Ball_h_
class Ball : 
	public MovingObject
{
protected:
	static Ball* it;

public:
	Ball(Ogre::SceneNode* node,Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity);
	~Ball();
	
	void init(Ogre::SceneNode* node,Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity); /*! Initialisation method for ball due to being a singleton*/
	void update(Ogre::Real a);

	static Ball* getBall();
};
#endif