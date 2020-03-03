#pragma once
#include "stdafx.h"
#include "inventory.h"
#include "build.h"
#include "equipment.h"
#include "land.h"


class gameNode;

#define MAXOPTION 5

class uiManager : public singletonBase<uiManager>
{
private:
	tagButton		_optionList[MAXOPTION];	 //옵션 리스트
	equipment*					_equipment;  //장비&스킬창
	inventory*						_inven;  //인벤토리
	build*							_build;  //건설창
	land*					     	 _land;  //토지 구매창

	int						_currentOption;
	bool						 _isOption;

	// ■■■■■■■■■■■■■■■■■■■■■■■■ PLAYER UI ■■■■■■■■■■■■■■■■■■■■■■■■

	tagPlayer*  _player;
	float	 _healthBar;   // 가로 체력바
	float		_expBar;   // 가로 경험치바
	float		_slushX; 

	RECT		  _exit;   // 나가는 RECT
public:
	uiManager();
	~uiManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();

	// 플레이어 옵션 창
	void PlayerUIRender();

	// 이외의 옵션 
	void optionsSetting();
	void setButtonAlpha();
	bool getOption()		{ return _isOption; }
	void setOption()		// 옵션 세팅 함수
	{
		if (!_isOption)
		{
			_isOption = true;
		}
		else
		{
			_equipment->setSkill();
			_land->setLand(false);
			_isOption = false;
			_currentOption = 1;
		}
	}		 // 옵션세팅


	void setInven(inventory* inven)					 { _inven = inven; }
	void playerAdressLink(tagPlayer* player)	     { _player = player;}
	void buildAdressLink(buildManager* buildManager) { _build->setBuildManager(buildManager);}
	
	//클래스 접근자
	land*	   getLand()		 { return _land; }
	build*	   getBuild()		 { return _build; }
	inventory* getInven()		 { return _inven; }
	equipment* getEquipment()	 { return _equipment; }

	void setOptionDirection(int num) { _currentOption = num; }
};

