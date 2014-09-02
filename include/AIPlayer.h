/*! Header file for opponent*/
#include "MovingObject.h"

class Ball;
class AIPlayer : public MovingObject
{
protected:
	static AIPlayer* enemy;
	Ogre::Vector3 bPos;
	float m_speed;
public:
	AIPlayer(Ogre::SceneNode* node,Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity);
	~AIPlayer();
	
	void init(Ogre::SceneNode* node, Ogre::Vector3 position, Ogre::AxisAlignedBox bounding, Ogre::Vector3 velocity); /*! Initialisation method for the enemy due to being a singleton*/
	void update(Ogre::Real a);
	
	static AIPlayer* getAIPlayer();
};

#include "Ball.h"