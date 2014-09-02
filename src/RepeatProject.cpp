/*! Main class project which creates the scene*/
#include "RepeatProject.h"

//-------------------------------------------------------------------------------------
RepeatProject::RepeatProject(void)
{
}
//-------------------------------------------------------------------------------------
RepeatProject::~RepeatProject(void)
{
}

//-------------------------------------------------------------------------------------
void RepeatProject::createScene(void)
{
	CreatePlayer(Ogre::Vector3(0,200,-250),Ogre::Vector3(75,20,5));
	CreateBall(Ogre::Vector3(0,200,0),Ogre::Vector3(20,20,20));
	CreateAIPlayer(Ogre::Vector3(0,200,250),Ogre::Vector3(75,20,5));

	//Floor and ceiling
	CreateWall(Ogre::Vector3(0,400,0),Ogre::Vector3(505,5,500), "Yellow1",CONSTANT_VALUES::FLOOR);
	CreateWall(Ogre::Vector3(0,0,0),Ogre::Vector3(505,5,500), "Yellow1",CONSTANT_VALUES::FLOOR);

	//Side Walls
	CreateWall(Ogre::Vector3(-250,200,0),Ogre::Vector3(5,400,500), "Yellow2",CONSTANT_VALUES::WALL);
	CreateWall(Ogre::Vector3(250,200,0),Ogre::Vector3(5,400,500), "Yellow2",CONSTANT_VALUES::WALL);
	
	// Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));

    // Create a light
    Ogre::Light* l1 = mSceneMgr->createLight("MainLight");
    l1->setPosition(0,200,-400);
	Ogre::Light* l2 = mSceneMgr->createLight("OpponentLight");
    l2->setPosition(0,200,275);

	mSceneMgr->setSkyDome(true, "Examples/SpaceSkyPlane", 5, 8);

	mGui3D = new Gui3D::Gui3D(&mMySimpleDemoPanelColors);
	Ogre::Viewport *viewport = mWindow->getViewport(0);
	mGui3D->createScreen(viewport, "purple", "mainScreen");
	createGamePanel();

	Camera::getCam()->init(mCamera, Player::getPlayer()->getNode());
	Camera::getCam()->setPosition(Ogre::Vector3( Player::getPlayer()->getNode()->getPosition().x,  Player::getPlayer()->getNode()->getPosition().y + 50,  Player::getPlayer()->getNode()->getPosition().z +100));

}

void RepeatProject::createGamePanel()
{
	mPanel = new Gui3D::Panel(mGui3D, mSceneMgr, Ogre::Vector2(200,100),10,"purple","test_panel");
	mPanel->hideInternalMousePointer();
	mPanel->makeCaption(5,20,300,0,"Player: ");
	mPanel->makeCaption(5,50,300,0,"Opponent: ");
	playerScoreCaption = mPanel->makeCaption(150,20,40,20, Ogre::StringConverter::toString(score.x));
	opponentScoreCaption = mPanel->makeCaption(150,50,40,20,Ogre::StringConverter::toString(score.y));
	mPanel->mNode->setPosition (0,0,0);
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        RepeatProject app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
