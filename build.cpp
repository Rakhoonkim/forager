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
		_buildList[i].rc = RectMake(WINSIZEX - 250, 25 + (_listHeight + 10) * i, _listWidth, _listHeight);
		_buildList[i].isClick = false;
		_buildList[i].isEffect = false;
	}
	//산업 리스트 초기화   == 0번 
	for (int i = 0; i < MAXINDUSTRY; i++)
	{
		_industryList[i].rc = RectMake(WINSIZEX - 200, 10 + _buildList[0].rc.bottom + (IMAGEMANAGER->findImage("industry")->getFrameHeight() + 5) * i, 156, IMAGEMANAGER->findImage("industry")->getFrameHeight());
		_industryList[i].isClick = false;
		_industryList[i].isEffect = false;
	}
	//농업 리스트 초기화   == 1번
	for (int i = 0; i < MAXFARMING; i++)
	{
		_farmingList[i].rc = RectMake(WINSIZEX - 200, 10 + _buildList[1].rc.bottom + (IMAGEMANAGER->findImage("farming")->getFrameHeight() + 5) * i, 156, IMAGEMANAGER->findImage("farming")->getFrameHeight());
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

}

void build::render()
{
}

void build::render(HDC hdc)
{
	for (int i = 0; i < 4; i++)
	{
		IMAGEMANAGER->findImage("bigLongBox")->frameRender(hdc, _buildList[i].rc.left, _buildList[i].rc.top, 0, i);
		//Rectangle(hdc, _buildList[i].rc);

		//char str[100];
		//sprintf_s(str, "참값 : %d", _buildList[i].isClick);
		//TextOut(hdc, _buildList[i].rc.left, _buildList[i].rc.top, str, strlen(str));
	}

	for (int i = 0; i < 3; i++)
	{
		if (!_buildList[0].isClick) break;
		IMAGEMANAGER->findImage("industry")->frameRender(hdc, _industryList[i].rc.left, _industryList[i].rc.top, 0, i);
		//Rectangle(hdc, _industryList[i].rc);
	}

	for (int i = 0; i < 2; i++)
	{
		if (!_buildList[1].isClick) break;
		IMAGEMANAGER->findImage("farming")->frameRender(hdc, _farmingList[i].rc.left, _farmingList[i].rc.top, 0, i);
		//Rectangle(hdc, _farmingList[i].rc);
	}
}

void build::buttonClick()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 2; i++)
		{
			if (PtInRect(&_buildList[i].rc, _ptMouse))
			{
				_direction = i;


				if (!_buildList[_direction].isClick)
				{
					_buildList[_direction].isClick = true;
				}
				else _buildList[_direction].isClick = false;

				for (int i = 0; i < MAXLIST; i++)
				{
					if (_buildList[i].isClick && _direction != i) _buildList[i].isClick = false;
				}


				break;
			}
		}

	/*	for (int i = 0; i < MAXLIST; i++)
		{
			_buildList[i].isClick = false;
		}*/


		
	/*	for (int i = 0; i < MAXLIST; i++)
		{
			if (_direction == i)
			{
				_buildList[i].isClick = true;
			}
			else _buildList[i].isClick = false;
		}*/

		listOpen();
	}

}

void build::listOpen()
{
	for (int i = 0; i < MAXLIST; i++)
	{
		_buildList[i].rc = RectMake(WINSIZEX - 250, 25 + (_listHeight + 10) * i, _listWidth, _listHeight);
	}

	if (_buildList[0].isClick)
	{
		for (int i = 0; i < MAXLIST; i++)
		{
			if (i == 0) continue;
			_buildList[i].rc = RectMake(WINSIZEX - 250, 20 + _industryList[2].rc.bottom + (_listHeight + 10) * (i - 1), _listWidth, _listHeight);
		}
	}
	else if (_buildList[1].isClick)
	{
		for (int i = 0; i < MAXLIST; i++)
		{
			if (i == 0) continue;
			if (i == 1) continue;
			_buildList[i].rc = RectMake(WINSIZEX - 250, 20 + _farmingList[1].rc.bottom + (_listHeight + 10) * (i -2), _listWidth, _listHeight);
		}
	}
}
