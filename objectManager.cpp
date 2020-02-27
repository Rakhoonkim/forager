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

	//EnemyCreate
	_slimeTimer = TIMEMANAGER->getWorldTime();
	_boarTimer = TIMEMANAGER->getWorldTime();
	_maxEnemy = 0;

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

	AutoEnemyCreate(); // enemyManager 
}

void objectManager::render()
{
	_cropsManager->render();
	_enemyManager->render();
	_buildManager->render();
	_puzzleManager->render();
}

void objectManager::AutoEnemyCreate()
{
	if (_maxEnemy > (2 * MAPMANAGER->getMapCount())) return;


	if (_slimeTimer + RND->getFromIntTo(10, 20) <= TIMEMANAGER->getWorldTime())
	{
		POINT rnd;
		rnd = MAPMANAGER->randomObjectTile();

		if (rnd.x != 0 && rnd.y != 0)
		{
			_maxEnemy++;
			_slimeTimer = TIMEMANAGER->getWorldTime();
			_enemyManager->CreateEnemy(ENEMY::SLIME, rnd.x, rnd.y);
		}
	}

	if (_boarTimer + RND->getFromIntTo(20, 30) <= TIMEMANAGER->getWorldTime())
	{
		POINT rnd2;
		rnd2 = MAPMANAGER->randomObjectTile();

		if (rnd2.x != 0 && rnd2.y != 0)
		{
			_maxEnemy++;
			_boarTimer = TIMEMANAGER->getWorldTime();
			_enemyManager->CreateEnemy(ENEMY::BOAR, rnd2.x, rnd2.y);
		}
	}
}
