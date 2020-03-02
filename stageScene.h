#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "objectManager.h"
#include "weather.h"


class stageScene : public gameNode
{
private:
	playerManager* _playerManager;		//PLAYER
	objectManager* _objectManager;		//OBJECT

	weather* _weather;					//����(������)
public:
	stageScene() {}
	~stageScene() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void enterStageScene();  // �������� ���� ��

	void setAlphaImage();	 // ����̵�Ʈ��, �����Ա� ���ĺ��� ó��
	void templeEntranceMouseCollision();	// ���� �Ա� ���콺 �浹 
};

