#include "stdafx.h"
#include "playerManager.h"
#include "cropsManager.h"
#include "buildManager.h"
#include "enemyManager.h"
#include "puzzleManager.h"

HRESULT playerManager::init()
{
	imageSetting();

	_player = new player();
	_player->init();

	ZORDER->addZorder(STAGEOBJECT::PLAYER, _player, NULL, NULL, NULL, NULL);
	
	_isOption = false;  // 옵션 키 초기화

	UIMANAGER->playerAdressLink(_player->get_PlayerAddress());		 // PLAYER->UI
	UIMANAGER->getInven()->setPlayer(_player->get_PlayerAddress());  // PLAYER->INVEN

	_alphaEffect = new alphaEffect;  // 경험치 
	_alphaEffect->init();

	return S_OK;
}

void playerManager::release()
{
	_player->release();
	_alphaEffect->release();  // 숫자 지우기
}

void playerManager::update()
{
	_player->update();

	if (!UIMANAGER->getOption()) objectCollisionMouse();   // 마우스 포인터를 보여주기 위한 

	itemCollisionPlayer();    // 아이템을 먹기 위한
	itemCollisionMouse();	  // 아이템을 먹기 위한
	optionControl();		  // 옵션창 컨트롤 
	bulletColision();		  // 총알 충돌
	_alphaEffect->update();	  // 경험치 
}

void playerManager::render()
{
	// 건물사용중이면 렌드를 끈다
	//if (!_buildManager->usedCheck()) _player->render();
	//_alphaEffect->render();
}

