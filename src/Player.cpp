/*! Player class*/
#include "Player.h"

Player * Player::me = 0;

Player::Player(Ogre::SceneNode* node,Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity)
	:MovingObject(node,position,bounding,velocity,CONSTANT_VALUES::PADDLE)
{
}

Player::~Player()
{
}

void Player::init(Ogre::SceneNode* node,Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity,OIS::Keyboard* keyboard)
{
	m_object = node;
	m_position = position;
	m_bounding = bounding;
	m_velocity = velocity;
	mKeyboard = keyboard;
}

void Player::update(Ogre::Real a)
{
	if (mKeyboard->isKeyDown(OIS::KC_D))
	{
		moveRight(a);
	}
	else if(mKeyboard->isKeyDown(OIS::KC_A))
	{
		moveLeft(a);
	}
	else
	{
		m_velocity.x = 0;
	}

	if(mKeyboard->isKeyDown(OIS::KC_W)) 
	{
		moveUp(a);
	}
	else if (mKeyboard->isKeyDown(OIS::KC_S) )
	{
		moveDown(a);
	}
	else
	{
		m_velocity.y = 0;
	}


	MovingObject::update(a);
}

void Player::moveLeft(Ogre::Real a)
{
	m_velocity.x = 40;
}

void Player::moveRight(Ogre::Real a)
{
	
	m_velocity.x = -40;
}

void Player::moveUp(Ogre::Real a)
{
	m_velocity.y = 40;
}

void Player::moveDown(Ogre::Real a)
{
	m_velocity.y = -40;
}

Player* Player::getPlayer()
{
	if(me == 0)
	{
		Ogre::AxisAlignedBox c;
		me = new Player(NULL, Ogre::Vector3(0,0,0),c,Ogre::Vector3(0,0,0));
	}
	return me;
}