#pragma once
#include "gameNode.h"
#include "player.h"
#include "alphaEffect.h"

class cropsManager;
class buildManager;
class enemyManager;
class puzzleManager;

class playerManager: public gameNode
{
private:
	player* _player;				// PLAYER
	
	cropsManager* _cropsManager;	// CROPS
	buildManager* _buildManager;	// BUILD
	enemyManager* _enemyManager;	// ENEMY
	puzzleManager* _puzzleManager;  // PUZZLE

	bool _isOption;					// 옵션창

	alphaEffect* _alphaEffect;		//경험치 
public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();			  // 이미지 셋팅

	//============== 충돌처리 ========================
	void itemCollisionMouse();		  //아이템충돌
	void itemCollisionPlayer();		  //아이템
	void objectCollisionMouse();	  //오브젝트 
	void bulletColision();			  //총알
	//===============================================

	void optionControl();			  //옵션 컨트롤

	void objectAttack(int num);		  //식물 공격 
	void enemyAttack(int num);		  //몬스터 공격 

	//주소세팅
	void set_CropsManager(cropsManager* cropsManager)	 { _cropsManager = cropsManager; }
	void set_BuildManager(buildManager* buildManager)	 { _buildManager = buildManager; }
	void set_EnemyManager(enemyManager* enemyManager)	 { _enemyManager = enemyManager; }
	void set_puzzleManager(puzzleManager* puzzleManager) { _puzzleManager = puzzleManager;}

	player* get_player() { return _player; }  // 플레이어 클래스 반환
};

