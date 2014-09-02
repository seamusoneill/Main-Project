/*! BaseObject header file*/
#pragma once
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <vector>

#include "FModManager.h"
#include "CONSTANT_VALUES.h"

class CONSTANT_VALUES;
using namespace std;
class BaseObject
{
protected:
	Ogre::Vector3 m_position;
	Ogre::SceneNode *m_object;
	Ogre::AxisAlignedBox m_bounding;
	Ogre::Quaternion m_orientation;
public:
	BaseObject(Ogre::SceneNode* node,Ogre::Vector3 position,Ogre::AxisAlignedBox bounding, int type);
	~BaseObject(void);

	virtual void update(Ogre::Real );
	Ogre::Vector3 lastAxis;
	int m_type;
	float m_radius;
	
	Ogre::SceneNode* getNode();
	Ogre::Vector3 getPosition();
	Ogre::AxisAlignedBox getBounding();
	Ogre::Quaternion getOrientation();
	
	void setOrientation(Ogre::Quaternion);
	void setPosition(Ogre::Vector3);
	
};