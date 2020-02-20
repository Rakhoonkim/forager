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

	bool _isOption;					// �ɼ�â

	//����ġ 
	alphaEffect* _alphaEffect;
public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();			  // �̹��� ����

	//============== �浹ó�� ========================
	void itemCollisionMouse();
	void itemCollisionPlayer();
	void objectCollisionMouse();	  // ���콺 Ŀ�� ���̱� 

	void optionControl();			  // �ɼ� ��Ʈ��

	void objectAttack(int num);		  //�۹� ���� 
	void enemyAttack(int num);		  //���� ���� 

	void set_CropsManager(cropsManager* cropsManager) { _cropsManager = cropsManager; }
	void set_BuildManager(buildManager* buildManager) { _buildManager = buildManager; }
	void set_EnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }

	player* get_player() { return _player; }
};

