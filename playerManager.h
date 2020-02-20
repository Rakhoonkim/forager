#pragma once
#include "gameNode.h"
#include "player.h"
#include "alphaEffect.h"

class cropsManager;
class buildManager;
class enemyManager;

class playerManager: public gameNode
{
private:
	player* _player;				// PLAYER
	cropsManager* _cropsManager;	// CROPS
	buildManager* _buildManager;	// BUILD
	enemyManager* _enemyManager;	// ENEMY

	bool _isOption;					// 옵션창

	//경험치 
	alphaEffect* _alphaEffect;
public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();			  // 이미지 셋팅

	//============== 충돌처리 ========================
	void itemCollisionMouse();
	void itemCollisionPlayer();
	void objectCollisionMouse();	  // 마우스 커서 보이기 

	void optionControl();			  // 옵션 컨트롤

	void objectAttack(int num);		  //작물 공격 
	void enemyAttack(int num);		  //몬스터 공격 

	void set_CropsManager(cropsManager* cropsManager) { _cropsManager = cropsManager; }
	void set_BuildManager(buildManager* buildManager) { _buildManager = buildManager; }
	void set_EnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }

	player* get_player() { return _player; }
};

