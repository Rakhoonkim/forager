#include "stdafx.h"
#include "alphaEffect.h"

alphaEffect::alphaEffect()
{
}

alphaEffect::~alphaEffect()
{
}

HRESULT alphaEffect::init()
{
	return S_OK;
}

void alphaEffect::release()
{
	vector<tagAlphaEffect*>::iterator  iter = _vAlphaEffect.begin();
	for (iter; iter != _vAlphaEffect.end(); iter++)
	{
		if (!(*iter)->isRender) continue;
		if ((*iter)->isRender)
		{
			_vAlphaEffect.erase(iter);
			break;
		}
	}
}

void alphaEffect::update()
{
	move();
}

void alphaEffect::render()
{
	vector<tagAlphaEffect*>::iterator  iter = _vAlphaEffect.begin();
	for (iter; iter != _vAlphaEffect.end(); iter++)
	{
		if (!(*iter)->isRender) continue;

		IMAGEMANAGER->findImage((*iter)->imageName)->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*iter)->x, (*iter)->y, (*iter)->frameX, (*iter)->frameY, (*iter)->alpha);
	}
}

void alphaEffect::move()
{
	vector<tagAlphaEffect*>::iterator  iter = _vAlphaEffect.begin();
	for (iter; iter != _vAlphaEffect.end(); iter++)
	{
		if (!(*iter)->isRender) continue;
		(*iter)->alpha += 5;

		(*iter)->y -= 10 * TIMEMANAGER->getElapsedTime();

		if ((*iter)->alpha >= 250)
		{
			(*iter)->isRender = false;
		}
	}
}

void alphaEffect::play(const char* imageName,int value, float x, float y)
{
	vector<int> temp;
	temp.push_back(10);  // +
	temp.push_back(11);  // X
	temp.push_back(12);  // P

	//+ 숫자 XP 형식에 맞게 중간에 삽입하기 
	if (value < 10)
	{
		temp.insert(temp.begin() + 1, value);	// 1의 자리 
	}
	else if (value >= 10)
	{
		temp.insert(temp.begin() + 1, value % 10);  // 10의자리
		temp.insert(temp.begin() + 1, value / 10);  // 1의자리
	}

	// 숫자 추가 
	for (int i = 0; i < temp.size(); i++)
	{
		tagAlphaEffect* tempEffect;
		tempEffect = new tagAlphaEffect;
		tempEffect->imageName = imageName;
		tempEffect->alpha = 0;
		tempEffect->x = x + (i * 15);
		tempEffect->y = y;
		tempEffect->frameX = temp[i];
		tempEffect->frameY = 0;
		tempEffect->isRender = true;  // 렌더 시작 
		_vAlphaEffect.push_back(tempEffect);
	}
}
