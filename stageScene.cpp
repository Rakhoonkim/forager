#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	_playerManager = new playerManager;
	_playerManager->init();
	return S_OK;
}

void stageScene::release()
{
	_playerManager->release();
}

void stageScene::update()
{
	_playerManager->update();
}

void stageScene::render()
{
	_playerManager->render();
}
