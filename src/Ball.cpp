#include "Ball.h"

Ball * Ball::it = 0;

Ball::Ball(Ogre::SceneNode* node, Ogre::Vector3 position,Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity)
	:MovingObject(node,position,bounding,velocity,CONSTANT_VALUES::BALL)
{
}

Ball::~Ball(){
}

void Ball::init(Ogre::SceneNode* node,Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity)
{
	m_object = node;
	m_position = position;
	m_bounding = bounding;
	m_velocity = velocity;
}

void Ball::update(Ogre::Real a)
{
	//Update code for ball

	MovingObject::update(a);
}

Ball* Ball::getBall()
{
	if (it ==0)
	{
		Ogre::AxisAlignedBox c;
		it = new Ball(NULL,Ogre::Vector3(0,0,0),c,Ogre::Vector3(0,0,0));
	}
	return it;
}