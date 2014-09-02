#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include <vector>

#include "CONSTANT_VALUES.h"
#include "BaseObject.h"
#include "MovingObject.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "Player.h"
#include "AIPlayer.h"
#include "Ball.h"
#include "FModManager.h"

#include "Gui3D.h"
#include "Gui3DPanel.h"
#include "MySimpleDemoPanelColors.h"

class BaseApplication : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
{
public:
    BaseApplication(void);
    virtual ~BaseApplication(void);

    virtual void go(void);
	
protected:
    virtual bool setup();
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createScene(void) = 0;
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );

    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    virtual void windowResized(Ogre::RenderWindow* rw);

	virtual void windowClosed(Ogre::RenderWindow* rw);

    Ogre::Root *mRoot;
    Ogre::Camera* mCamera;
    Ogre::SceneManager* mSceneMgr;
    Ogre::RenderWindow* mWindow;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;

    OgreBites::SdkCameraMan* mCameraMan;     
	bool mCursorWasVisible;                  
    bool mShutDown;

    OIS::InputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;

	vector<BaseObject*> objects; /*! Vector for every object in the game*/
	Camera mCam;
	bool check;
	Ogre::Vector2 score;
	
	/*!Gui*/
	Gui3D::Gui3D* mGui3D;
	Gui3D::Panel* mPanel;
	Gui3D::ProgressBar* mForceProgressbar;
	Gui3D::Caption* playerScoreCaption;
	Gui3D::Caption* opponentScoreCaption;
	MySimpleDemoPanelColors mMySimpleDemoPanelColors;

	/*! FMOD Stuff*/
	FMOD_RESULT result;
	FMOD::Sound *sound;
	FMOD::Channel *channel;
	bool pauseStream;

	FMOD_RESULT resultHit;
	FMOD_RESULT resultBounce;
	FMOD_RESULT resultScore;
	FMOD::Sound *soundHit;
	FMOD::Sound *soundBounce;
	FMOD::Sound *soundScore;
	FMOD::Channel *channelHit;
	FMOD::Channel *channelBounce;
	FMOD::Channel *channelScore;

	FMOD_RESULT result2;
	FMOD::Sound *sound2;
	FMOD::Channel *channel2;
	FMOD::Reverb *reverb;
	bool pauseSpatial;

	/*! Creation methods for each object*/
	void CreateWall(Ogre::Vector3 position,Ogre::Vector3 scale,Ogre::String str, int type);
	void CreatePlayer(Ogre::Vector3 position, Ogre::Vector3 scale);
	void CreateBall(Ogre::Vector3 position, Ogre::Vector3 scale);
	void CreateAIPlayer(Ogre::Vector3 position, Ogre::Vector3 scale);
};

#endif
