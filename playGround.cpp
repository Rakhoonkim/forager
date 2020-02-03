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

	_playerManager = new playerManager;
	_playerManager->init();


	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	_playerManager->release();
}


void playGround::update()
{
	gameNode::update();

	_playerManager->update();
}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY,BLACKNESS);
	//===========================================================
	_playerManager->render();
	TIMEMANAGER->render(getMemDC());
	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}
