#include "stdafx.h"
#include "objectManager.h"
#include "playerManager.h"

objectManager::objectManager()
{
}

objectManager::~objectManager()
{
}

HRESULT objectManager::init()
{
	_cropsManager = new cropsManager;
	_cropsManager->init();

	_buildManager = new buildManager;
	_buildManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_puzzleManager = new puzzleManager;
	_puzzleManager->init();

	UIMANAGER->buildAdressLink(_buildManager);
	return S_OK;
}

void objectManager::release()
{
	_cropsManager->release();
	_buildManager->release();
	_enemyManager->release();
	_puzzleManager->release();
}

void objectManager::update()
{
	_cropsManager->update();
	_buildManager->update();
	_enemyManager->update();
	_puzzleManager->update();
}

void objectManager::render()
{
	_cropsManager->render();
	_enemyManager->render();
	_buildManager->render();
	//_puzzleManager->render(); ZORDER에서 렌더링을 해주고 있음
}


