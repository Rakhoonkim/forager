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
	return S_OK;
}

void equipment::release()
{
}

void equipment::update()
{
}

void equipment::render()
{
}

void equipment::render(HDC hdc)
{
	Rectangle(hdc, _skillButton.rc);
	Rectangle(hdc, _featButton.rc);
	/*IMAGEMANAGER->findImage("bigBox")->frameRender(hdc, _skillButton.rc.left, _skillButton.rc.top, 0, 2);
	IMAGEMANAGER->findImage("bigBox")->frameRender(hdc, _featButton.rc.left, _featButton.rc.top, 0, 3);*/
	IMAGEMANAGER->findImage("skillIcon")->render(hdc, _skillButton.rc.left - 15, _skillButton.rc.top - 3);
	IMAGEMANAGER->findImage("featIcon")->render(hdc, _featButton.rc.left - 15, _featButton.rc.top - 3);
	
	for (int i = 0; i < 11; i++)
	{
		Rectangle(hdc, _weaponButton[i].rc); 
	}
}

void equipment::buttonSetting()
{
	_skillButton.rc = RectMake(WINSIZEX / 2 - 160, 140,120, 60);
	_featButton.rc = RectMake(WINSIZEX / 2 + 40, 140,120, 60);


	for (int i = 0; i < 11; i++)
	{
		_weaponButton[i].rc = RectMake(WINSIZEX / 5 + i * 65, WINSIZEY / 2 - 50, 50  , 100);
	}
}
