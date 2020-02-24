#pragma once
#include "stdafx.h"
#include "inventory.h"
#include "build.h"
#include "equipment.h"
#include "land.h"
#include "weather.h"

class gameNode;

#define MAXOPTION 5

class uiManager : public singletonBase<uiManager>
{
private:
	tagButton _optionList[MAXOPTION];
	equipment* _equipment;
	inventory* _inven;
	build* _build;
	land* _land;
	weather* _weather;

	int _currentOption;
	bool _isOption;

	// === player Setting;
	tagPlayer* _player;
	float _healthBar;   // 체력바 가로 
	float _expBar;		// 경험치바 가로 
	float _slushX;
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
	bool getOption() { return _isOption; }
	void setOption() 
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
	
	build* getBuild()			 { return _build; }
	inventory* getInven()		 { return _inven; }
	equipment* getEquipment()	 { return _equipment; }
	land* getLand()				 { return _land; }

	void setOptionDirection(int num) { _currentOption = num; }
};

