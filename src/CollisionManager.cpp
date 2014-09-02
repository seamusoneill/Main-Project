/*! Class to check if objects collide*/
#include "CollisionManager.h"

CollisionManager::CollisionManager(void)
{
}

CollisionManager::~CollisionManager(void)
{
}

static Ogre::Vector3 edgeA,edgeB, axis;
static CollisionReturn colReturn(true,LONG_MAX,Ogre::Vector3());
static int sideA,sideB,i;
static Ogre::Vector3 edgeOne, edgeTwo;
static double temporaryValue, minA, maxA, minB, maxB;
static CollisionReturn colCheckReturn(true,0,Ogre::Vector3());

CollisionReturn CollisionManager::CheckSAT(BaseObject* a, BaseObject* b)
{ 
	colReturn = CollisionReturn(true,LONG_MAX,Ogre::AxisAlignedBox(0,0,0,0,0,0));

	if(a->getNode()->_getWorldAABB().contains(b->getNode()->_getWorldAABB())||a->getNode()->_getWorldAABB().intersects(b->getNode()->_getWorldAABB()))
	{
		colReturn.m_boolean = true;
		colReturn.m_box = a->getNode()->_getWorldAABB().intersection(b->getNode()->_getWorldAABB());
	}
	else
	{
		colReturn.m_boolean = false;
	}
	return colReturn;
}

void CollisionManager::CollisionMove(MovingObject* a, BaseObject* b, CollisionReturn cr)
{
	Ogre::Vector3 move = Ogre::Vector3(INT32_MAX,INT32_MAX,INT32_MAX);
	if(a->getPosition().y < b->getPosition().y)
	{
		move.y = -(cr.m_box.getMaximum().y-cr.m_box.getMinimum().y);
	}
	else
	{
		move.y = (cr.m_box.getMaximum().y-cr.m_box.getMinimum().y);
	}
	if(a->getPosition().x < b->getPosition().x)
	{
		move.x = -(cr.m_box.getMaximum().x-cr.m_box.getMinimum().x);
	}
	else
	{
		move.x = (cr.m_box.getMaximum().x-cr.m_box.getMinimum().x);
	}
	if(a->getPosition().z < b->getPosition().z)
	{
		move.z = -(cr.m_box.getMaximum().z-cr.m_box.getMinimum().z);
	}
	else
	{
		move.z = (cr.m_box.getMaximum().z-cr.m_box.getMinimum().z);
	}
	move.x = ((move.x/abs(move.x))*(abs(move.x)+0.1f));
	move.y = ((move.y/abs(move.y))*(abs(move.y)+0.1f));
	move.z = ((move.z/abs(move.z))*(abs(move.z)+0.1f));
	move += a->getPosition();
	bool ridX = false;
	bool ridZ = false;
	bool ridY = false;
	if(abs(move.y-a->getPosition().y) < abs(move.z-a->getPosition().z))
	{
		ridZ = true;
	}
	else
	{
		ridY = true;
	}
	if(abs(move.y-a->getPosition().y) < abs(move.x-a->getPosition().x))
	{
		ridX = true;
	}
	else
	{
		ridY = true;
	}
	if(abs(move.x-a->getPosition().x) < abs(move.z-a->getPosition().z))
	{
		ridZ = true;
	}
	else
	{
		ridX = true;
	}
	if(ridX)
		move.x = a->getPosition().x;
	if(ridZ)
		move.z = a->getPosition().z;
	if(ridY)
		move.y = a->getPosition().y;
	a->setPosition(move);
	a->setVelocity(Ogre::Vector3(0,0,0));
}

void CollisionManager::CollisionBounce(MovingObject* a, Ogre::Vector3 bVel, int type)
{	
	if (type == CONSTANT_VALUES::FLOOR)
	{
		a->setVelocity(Ogre::Vector3(bVel.x,bVel.y * -1,bVel.z));
	}
	else if(type == CONSTANT_VALUES::WALL)
	{
		a->setVelocity(Ogre::Vector3(bVel.x * -1,bVel.y,bVel.z));
	}
	else if(type == CONSTANT_VALUES::PADDLE)
	{
		Ogre::Vector3 y = a->getPosition();
		a->setVelocity(Ogre::Vector3(bVel.x,bVel.y,bVel.z * -1));
	}
}