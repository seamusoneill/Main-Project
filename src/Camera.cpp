#include "Camera.h"

Camera* Camera::cam =0;

Camera::Camera()
{
}

Camera::~Camera(void)
{
}

void Camera::init(Ogre::Camera* cam, Ogre::SceneNode* node)
{
	mCamera = cam;
	mNode = node;
	posAround = Ogre::Vector3(0,50,100);
	around = mCamera->getPosition() - mNode->getPosition();
	minDist = 50;
	maxDist = 350;
	rotSpeed = 0.01;
	mouseRotSpeedMult = -5;
	scrlSpd = 10;
}

void Camera::update(Ogre::Real a)
{
	mCamera->setPosition(mNode->getPosition().x+around.x,mNode->getPosition().y + posAround.y,mNode->getPosition().z+around.z);mCamera->lookAt(mNode->getPosition());
}

void Camera::rotateMouse(const OIS::MouseEvent& evt){

	Ogre::Matrix3 mat;
	if( abs(evt.state.Z.rel)==0){
		if(abs(evt.state.X.rel) >= abs(evt.state.Y.rel))
		{
			if(evt.state.X.rel > 5)
			{
				if (around.x < 180)
				{
					mat = Ogre::Matrix3(cos(-(Ogre::Real)(rotSpeed*mouseRotSpeedMult)),0,sin(-(Ogre::Real)(rotSpeed*mouseRotSpeedMult)),
													0,1,0,
												-sin(-(Ogre::Real)(rotSpeed*mouseRotSpeedMult)),0,cos(-(Ogre::Real)(rotSpeed*mouseRotSpeedMult)));

			
					Ogre::Vector3 accel = mCamera->getPosition() - mNode->getPosition();
					accel = accel * mat;
					accel = accel + mNode->getPosition();
					mCamera->setPosition(accel);
					around = mCamera->getPosition() - mNode->getPosition();
				}
			}
			else if(evt.state.X.rel < -5)
			{
				if(around.x > -180)
				{
				mat = Ogre::Matrix3(cos((Ogre::Real)(rotSpeed*mouseRotSpeedMult)),0,sin((Ogre::Real)(rotSpeed*mouseRotSpeedMult)),
													0,1,0,
												-sin((Ogre::Real)(rotSpeed*mouseRotSpeedMult)),0,cos((Ogre::Real)(rotSpeed*mouseRotSpeedMult)));

			
				Ogre::Vector3 accel = mCamera->getPosition() - mNode->getPosition();
				accel = accel * mat;
				accel = accel + mNode->getPosition();
				mCamera->setPosition(accel);
				around = mCamera->getPosition() - mNode->getPosition();
				}
			}
		}
		else{
				if(evt.state.Y.rel < -5){
					if(posAround.y >-20)
						posAround.y -= 5;
				}
				else if(evt.state.Y.rel > 5){
					if(posAround.y < 100)
						posAround.y += 5;
			}
		}
	}
	if(evt.state.Z.rel > 0){
		dist--;
		Ogre::Vector3 temp = mCamera->getPosition() - mNode->getPosition();
		temp.normalise();
		temp = temp*scrlSpd;
		if(topDownDist() > minDist)
			mCamera->setPosition(mCamera->getPosition()-temp);

		around = mCamera->getPosition() - mNode->getPosition();
	}
	else if(evt.state.Z.rel < 0){
		dist++;
		Ogre::Vector3 temp = mCamera->getPosition() - mNode->getPosition();
		temp.normalise();
		temp = temp*scrlSpd;
		if(topDownDist() < maxDist)
			mCamera->setPosition(mCamera->getPosition()+temp);

		around = mCamera->getPosition() - mNode->getPosition();
	}

}

void Camera::changePos(Ogre::Vector3 vec){
	posAround = vec;
}

float Camera::topDownDist(){
	Ogre::Vector2 vec1 = Ogre::Vector2(mNode->getPosition().x, mNode->getPosition().z);
	Ogre::Vector2 vec2 = Ogre::Vector2(mCamera->getPosition().x, mCamera->getPosition().z);
	vec1 = vec1 - vec2;
	return vec1.length();
}

/*! Getters */
Camera* Camera::getCam(){
	if(cam == 0){
		cam = new Camera();
	}
	return cam;
}

Ogre::Vector3 Camera::getPosition()
{
	return mCamera->getPosition();
}

/*! Setters*/
void Camera::setPosition(Ogre::Vector3 vec)
{
	mCamera->setPosition(vec);
}