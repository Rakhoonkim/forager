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
	SCENEMANAGER->addScene("STAGE", new stageScene);
	SCENEMANAGER->addScene("MAPTOOL", new mapToolScene);

	SCENEMANAGER->changeScene("STAGE");

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
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY,BLACKNESS);
	//===========================================================

	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}