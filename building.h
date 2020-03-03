#pragma once
#include "stdafx.h"

#define MAXFURNACELIST 9 
#define MAXFORGELIST 6
#define MAXSEWINGLIST 3

class building 
{
protected:
	tagObject					   _building;  //건물 구조체

	tagButton _furnaceButton[MAXFURNACELIST];  //버튼리스트
	tagButton	  _forgeButton[MAXFORGELIST];  //모루리스트
	tagButton	_sewingButton[MAXSEWINGLIST];  //재봉소리스트

	tagButton		 _craftButton;   //생산버튼
	tagButton		_addButton[2];   //추가버튼

	FURNACERECIPE		 _furnace;   //임시 저장하는 변수
	FORGERECIPE			   _forge;
	SEWINGRECIPE		  _sewing;

	float		_timer;   // 타이머 
	
	int     _itemCount;   // 아이템 개수
	int   _effectCount;   // 효과 인터벌 카운터
	 
	int      _backPack;   // 가방 
	int		   _wallet;   // 지갑 
	int		_direction;   // 현재 버튼을 어딜 가리키는지 
	
	bool	_craftPage;   // 제작페이지
	bool	   _isWork;   // 작동중인지 
	bool	    _isUse;   // 사용중인지

public:
	building();
	~building();

	virtual HRESULT init(BUILDING building, const char* imageName,int idx, int idy, bool farming = FALSE);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void EffectRender();           // 이펙트 렌더

	virtual void buttonInit();			   // 버튼 초기화
	virtual void buttonClick();			   // 버튼 클릭
	virtual void craftButton();			   // 버튼을 누르면 레시피 설정 
	virtual void isWorking();			   // 작동중 : 시간 후 아이템 드랍
	//설정자
	virtual void buttonEffect();//(사용안함) // 초기 구현 
	virtual void setHp(int maxHp, int hp);	   // 체력 설정
	virtual void setCenterXY(int idx,int idy); // 중간 위치 설정
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
	//제어함수 
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
	//제어함수 
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
	//제어함수 
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