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

	_mapToolScene = new mapToolScene;
	_mapToolScene->init();


	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	_mapToolScene->release();
}


void playGround::update()
{
	gameNode::update();

	_mapToolScene->update();
}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY,BLACKNESS);
	//===========================================================

	_mapToolScene->render();
	TIMEMANAGER->render(getMemDC());
	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}
