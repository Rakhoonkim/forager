#include "stdafx.h"
#include "skill.h"

skill::skill()
{
}

skill::~skill()
{
}

HRESULT skill::init()
{
	_startX = WINSIZEX / 2 - 190;	 // 스킬 타일의 X 시작점
	_startY = WINSIZEY / 2 - 190;    // 스킬 타일의 Y 시작점 
	_tileSize = 80;		 // 80 크기
	_skillPoint = 0;

	_offsetX = 0;
	_offsetY = 0;
	skillSetting();
	return S_OK;
}

void skill::release()
{
}

void skill::update()
{
	if (_offsetX > 1200) _offsetX = 0;
	if (_offsetY > 720) _offsetY = 0;
	buttonClick();
}

void skill::render(HDC hdc)
{
	_offsetX++;
	_offsetY++;
	IMAGEMANAGER->findImage("skillBackground")->loopRender(hdc, &RectMake(0, 0, WINSIZEX, WINSIZEY), _offsetX, _offsetY);
	
	IMAGEMANAGER->findImage("skillPoint")->render(hdc, WINSIZEX / 2 - 130, 50);
	
	//스킬포인트 추가 
	if ((*_skillPoint) < 10)
	{
		IMAGEMANAGER->findImage("whiteNum")->frameRender(hdc, WINSIZEX / 2 + 70, 50, (*_skillPoint), 0);
	}
	//10자리 시 추가 예정 
	
	// 스킬 타일
	for (int i = 0; i < SKILLX * SKILLY; i++)
	{
		IMAGEMANAGER->findImage("skillTile")->alphaFrameRender(hdc, _skill[i].x, _skill[i].y, _skill[i].frameX, _skill[i].frameY, _skill[i].alpha);
	}

	// 필요한 스킬 포인트
	for (int i = 0; i < SKILLX * SKILLY; i++)
	{
		if (PtInRect(&_skill[i].rc, _ptMouse))
		{
			IMAGEMANAGER->findImage("needPoint")->render(hdc, WINSIZEX / 2 - 130, _skill[14].rc.bottom + 30);
			IMAGEMANAGER->findImage("whiteNum")->frameRender(hdc, WINSIZEX / 2 + 70, _skill[14].rc.bottom + 30,_skill[i].skillPoint,0);
		}
	}

}

void skill::skillSetting()
{
	for (int i = 0; i < SKILLY; i++)
	{
		for (int j = 0; j < SKILLX; j++)
		{
			SetRect(&_skill[i * SKILLX + j].rc, _startX + ((_tileSize + 20) * j) , _startY + ((_tileSize + 20)* i), _startX + _tileSize + ((_tileSize + 20) * j), _startY + ((_tileSize + 20) * i) + _tileSize);
			_skill[i * SKILLX + j].frameX = j;
			_skill[i * SKILLX + j].frameY = i;
			_skill[i * SKILLX + j].alpha = 150;
			_skill[i * SKILLX + j].isClick = false;
			_skill[i * SKILLX + j].isUse = false;
			_skill[i * SKILLX + j].x = _skill[i * SKILLX + j].rc.left;
			_skill[i * SKILLX + j].y = _skill[i * SKILLX + j].rc.top;
			_skill[i * SKILLX + j].skillPoint = 1;
		}
	}

	// 0 1 2 3
	// 4 5 6 7
	// 8 9 10 11
	// 12 13 14 15

	//스킬 포인트 정의
	_skill[1].skillPoint = 2;
	_skill[2].skillPoint = 2;
	_skill[4].skillPoint = 2;
	_skill[8].skillPoint = 2;
	_skill[7].skillPoint = 2;
	_skill[11].skillPoint = 2;
	_skill[13].skillPoint = 2;
	_skill[14].skillPoint = 2;

	_skill[0].skillPoint = 3;
	_skill[3].skillPoint = 3;
	_skill[12].skillPoint = 3;
	_skill[15].skillPoint = 3;
}

void skill::buttonClick()
{
	//클릭하면 
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < SKILLX * SKILLY; i++)
		{
			if (PtInRect(&_skill[i].rc, _ptMouse) && (*_skillPoint) >= _skill[i].skillPoint)
			{
				(*_skillPoint)--;
				_skill[i].alpha = 0;
				_skill[i].isClick = true;
				break;
			}
		}
	}
}
