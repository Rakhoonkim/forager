#include "stdafx.h"
#include "build.h"

build::build()
{
}

build::~build()
{
}

HRESULT build::init()
{
	_listHeight = IMAGEMANAGER->findImage("bigLongBox")->getFrameHeight();
	_listWidth = IMAGEMANAGER->findImage("bigLongBox")->getFrameWidth();

	//4가지 리스트 초기화 
	for (int i = 0; i < MAXLIST; i++)
	{
		_buildList[i].rc = RectMake(WINSIZEX - 250, 25 + (_listHeight + 10) * i, _listWidth , _listHeight);
		_buildList[i].isClick = false;
		_buildList[i].isEffect = false;
	}
	//산업 리스트 초기화   == 0번 
	for (int i = 0; i < MAXINDUSTRY; i++)
	{
		_industryList[i].rc = RectMake(_buildList[0].rc.left, _buildList[0].rc.bottom + (IMAGEMANAGER->findImage("industry")->getFrameHeight() + 5) * i, 156, IMAGEMANAGER->findImage("industry")->getFrameHeight());
		_industryList[i].isClick = false;
		_industryList[i].isEffect = false;
	}
	//농업 리스트 초기화   == 1번
	for (int i = 0; i < MAXFARMING; i++)
	{
		_farmingList[i].rc = RectMake(_buildList[1].rc.left, _buildList[1].rc.top + (IMAGEMANAGER->findImage("farming")->getFrameHeight() + 5) * i, 156, IMAGEMANAGER->findImage("farming")->getFrameHeight());
		_farmingList[i].isClick = false;
		_farmingList[i].isEffect = false;
	}

	_direction = 0;

	return S_OK;
}

void build::release()
{
}

void build::update()
{
	buttonClick();
	listOpen();
}

void build::render()
{
}

void build::render(HDC hdc)
{
	for (int i = 0; i < 4; i++)
	{
		IMAGEMANAGER->findImage("bigLongBox")->frameRender(hdc, _buildList[i].rc.left, _buildList[i].rc.top,0,i);
		Rectangle(hdc, _buildList[i].rc);
	}
	IMAGEMANAGER->findImage("longBox")->frameRender(hdc,WINSIZEX / 2, WINSIZEY/2, 0,0);

	for (int i = 0; i < 3; i++)
	{
		if (!_buildList[0].isClick) break;
		Rectangle(hdc, _industryList[i].rc);
	}
}

void build::buttonClick()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXLIST; i++)
		{
			if (PtInRect(&_buildList[i].rc, _ptMouse))
			{
				_direction = i;
			}
		}
	}

	for (int i = 0; i < MAXLIST; i++)
	{
		if (i == _direction)
		{
			_buildList[i].isClick = true;
		}
		else
		{
			_buildList[i].isClick = false;
		}
	}
}

void build::listOpen()
{
	if (_buildList[0].isClick)
	{
		for (int i = 0; i < MAXLIST; i++)
		{
			if (i == 0) continue;
			_buildList[i].rc = RectMake(WINSIZEX - 250, _industryList[2].rc.top + 25 + (_listHeight + 10) * i, _listWidth, _listHeight);
		}
	}
}
