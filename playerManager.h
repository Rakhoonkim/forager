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

	bool _isOption;					// �ɼ�â

	alphaEffect* _alphaEffect;		//����ġ 
public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();			  // �̹��� ����

	//============== �浹ó�� ========================
	void itemCollisionMouse();		  //�������浹
	void itemCollisionPlayer();		  //������
	void objectCollisionMouse();	  //������Ʈ 
	void bulletColision();			  //�Ѿ�
	//===============================================

	void optionControl();			  //�ɼ� ��Ʈ��

	void objectAttack(int num);		  //�Ĺ� ���� 
	void enemyAttack(int num);		  //���� ���� 

	//�ּҼ���
	void set_CropsManager(cropsManager* cropsManager)	 { _cropsManager = cropsManager; }
	void set_BuildManager(buildManager* buildManager)	 { _buildManager = buildManager; }
	void set_EnemyManager(enemyManager* enemyManager)	 { _enemyManager = enemyManager; }
	void set_puzzleManager(puzzleManager* puzzleManager) { _puzzleManager = puzzleManager;}

	player* get_player() { return _player; }  // �÷��̾� Ŭ���� ��ȯ
};

