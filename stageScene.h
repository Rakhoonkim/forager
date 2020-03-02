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

	weather* _weather;					//날씨(사용안함)
public:
	stageScene() {}
	~stageScene() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void enterStageScene();  // 스테이지 들어올 때

	void setAlphaImage();	 // 드루이드트리, 던전입구 알파블렌더 처리
	void templeEntranceMouseCollision();	// 던전 입구 마우스 충돌 
};

