#pragma once
#include "BaseApplication.h"
#include "BaseObject.h"

class CollisionReturn{
public:
	CollisionReturn(bool boolean, double distance,Ogre::Vector3 axis):m_boolean(boolean),m_distance(distance),m_axis(axis){}
	CollisionReturn(bool boolean, double distance, Ogre::AxisAlignedBox box):m_boolean(boolean),m_distance(distance),m_box(box){}
	bool m_boolean;
	double m_distance;
	Ogre::Vector3 m_axis;
	Ogre::AxisAlignedBox m_box;
};