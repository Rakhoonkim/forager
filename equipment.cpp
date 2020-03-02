#include "stdafx.h"
#include "equipment.h"

equipment::equipment()
{
}

equipment::~equipment()
{
}

HRESULT equipment::init()
{
	buttonSetting();

	_skill = new skill;
	_skill->init();
	
	_isSkill = false;

	return S_OK;
}

void equipment::release()
{
}

void equipment::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_skillButton.rc, _ptMouse))
		{
				_isSkill = true;
		}
		KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}

	if (_isSkill)
	{
		_skill->update();
		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			_isSkill = false;
		}
	}

}

void equipment::render()
{
}

void equipment::render(HDC hdc)
{
	//스킬창이 아니면 
	if (!_isSkill)
	{
		//스킬 및 위업
		//Rectangle(hdc, _skillButton.rc);
		//Rectangle(hdc, _featButton.rc);
		IMAGEMANAGER->findImage("skillIcon")->render(hdc, _skillButton.rc.left - 15, _skillButton.rc.top - 3);
		IMAGEMANAGER->findImage("featIcon")->render(hdc, _featButton.rc.left - 15, _featButton.rc.top - 3);

		//장비창 렌더 
		for (int i = 0; i < 15; i++)
		{
			// 가장 위 장비 및 도구 
			if (i < 11)
			{
				//Rectangle(hdc, _weaponButton[i].rc);
				IMAGEMANAGER->findImage("disableBlock")->frameRender(hdc, _weaponButton[i].rc.left, _weaponButton[i].rc.top, 3, 0);
			}
			// 가장 왼쪽 장신구
			if (i < 6)
			{
				//Rectangle(hdc, _equipButton[i].rc);
				IMAGEMANAGER->findImage("disableBlock")->frameRender(hdc, _equipButton[i].rc.left, _equipButton[i].rc.top, 1, 0);
			}
			// 가운데 씰
			if (i < 9)
			{
				//Rectangle(hdc, _sealButton[i].rc);
				IMAGEMANAGER->findImage("disableBlock")->frameRender(hdc, _sealButton[i].rc.left, _sealButton[i].rc.top, 2, 0);
			}
			// 오른쪽 유물 칸 
			//Rectangle(hdc, _treasureButton[i].rc);
			IMAGEMANAGER->findImage("disableBlock")->frameRender(hdc, _treasureButton[i].rc.left, _treasureButton[i].rc.top, 0, 0);
		}
	}
	else // 스킬창이면
	{
		_skill->render(hdc);
	}
}

void equipment::buttonSetting()
{
	_skillButton.rc = RectMake(WINSIZEX / 2 - 160, 140, 120, 60);
	_featButton.rc = RectMake(WINSIZEX / 2 + 40, 140, 120, 60);

	//장비창 셋팅 
	for (int i = 0; i < 11; i++)
	{
		_weaponButton[i].rc = RectMake(WINSIZEX / 6 - 30 + i * (72 + 5), WINSIZEY / 2 - 100, 72, 72);
		_weaponButton[i].isClick = false;
		_weaponButton[i].isEffect = false;
	}
	//하단 장비창 
	for (int i = 0; i < 3; i++)
	{
		//가장 왼쪽 
		for (int j = 0; j < 2; j++)
		{
			_equipButton[i * 2 + j].rc = RectMake(_weaponButton[0].rc.left + j * (72 + 5) - 15, WINSIZEY / 2 + 100 + i * (72 + 5), 72, 72);
			_equipButton[i * 2 + j].isClick = false;
			_equipButton[i * 2 + j].isEffect = false;
		}
		// 가운데 
		for (int j = 0;j < 3; j++)
		{
			_sealButton[i * 3 + j].rc = RectMake(_weaponButton[3].rc.left + j * (72 + 5) + 5, WINSIZEY / 2 + 100 + i * (72 + 5), 72, 72);
			_sealButton[i * 3 + j].isClick = false;
			_sealButton[i * 3 + j].isEffect = false;
		}
		// 오른쪽
		for (int j = 0; j < 5; j++)
		{
			_treasureButton[i * 5 + j].rc = RectMake(_weaponButton[7].rc.left + j * (72 + 5) + 20, WINSIZEY / 2 + 100 + i * (72 + 5), 72, 72);
			_treasureButton[i * 5 + j].isClick = false;
			_treasureButton[i * 5 + j].isEffect = false;
		}
	}
}
