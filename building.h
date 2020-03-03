#pragma once
#include "stdafx.h"

#define MAXFURNACELIST 9 
#define MAXFORGELIST 6
#define MAXSEWINGLIST 3

class building 
{
protected:
	tagObject					   _building;  //�ǹ� ����ü

	tagButton _furnaceButton[MAXFURNACELIST];  //��ư����Ʈ
	tagButton	  _forgeButton[MAXFORGELIST];  //��縮��Ʈ
	tagButton	_sewingButton[MAXSEWINGLIST];  //����Ҹ���Ʈ

	tagButton		 _craftButton;   //�����ư
	tagButton		_addButton[2];   //�߰���ư

	FURNACERECIPE		 _furnace;   //�ӽ� �����ϴ� ����
	FORGERECIPE			   _forge;
	SEWINGRECIPE		  _sewing;

	float		_timer;   // Ÿ�̸� 
	
	int     _itemCount;   // ������ ����
	int   _effectCount;   // ȿ�� ���͹� ī����
	 
	int      _backPack;   // ���� 
	int		   _wallet;   // ���� 
	int		_direction;   // ���� ��ư�� ��� ����Ű���� 
	
	bool	_craftPage;   // ����������
	bool	   _isWork;   // �۵������� 
	bool	    _isUse;   // ���������

public:
	building();
	~building();

	virtual HRESULT init(BUILDING building, const char* imageName,int idx, int idy, bool farming = FALSE);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void EffectRender();           // ����Ʈ ����

	virtual void buttonInit();			   // ��ư �ʱ�ȭ
	virtual void buttonClick();			   // ��ư Ŭ��
	virtual void craftButton();			   // ��ư�� ������ ������ ���� 
	virtual void isWorking();			   // �۵��� : �ð� �� ������ ���
	//������
	virtual void buttonEffect();//(������) // �ʱ� ���� 
	virtual void setHp(int maxHp, int hp);	   // ü�� ����
	virtual void setCenterXY(int idx,int idy); // �߰� ��ġ ����
	virtual void setUsed()					     { _isUse = false; }
	virtual void setAni()						 { _building.ani = KEYANIMANAGER->findAnimation("furnace"); }

	virtual bool getUsed()						 { return _isUse; }
	virtual tagObject* getBuilding()			 { return &_building; }
};

// furnace
class furnace : public building
{
public:
	furnace();
	~furnace();

	virtual void update();
	virtual void render();
	virtual void EffectRender();
	//�����Լ� 
	virtual void buttonEffect();
	virtual void buttonClick();
	virtual void buttonInit();
	virtual void isWorking();
	virtual void craftButton();  
};

// forge
class forge : public building
{
public:
	forge() {}
	~forge() {}

	virtual void update();
	virtual void render();
	virtual void EffectRender();
	//�����Լ� 
	virtual void buttonEffect();
	virtual void buttonClick();
	virtual void buttonInit();
	virtual void isWorking();
	virtual void craftButton();
};

// forge SEWING_STATION
class sewingStation : public building
{

public:
	sewingStation() {}
	~sewingStation() {}

	virtual void update();
	virtual void render();
	virtual void EffectRender();
	//�����Լ� 
	virtual void buttonEffect();
	virtual void buttonClick();
	virtual void buttonInit();
	virtual void isWorking();
	virtual void craftButton();
};

//FISHTRAP
class fishTrap : public building
{
private:
	float _startY;

	bool _upDown;
	bool _caught;
public:
	fishTrap() {
		_caught = false; 
		_upDown = false;
		_startY = 10;
	}
	~fishTrap() {}

	virtual void update();
	virtual void render();	
	virtual void EffectRender();
	virtual void isWorking();

};

class bridge : public building
{
public:
	bridge() {}
	~bridge() {}

	virtual void update();
	virtual void render();
	virtual void EffectRender();
};