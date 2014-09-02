#pragma once

#include "BaseApplication.h"
#include "BaseObject.h"
#include "CollisionReturn.h"

class CollisionManager
{
protected:
	static void CheckAxis(BaseObject* a, BaseObject *b, Ogre::Vector3 axis);
public:
	CollisionManager(void);
	~CollisionManager(void);
	static bool CheckCollision(BaseObject* obj1, BaseObject* obj2 );
	static CollisionReturn CheckSAT(BaseObject* a, BaseObject * b);
	static void CollisionMove(MovingObject * a, BaseObject* b, CollisionReturn cr);
	static void CollisionBounce(MovingObject * a, Ogre::Vector3 bVel, int type);
};