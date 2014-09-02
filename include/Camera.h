/*! Camera class header*/
#pragma once

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OISMouse.h>
#include <math.h>

class Camera
{
public:
	Camera();
	~Camera(void);
	void init(Ogre::Camera * cam, Ogre::SceneNode* node);
	void update(Ogre::Real);
	
	void rotateMouse(const OIS::MouseEvent& evt);
	void changePos(Ogre::Vector3 vec);
	float topDownDist();

	Ogre::Camera* mCamera;
	/*! Getters */
	Ogre::SceneNode* getNode();
	Ogre::Vector3 getPosition();
	static Camera* getCam();

	/*! Setters*/
	void setPosition(Ogre::Vector3 vec);

private:
	
	Ogre::SceneNode* mNode;
	Ogre::Vector3 posAround;
	OIS::Keyboard* mKeyboard;
	int minDist; /*! Closest the camera gets to the target*/
	int maxDist;/*! Furthest away the camera gets from the target*/
	Ogre::Vector3 around; /*! Where the camera is in relation to the target*/
	float dist;/*! Distance from the target*/
	static Camera*cam;
	double rotSpeed;
	int mouseRotSpeedMult; /*! To controll the speed the mouse rotates at*/
	int scrlSpd; /*! Speeed to scroll in with mouse wheel*/
};