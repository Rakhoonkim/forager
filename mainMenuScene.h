#pragma once
#include "gameNode.h"

#define MAXBUTTON 8
class mainMenuScene : public gameNode
{
private:
	tagButton _button[MAXBUTTON];	//��ư 7�� 
	//tagButton _mapToolButton;
	//tagButton _play;
	//tagButton _extra;
	//tagButton _roadMap;
	//tagButton _comunity;
	//tagButton _credit;
	//tagButton _option;
	//tagButton _exit;

	int _buttonX;	// ��ư ������ 
	int _buttonY;
	int _distance;  // ��ư ����
	
	int _offsetX;	// �������� X��
	int _offsetY;	// �������� Y��
public:
	mainMenuScene();
	~mainMenuScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();	//�̹��� ����
	void buttonSetting();	//��ư ����

	void buttonClick();		//��ư Ŭ��
	void buttonEffect();	//��ư ����Ʈ

};

