#pragma once
#include "gameNode.h"

class mainMenuScene : public gameNode
{
private:
	tagButton _button[7];

	//tagButton _play;
	//tagButton _extra;
	//tagButton _roadMap;
	//tagButton _comunity;
	//tagButton _credit;
	//tagButton _option;
	//tagButton _exit;

	int _buttonX;  
	int _buttonY;
	int _distance;
	int _offsetX;
	int _offsetY;
public:
	mainMenuScene();
	~mainMenuScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();
	void buttonSetting();

	void buttonClick();
	void buttonEffect();

};

