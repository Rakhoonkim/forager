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
	SCENEMANAGER->addScene("MAINMENU",  new mainMenuScene);	// MAINMENU
	SCENEMANAGER->addScene("MAPTOOL",   new mapToolScene);	// MAPTOOL
	SCENEMANAGER->addScene("STAGE",		new stageScene);	// STAGE
	SCENEMANAGER->addScene("BOSS",      new bossScene);		// BOSS

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
	SCENEMANAGER->render(); // MAIN
	
	//오브젝트를 가리키지 않으면 최상단에 마우스가 나타나기 위한 렌더
	if (!CURSORMANAGER->getCursor()->getObjectPoint()) CURSORMANAGER->render();   //CURSOR
	
	//TIMEMANAGER->render(getMemDC()); //  FRAME 확인하기 위한 렌더링 함수
	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}
