/*! Player class header file*/
#pragma once

#include "MovingObject.h"
#include <OISKeyboard.h>
#include "Camera.h" 

class Camera;
class Player:
	public MovingObject
{
protected:
	OIS::Keyboard* mKeyboard;
	static Player* me;

public:
	Player(Ogre::SceneNode* node,Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity);
	~Player(void);

	void init(Ogre::SceneNode* node, Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity, OIS::Keyboard* Keyboard); /*! Initialisation method for the player due to being a singleton*/
	void update(Ogre::Real a);

	void moveLeft(Ogre::Real a);
	void moveRight(Ogre::Real a);
	void moveUp(Ogre::Real a);
	void moveDown(Ogre::Real a);

	
	
	static Player* getPlayer();
};