void playerManager::imageSetting()
{
	IMAGEMANAGER->addFrameImage("playerIdle", "./image/player/playerIdle.bmp", 198, 96, 6, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("playerWalk", "./image/player/playerWalk.bmp", 198, 108, 6, 2, true, RGB(255, 0, 255), true);

	KEYANIMANAGER->addCoordinateFrameAnimation("playerIdle_R", "playerIdle", 0, 5, 15, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("playerIdle_L", "playerIdle", 6, 11, 15, false, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("playerWalk_R", "playerWalk", 0, 5, 15, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("playerWalk_L", "playerWalk", 6, 11, 15, false, true);

	//곡괭이
	IMAGEMANAGER->addFrameImage("playerPick", "./image/player/playerPickaxe.bmp", 532, 106, 7, 2, true, RGB(255, 0, 255), true);

	KEYANIMANAGER->addCoordinateFrameAnimation("playerPick_R", "playerPick", 0, 7, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("playerPick_L", "playerPick", 7, 14, 15, false, false);

	// image
	IMAGEMANAGER->addFrameImage("shadow", "./image/player/shadow.bmp", 80, 16, 5, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("shadow", "shadow", 80, 16, 16, 16, 1, 0.3f, 20);

	IMAGEMANAGER->addFrameImage("playerWeapon", "./image/player/playerWeapon.bmp",162, 108,3,2, true, RGB(255, 0, 255), true);
}

//아이템&플레이어
void playerManager::itemCollisionPlayer()
{
	for (int i = 0; i < ITEMMANAGER->getVItem().size(); i++)
	{
		//한번만 확인하기 위해 BOOL값 확인
		if (!ITEMMANAGER->getVItem()[i]->getItem()->drop) continue;
		RECT temp;
		//아이템이랑 몸이랑 충돌 
		if ((IntersectRect(&temp, &ITEMMANAGER->getVItem()[i]->getItem()->rc, &_player->get_PlayerAddress()->rc)))
		{
			ITEMMANAGER->getVItem()[i]->setGain();
			break;
		}
	}
}
// 아이템&마우스 
void playerManager::itemCollisionMouse()
{
	for (int i = 0; i < ITEMMANAGER->getVItem().size(); i++)
	{
		//한번만 확인하기 위해 BOOL값 확인
		if (!ITEMMANAGER->getVItem()[i]->getItem()->drop) continue;
		// 마우스와 아이템 충돌 
		if ((PtInRect(&ITEMMANAGER->getVItem()[i]->getItem()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y))))
		{
			ITEMMANAGER->getVItem()[i]->setGain(_player->get_PlayerAddress()->x, _player->get_PlayerAddress()->y);
			break;
		}
	}
}
//오브젝트와 마우스 충돌
void playerManager::objectCollisionMouse()
{
	//■■■■■■■■■■■■■■■■■■■■■■ CropsCollision ■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < _cropsManager->getVCrops().size(); ++i)
	{
		//플레이어 공격중일 떄 
		if (_cropsManager->getVCrops()[i]->getCrops()->isClick && PtInRect(&_cropsManager->getVCrops()[i]->getCrops()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			//커서 매니져 세팅
			CURSORMANAGER->setCropsPoint();
			CURSORMANAGER->getCursor()->setCursorXY(_cropsManager->getVCrops()[i]->getCrops()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _cropsManager->getVCrops()[i]->getCrops()->centerY - CAMERAMANAGER->getWorldCamera().cameraY);

			if (_player->get_PlayerAddress()->health > 0) objectAttack(i);
			return;
		}
	}

	//■■■■■■■■■■■■■■■■■■■■■■ buildAttackCollision ■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < _buildManager->getVBuild().size(); ++i)
	{
		//거리가 가까우면
		if (180 >= getDistance(_buildManager->getVBuild()[i]->getBuilding()->centerX, _buildManager->getVBuild()[i]->getBuilding()->centerY, _player->get_PlayerAddress()->x, _player->get_PlayerAddress()->y))
		{
			// 건물 USED 창 띄우지 않고 and 마우스가 충돌 나면 
			if (!_buildManager->getVBuild()[i]->getUsed() && PtInRect(&_buildManager->getVBuild()[i]->getBuilding()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
			{
				//클릭 중으로 변경
				_buildManager->getVBuild()[i]->getBuilding()->isClick = true;
				// 건물마다 마우스 커서가 달라서 조건을 줌 
				if (_buildManager->getVBuild()[i]->getBuilding()->building == BUILDING::BRIDGE || _buildManager->getVBuild()[i]->getBuilding()->building == BUILDING::FISHTRAP)
				{
					CURSORMANAGER->setBridgePoint();
					CURSORMANAGER->getCursor()->setCursorXY(_buildManager->getVBuild()[i]->getBuilding()->x - CAMERAMANAGER->getWorldCamera().cameraX, _buildManager->getVBuild()[i]->getBuilding()->y - CAMERAMANAGER->getWorldCamera().cameraY - 15);
				}
				else if (_buildManager->getVBuild()[i]->getBuilding()->building == BUILDING::FURNACE || _buildManager->getVBuild()[i]->getBuilding()->building == BUILDING::FORGE || _buildManager->getVBuild()[i]->getBuilding()->building == BUILDING::SEWING_STATION)
				{
					CURSORMANAGER->setBuildPoint();
					CURSORMANAGER->getCursor()->setCursorXY(_buildManager->getVBuild()[i]->getBuilding()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _buildManager->getVBuild()[i]->getBuilding()->centerY - CAMERAMANAGER->getWorldCamera().cameraY);
				}
				return;
			}
			else
			{
				_buildManager->getVBuild()[i]->getBuilding()->isClick = false;
			}
		}
		else
		{
			//BOOL값 초기화
			_buildManager->getVBuild()[i]->getBuilding()->isClick = false;
			_buildManager->getVBuild()[i]->setUsed();
		}
	}

	//■■■■■■■■■■■■■■■■■■■■■■ EnemyCollision ■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < _enemyManager->getVEnemy().size(); ++i)
	{
		//플레이어 공격중일 떄 
		if (!_enemyManager->getVEnemy()[i]->getEnemy()->isHit && PtInRect(&_enemyManager->getVEnemy()[i]->getEnemy()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			//몬스터 마다 
			if (_enemyManager->getVEnemy()[i]->getEnemy()->enemy == ENEMY::SLIME)
			{
				CURSORMANAGER->setCropsPoint();
				CURSORMANAGER->getCursor()->setCursorXY(_enemyManager->getVEnemy()[i]->getEnemy()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _enemyManager->getVEnemy()[i]->getEnemy()->centerY - CAMERAMANAGER->getWorldCamera().cameraY);
			}
			else if (_enemyManager->getVEnemy()[i]->getEnemy()->enemy == ENEMY::DEMON ||
				_enemyManager->getVEnemy()[i]->getEnemy()->enemy == ENEMY::BOAR)
			{
				CURSORMANAGER->setBridgePoint();
				CURSORMANAGER->getCursor()->setCursorXY(_enemyManager->getVEnemy()[i]->getEnemy()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _enemyManager->getVEnemy()[i]->getEnemy()->centerY - CAMERAMANAGER->getWorldCamera().cameraY);
			}
			else if (_enemyManager->getVEnemy()[i]->getEnemy()->enemy == ENEMY::SKULL)
			{
				CURSORMANAGER->setBridgePoint();
				CURSORMANAGER->getCursor()->setCursorXY(_enemyManager->getVEnemy()[i]->getEnemy()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _enemyManager->getVEnemy()[i]->getEnemy()->centerY - CAMERAMANAGER->getWorldCamera().cameraY + 25);
			}
			else if (_enemyManager->getVEnemy()[i]->getEnemy()->enemy == ENEMY::DEMON_BOSS)
			{
				CURSORMANAGER->setBossPoint();
				CURSORMANAGER->getCursor()->setCursorXY(_enemyManager->getVEnemy()[i]->getEnemy()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _enemyManager->getVEnemy()[i]->getEnemy()->centerY - CAMERAMANAGER->getWorldCamera().cameraY + 25);

			}

			if (_player->get_PlayerAddress()->health > 0) enemyAttack(i);
			return;
		}
	}

	//■■■■■■■■■■■■■■■■■■■■■■ PuzzleCollision ■■■■■■■■■■■■■■■■■■■■■■
	if (!_puzzleManager->getTreasureChest()->getIsOpen() && 180 >= getDistance(_puzzleManager->getTreasureChest()->getPuzzle()->centerX, _puzzleManager->getTreasureChest()->getPuzzle()->centerY, _player->get_PlayerAddress()->x, _player->get_PlayerAddress()->y))
	{
		if (PtInRect(&_puzzleManager->getTreasureChest()->getPuzzle()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			CURSORMANAGER->setBuildPoint();
			CURSORMANAGER->getCursor()->setCursorXY(_puzzleManager->getTreasureChest()->getPuzzle()->x - CAMERAMANAGER->getWorldCamera().cameraX + 49, _puzzleManager->getTreasureChest()->getPuzzle()->y - CAMERAMANAGER->getWorldCamera().cameraY + 75);
			_puzzleManager->getTreasureChest()->getPuzzle()->isClick = true;
			return;
		}
		else _puzzleManager->getTreasureChest()->getPuzzle()->isClick = false;

	}
	else _puzzleManager->getTreasureChest()->getPuzzle()->isClick = false;

	CURSORMANAGER->setCursor();
	CURSORMANAGER->getCursor()->setCursorChange();
}

//총알 충돌
void playerManager::bulletColision()
{
	for (int i = 0;i < _enemyManager->getBulletManager()->getBullet()->getVBullet().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->get_PlayerAddress()->rc, &_enemyManager->getBulletManager()->getBullet()->getVBullet()[i]->rc))
		{
			_player->playerHit();
			if (_enemyManager->getBulletManager()->getBullet()->getVBullet()[i]->isFire) EFFECTMANAGER->play("fireBall", _enemyManager->getBulletManager()->getBullet()->getVBullet()[i]->x, _enemyManager->getBulletManager()->getBullet()->getVBullet()[i]->y);
			_enemyManager->getBulletManager()->getBullet()->getVBullet()[i]->isFire = false;
			break;
		}
	}
}

//옵션창 컨트롤
void playerManager::optionControl()
{
	//옵션창 컨트롤
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) && !UIMANAGER->getBuild()->getisBuilding() && !_buildManager->usedCheck())
	{
		UIMANAGER->setOption();
	}
}

void playerManager::objectAttack(int num)
{
	//TYPE마다 데미지 입히기 추가할 예정 
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//거리가 좁혀지면 데미지를 입힌다.
		if (getDistance(_player->get_PlayerAddress()->x, _player->get_PlayerAddress()->y, _cropsManager->getVCrops()[num]->getCrops()->centerX, _cropsManager->getVCrops()[num]->getCrops()->centerY) <= 120)
		{
			_player->setPlayerHealth(3);		// 체력소진
			_cropsManager->getVCrops()[num]->setCropsEffect(true);
			_cropsManager->getVCrops()[num]->setCropsIsHit(true);
			_cropsManager->getVCrops()[num]->setCropsHit(_player->get_PlayerAddress()->damage);
		}
		//KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}
}

void playerManager::enemyAttack(int num)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//거리가 좁혀지면 데미지를 입힌다.
		if (getDistance(_player->get_PlayerAddress()->x, _player->get_PlayerAddress()->y, _enemyManager->getVEnemy()[num]->getEnemy()->centerX, _enemyManager->getVEnemy()[num]->getEnemy()->centerY) <= 80)
		{
			_player->setPlayerHealth(3);		 // 체력소진
			_enemyManager->getVEnemy()[num]->setEnemyHit(_player->get_PlayerAddress()->damage);
		}
		//KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}
}

