#pragma once
#include "stdafx.h"
#include "inventory.h"

class gameNode;

#define MAXOPTION 5

class uiManager : public singletonBase<uiManager>
{
private:
	tagButton _optionList[MAXOPTION];


	inventory* _inven;

	int _currentOption;
	bool _isOption;
public:
	uiManager();
	~uiManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();
	void optionsSetting();
	void setButtonAlpha();
	void setOption() 
	{
		if (!_isOption)
		{
			_isOption = true;
		}
		else _isOption = false;
	}


	void setInven(inventory* inven) { _inven = inven; }
};

