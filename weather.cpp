#include "stdafx.h"
#include "weather.h"

weather::weather()
{
}

weather::~weather()
{
}

HRESULT weather::init()
{
	_time = TIMEMANAGER->getWorldTime();
	_night = false;
	_alpha = 0;

	return S_OK;
}

void weather::release()
{
}

void weather::update()
{
	if (_time + 120 <= TIMEMANAGER->getWorldTime())
	{
		_time = TIMEMANAGER->getWorldTime();
		
		if (!_night)
		{
			_night = true;
		}
		else
		{
			_night = false;
		}
	
	}

	if (_night)
	{
		if (_alpha < 100)
		{
			_alpha++;
		}
	}
	else
	{
		if (_alpha > 0) _alpha--;
	}
}

void weather::render(HDC hdc)
{
	//IntersectClipRect(hdc, WINSIZEX / 2, WINSIZEY / 2, WINSIZEX / 2 + 100, WINSIZEY / 2 + 100); // 이 부분만 그리고 
	//ExcludeClipRect(hdc, WINSIZEX / 2, WINSIZEY / 2, WINSIZEX / 2 + 100, WINSIZEY / 2 + 100); 이부분 빼고
	IMAGEMANAGER->findImage("startBackground")->alphaRender(hdc, 0, 0, _alpha);
}
