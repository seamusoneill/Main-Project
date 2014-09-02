/*! Class for basic solid objects*/
#include "BaseObject.h"

BaseObject::BaseObject(Ogre::SceneNode* node, Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, int type)
	:m_object(node),
	m_position(position),
	m_bounding(bounding),
	lastAxis(1,0,0),
	m_type(type)
{
	m_radius = m_bounding.getSize().length();
}

BaseObject::~BaseObject(void)
{
}

void BaseObject::update(Ogre::Real a)
{
	m_object->setPosition(m_position);
	m_bounding = m_object->_getWorldAABB();
}

/*! Getters*/
Ogre::SceneNode* BaseObject::getNode()
{
	return m_object;
}

Ogre::Vector3 BaseObject::getPosition()
{
	return m_position;
}

Ogre::AxisAlignedBox BaseObject::getBounding()
{
	return m_bounding;
}

Ogre::Quaternion BaseObject::getOrientation()
{
	return m_orientation;
}


/*! Setters */
void BaseObject::setPosition(Ogre::Vector3 position)
{
	m_position = position;
}

void BaseObject::setOrientation(Ogre::Quaternion myOrient)
{
	m_orientation = myOrient;
}