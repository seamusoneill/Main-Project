/*! Moving object class, adds velocity to BaseObject*/
#include "MovingObject.h"

MovingObject::MovingObject(Ogre::SceneNode* node, Ogre::Vector3 position,Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity, int type)
	:BaseObject(node,position,bounding,type),
	m_velocity(velocity)
{
	
}

MovingObject::~MovingObject(void)
{
}

void MovingObject::update(Ogre::Real a)
{
	m_position += m_velocity*a; 
	m_radius = m_bounding.getSize().length();
	BaseObject::update(a);
}

Ogre::Vector3 MovingObject::getVelocity()
{
	return m_velocity;
}

void MovingObject::setVelocity(Ogre::Vector3 velocity)
{
	 m_velocity = velocity;
}