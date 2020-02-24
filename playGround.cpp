#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);
	SCENEMANAGER->addScene("MAINMENU", new mainMenuScene);	// MAIN
	SCENEMANAGER->addScene("STAGE", new stageScene);		// STAGE
	SCENEMANAGER->addScene("MAPTOOL", new mapToolScene);	// MAPTOOL

	SCENEMANAGER->changeScene("MAINMENU");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	SCENEMANAGER->release();
}


void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//===========================================================
	if(!UIMANAGER->getLand()->getLand()) SCENEMANAGER->render(); // MAIN
	
	if (!CURSORMANAGER->getCursor()->getObjectPoint()) CURSORMANAGER->render();   //CURSOR
	
	TIMEMANAGER->render(getMemDC()); // юс╫ц 
	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}
