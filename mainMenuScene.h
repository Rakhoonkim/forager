#pragma once
#include "gameNode.h"

class mainMenuScene : public gameNode
{
private:
	tagButton _button[7];	//버튼 7개 

	//tagButton _play;
	//tagButton _extra;
	//tagButton _roadMap;
	//tagButton _comunity;
	//tagButton _credit;
	//tagButton _option;
	//tagButton _exit;

	int _buttonX;	// 버튼 기준점 
	int _buttonY;
	int _distance;  // 버튼 간격
	
	int _offsetX;	// 루프렌더 X값
	int _offsetY;	// 루프렌더 Y값
public:
	mainMenuScene();
	~mainMenuScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();	//이미지 세팅
	void buttonSetting();	//버튼 세팅

	void buttonClick();		//버튼 클릭
	void buttonEffect();	//버튼 이펙트

};

