/*! BaseApplication Class. Updates all objects*/
#include "BaseApplication.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#include "FModManager.h"
#endif


//-------------------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
    : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mCameraMan(0),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
	check(true),
	score(0,0)
{
	result = FModManager::System()->createStream("media/Song.mp3", FMOD_LOOP_NORMAL,0, &sound);
	FModManager::System()->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
	pauseStream = false;
	result = channel->setVolume(0.5f);

	resultHit = FModManager::System()->createSound("media/hit.wav",FMOD_3D, 0, &soundHit);
	resultBounce = FModManager::System()->createSound("media/bounce.wav",FMOD_3D, 0, &soundBounce);
	resultScore = FModManager::System()->createSound("media/score.wav",FMOD_3D, 0, &soundScore);

}

//-------------------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
    if (mCameraMan) delete mCameraMan;

    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
}
/*! Creates the walls*/
void BaseApplication::CreateWall(Ogre::Vector3 position,Ogre::Vector3 scale, Ogre::String str, int type)
{
	Ogre::Entity *cube = mSceneMgr->createEntity("cube"+Ogre::StringConverter::toString(objects.size()), "cube.mesh");
	cube->setMaterialName("Examples/" + str);
	Ogre::SceneNode *cubeNode = mSceneMgr->createSceneNode("object"+Ogre::StringConverter::toString(objects.size()));
	mSceneMgr->getRootSceneNode()->addChild(cubeNode);
	cubeNode->attachObject(cube);
	cube->setCastShadows(true);
	float cubeModelLength = 100;
	cubeNode->scale(scale.x/cubeModelLength, scale.y/cubeModelLength, scale.z/cubeModelLength);
	cubeNode-> setPosition(position);
	Ogre::AxisAlignedBox bounding = Ogre::AxisAlignedBox(-scale.x/2 + position.x,-scale.y/2+ position.y,-scale.z/2+ position.z
		,scale.x/2+ position.x,scale.y/2+ position.y,scale.z/2+ position.z);
	
	objects.push_back(new BaseObject(cubeNode,Ogre::Vector3(position),bounding,type));
}
/*! Creates the ball*/
void BaseApplication::CreateBall(Ogre::Vector3 position, Ogre::Vector3 scale)
{
	Ogre::Entity *ball = mSceneMgr->createEntity("ball","sphere.mesh");
	ball->setMaterialName("Examples/Blue");
	Ogre::SceneNode* ballNode = mSceneMgr->createSceneNode("ballNode");
	mSceneMgr->getRootSceneNode()->addChild(ballNode);
	ballNode->attachObject(ball);
	ball->setCastShadows(true);
	float modelSphereRadius = 500;
	ballNode->scale(scale.x/modelSphereRadius,scale.y/modelSphereRadius,scale.z/modelSphereRadius);
	ballNode->setPosition(position);
	Ogre::AxisAlignedBox bounding = Ogre::AxisAlignedBox(-scale.x/2 + position.x,-scale.y/2+ position.y,-scale.z/2+ position.z
		,scale.x/2+ position.x,scale.y/2+ position.y,scale.z/2+ position.z);
	Ball *b = Ball::getBall();
	b->init(ballNode,Ogre::Vector3(position),bounding,Ogre::Vector3(25,-30,-50));
	objects.push_back(b);
}
/*! Creates the player*/
void BaseApplication::CreatePlayer(Ogre::Vector3 position, Ogre::Vector3 scale)
{
	Ogre::Entity *paddle = mSceneMgr->createEntity("cube", "cube.mesh");
	paddle->setMaterialName("Examples/Outline");
	Ogre::SceneNode * paddleNode = mSceneMgr->createSceneNode("paddleNode");
	mSceneMgr->getRootSceneNode()->addChild(paddleNode);
	paddleNode->attachObject(paddle);
	paddle->setCastShadows(true);
	float cubeModelLength = 100;
	paddleNode->scale(scale.x/cubeModelLength,scale.y/cubeModelLength,scale.z/cubeModelLength);
	paddleNode->setPosition(position);
	Ogre::AxisAlignedBox bounding = Ogre::AxisAlignedBox(-scale.x/2 + position.x,-scale.y/2+ position.y,-scale.z/2+ position.z
		,scale.x/2+ position.x,scale.y/2+ position.y,scale.z/2+ position.z);
	Player *p = Player::getPlayer();
	p->init(paddleNode,Ogre::Vector3(position),bounding,Ogre::Vector3(0,0,0),mKeyboard);
	objects.push_back(p);
}
/*! Creates the opponent*/
void BaseApplication::CreateAIPlayer(Ogre::Vector3 position, Ogre::Vector3 scale)
{
	Ogre::Entity *enemyPaddle = mSceneMgr->createEntity("enemyCube", "cube.mesh");
	enemyPaddle->setMaterialName("Examples/EnemyOutline");
	Ogre::SceneNode * enemyPaddleNode = mSceneMgr->createSceneNode("enemyPaddleNode");
	mSceneMgr->getRootSceneNode()->addChild(enemyPaddleNode);
	enemyPaddleNode->attachObject(enemyPaddle);
	enemyPaddle->setCastShadows(true);
	float cubeModelLength = 100;
	enemyPaddleNode->scale(scale.x/cubeModelLength,scale.y/cubeModelLength,scale.z/cubeModelLength);
	enemyPaddleNode->setPosition(position);
	Ogre::AxisAlignedBox bounding = Ogre::AxisAlignedBox(-scale.x/2 + position.x,-scale.y/2+ position.y,-scale.z/2+ position.z
		,scale.x/2+ position.x,scale.y/2+ position.y,scale.z/2+ position.z);
	AIPlayer *ai = AIPlayer::getAIPlayer();
	ai->init(enemyPaddleNode,Ogre::Vector3(position),bounding,Ogre::Vector3(0,0,0));
	objects.push_back(ai);
}
//-------------------------------------------------------------------------------------
bool BaseApplication::configure(void)
{

    if(mRoot->showConfigDialog())
    {
		mWindow = mRoot->initialise(true, "Repeat Project Render Window");

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        HWND hwnd;
        mWindow->getCustomAttribute("WINDOW", (void*)&hwnd);
        LONG iconID   = (LONG)LoadIcon( GetModuleHandle(0), MAKEINTRESOURCE(IDI_APPICON) );
        SetClassLong( hwnd, GCL_HICON, iconID );
#endif
        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------------------------
void BaseApplication::chooseSceneManager(void)
{
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}
//-------------------------------------------------------------------------------------
void BaseApplication::createCamera(void)
{
    mCamera = mSceneMgr->createCamera("PlayerCam");

    mCamera->setPosition(Ogre::Vector3(0,20,-500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}
//-------------------------------------------------------------------------------------
void BaseApplication::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    windowResized(mWindow);

    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
}
//-------------------------------------------------------------------------------------
void BaseApplication::createViewports(void)
{
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
//-------------------------------------------------------------------------------------
void BaseApplication::setupResources(void)
{
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//-------------------------------------------------------------------------------------
void BaseApplication::createResourceListener(void)
{

}
//-------------------------------------------------------------------------------------
void BaseApplication::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-------------------------------------------------------------------------------------
void BaseApplication::go(void)
{
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif

    if (!setup())
        return;

    mRoot->startRendering();

    destroyScene();
}
//-------------------------------------------------------------------------------------
bool BaseApplication::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createCamera();
    createViewports();

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    createResourceListener();
    
    loadResources();

	createFrameListener(); 
	createScene();
    
    
	return true;
};
/*! Update all objects and handles collisions*/
	
int ballTick = 0;
Ogre::Vector3 bVel;

bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    mKeyboard->capture();
    mMouse->capture();

	int size = objects.size();
	
	for(int i = 0; i < size; i++)
	{
		objects[i]->update(evt.timeSinceLastFrame);
	}

	if(objects[1]->getPosition().z < objects[0]->getPosition().z - 30) /*! Check if the ball goes past the player */
	{
		/*! Play sound*/
		FModManager::System()->playSound(FMOD_CHANNEL_FREE, soundScore, true, &channelScore);
		FMOD_VECTOR  sourcePos  = { objects[0]->getPosition().x, objects[0]->getPosition().y, objects[0]->getPosition().z };
		channelScore->set3DAttributes(&sourcePos,0);
		channelScore->set3DMinMaxDistance(5,500);
		resultScore = channelScore->setVolume(1.0f);
		channelScore->setPaused(false);

		objects[1]->setPosition(Ogre::Vector3(0,200,0));
		score.y++;
	}
	else if(objects[1]->getPosition().z > objects[2]->getPosition().z + 30) /*! Check if the ball goes past the opponent*/
	{
		/*! Play sound*/
		FModManager::System()->playSound(FMOD_CHANNEL_FREE, soundScore, true, &channelScore);
		FMOD_VECTOR  sourcePos  = { objects[0]->getPosition().x, objects[0]->getPosition().y, objects[0]->getPosition().z };
		channelScore->set3DAttributes(&sourcePos,0);
		channelScore->set3DMinMaxDistance(5,500);
		resultScore = channelScore->setVolume(1.0f);
		channelScore->setPaused(false);

		objects[1]->setPosition(Ogre::Vector3(0,200,0));
		score.x++;
	}
	ballTick++;

	if (ballTick > 50)
	{
		bVel = Ball::getBall()->getVelocity();
		ballTick = 0;
	}
	if(true)
	{
		BaseObject* collidee;
		BaseObject* collider;
		int collideeType;
		int colliderType;
		check = false;

		for (int i = 0; i < size; i++)
		{
			int iType = objects[i]->m_type;
			Ogre::Vector3 iPos = objects[i]->getPosition();

			for (int j = 0; j< size; j++)
			{
				int jType = objects[j]->m_type;
			
				if(iType != jType && ((iType != CONSTANT_VALUES::WALL && jType != CONSTANT_VALUES::FLOOR) || (jType != CONSTANT_VALUES::WALL && iType !=CONSTANT_VALUES::FLOOR)))
				{
					if (iType == CONSTANT_VALUES::BALL || jType == CONSTANT_VALUES::BALL 
						|| iType ==CONSTANT_VALUES::PADDLE || jType == CONSTANT_VALUES::PADDLE)
					{
						if (iType == CONSTANT_VALUES::BALL || iType == CONSTANT_VALUES::PADDLE)
						{
							collidee = objects[i];
							collideeType = iType;
							collider = objects[j];
							colliderType = jType;
						}
						else if (jType == CONSTANT_VALUES::BALL || jType == CONSTANT_VALUES::PADDLE)
						{
							collidee = objects[j];
							collideeType = jType;
							collider = objects[i];
							colliderType = jType;
						}
						Ogre::Vector3 jPos = objects[j]->getPosition();

						if(sqrt(((jPos.x - iPos.x) * (jPos.x - iPos.x)) 
							+   ((jPos.y - iPos.y) * (jPos.y - iPos.y)) 
							+   ((jPos.z - iPos.z) * (jPos.z - iPos.z))) 
							< sqrt((objects[j]->m_radius * objects[j]->m_radius)
							+      (objects[i]->m_radius * objects[i]->m_radius))) //If the object's bounding spheres overlap
						{
							CollisionReturn colReturn = CollisionManager::CheckSAT(objects[i],objects[j]);
							if(colReturn.m_boolean)
						{
							if (colliderType == CONSTANT_VALUES::WALL || colliderType == CONSTANT_VALUES::FLOOR)
								{
									CollisionManager::CollisionMove((MovingObject*)collidee,collider,colReturn);
									if (collideeType == CONSTANT_VALUES::BALL)
										{	
											/*! Play sound*/
											FModManager::System()->playSound(FMOD_CHANNEL_FREE, soundBounce, true, &channelBounce);
											FMOD_VECTOR  sourcePos  = { objects[1]->getPosition().x, objects[1]->getPosition().y, objects[1]->getPosition().z }; //Ball should be source of noise and is
											channelBounce->set3DAttributes(&sourcePos,0);
											channelBounce->set3DMinMaxDistance(5,500);
											resultBounce = channelBounce->setVolume(1.0f);
											channelBounce->setPaused(false);

											if (colliderType == CONSTANT_VALUES::WALL)
											{
												CollisionManager::CollisionBounce((MovingObject*)collidee,bVel,colliderType);
											}
											else if (colliderType == CONSTANT_VALUES::FLOOR)
											{
												CollisionManager::CollisionBounce((MovingObject*)collidee,bVel,colliderType);
											}
										}
								}
								else if (colliderType == CONSTANT_VALUES::PADDLE && collideeType == CONSTANT_VALUES::BALL)
								{	
									/*! Play sound*/
									FModManager::System()->playSound(FMOD_CHANNEL_FREE, soundHit, true, &channelHit);
									FMOD_VECTOR  sourcePos  = { objects[0]->getPosition().x, objects[0]->getPosition().y, objects[0]->getPosition().z }; //Ball should be source of noise except it seemed to difficult to tell when the opponent deflected
									channelHit->set3DAttributes(&sourcePos,0);
									channelHit->set3DMinMaxDistance(5,500);
									resultHit = channelHit->setVolume(1.0f);
									channelHit->setPaused(false);

									CollisionManager::CollisionMove((MovingObject*)collidee,collider,colReturn);
									CollisionManager::CollisionBounce((MovingObject*)collidee,bVel,colliderType);
								}
							}
						}
					}
				}
			}
		}
	}
	else 
		check = true;
	
	Camera::getCam()->update(evt.timeSinceLastFrame);
	
	mPanel->mNode->setPosition(Camera::getCam()->getPosition() 
		+ Ogre::Vector3(Camera::getCam()->mCamera->getDirection().normalisedCopy().x *10,
		Camera::getCam()->mCamera->getDirection().normalisedCopy().y*10,
		Camera::getCam()->mCamera->getDirection().normalisedCopy().z*10));

	
	Ogre::Vector3 direction = Camera::getCam()->mCamera->getDirection();
	Ogre::Vector3 xaxis = direction.crossProduct(Ogre::Vector3(0,1,0));
	xaxis.normalise();

	Ogre::Vector3 yaxis = direction.crossProduct(xaxis);
	yaxis.normalise();

	Ogre::Matrix3 m1(xaxis.x,yaxis.x,direction.x,xaxis.y,yaxis.y,direction.y,xaxis.z,yaxis.z,direction.z);
	
	mPanel->mNode->setOrientation(Ogre::Quaternion(m1));
	mPanel->mNode->yaw(Ogre::Degree(180));
	mPanel->mNode->roll(Ogre::Degree(180));
	Ogre::Vector3 moveOffset = (-4.5f*xaxis.normalisedCopy()) +(-3.6f*yaxis.normalisedCopy());
	mPanel->mNode->setPosition(mPanel->mNode->getPosition() + moveOffset);
	playerScoreCaption->text(Ogre::StringConverter::toString(score.x));
	opponentScoreCaption ->text(Ogre::StringConverter::toString(score.y));
    
	if(pauseStream == true)
		channel->setPaused(true);
	else
		channel->setPaused(false);

	FMOD_VECTOR  listenervel  = { ((MovingObject*)objects[0])->getVelocity().x, ((MovingObject*)objects[0])->getVelocity().y, ((MovingObject*)objects[0])->getVelocity().z };

	FMOD_VECTOR  listenerpos  = { objects[0]->getNode()->getPosition().x, objects[0]->getNode()->getPosition().y, objects[0]->getNode()->getPosition().z };
	FModManager::System()->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);

	FModManager::System()->update();
	
	return true;
}
//-------------------------------------------------------------------------------------
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
	if(arg.key == OIS::KC_P)
	{
		if (pauseStream)
		{
			pauseStream = false;
		}
		else if(!pauseStream)
		{
			pauseStream = true;
		}
	}
    if(arg.key == OIS::KC_F5)   /*! refresh all textures*/
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   /*! take a screenshot*/
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }

    return true;
}

bool BaseApplication::keyReleased( const OIS::KeyEvent &arg )
{
    mCameraMan->injectKeyUp(arg);
    return true;
}

/*! Rotates the camera*/
bool BaseApplication::mouseMoved( const OIS::MouseEvent &arg )
{
	Camera::getCam()->rotateMouse(arg);
    return true;
}

bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    mCameraMan->injectMouseDown(arg, id);
    return true;
}

bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    mCameraMan->injectMouseUp(arg, id);
    return true;
}

void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}


void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
	if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}
