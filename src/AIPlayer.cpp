/*! Opponent class*/
#include "AIPlayer.h"	


AIPlayer * AIPlayer::enemy = 0;


AIPlayer::AIPlayer(Ogre::SceneNode* node,Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity)
	:MovingObject(node,position,bounding,velocity,CONSTANT_VALUES::PADDLE)
{
	m_speed = 28.25;
}	

AIPlayer::~AIPlayer()
{
}

void AIPlayer::init(Ogre::SceneNode* node, Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity) /*! Initialisation method for the enemy due to being a singleton*/
{
	m_object = node;
	m_position = position;
	m_bounding = bounding;
	m_velocity = velocity;
}

void AIPlayer::update(Ogre::Real a)
{
	Ogre::Vector3 bPos = Ball::getBall()->getPosition();
	
	if (bPos.x <= m_position.x)
	{
		m_velocity.x = -m_speed;
	}
	else if (bPos.x > m_position.x)
	{
		m_velocity.x = m_speed;
	}

	if (bPos.y <= m_position.y)
	{
		m_velocity.y = -m_speed;
	}
	else if (bPos.y > m_position.y)
	{
		m_velocity.y = m_speed;
	}

	MovingObject::update(a);
}
	
AIPlayer* AIPlayer::getAIPlayer()
{
	if(enemy == 0)
	{
		Ogre::AxisAlignedBox c;
		enemy = new AIPlayer(NULL, Ogre::Vector3(0,0,0),c,Ogre::Vector3(0,0,0));
	}
	return enemy;
}
