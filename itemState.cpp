#include "stdafx.h"
#include "itemState.h"

itemState::itemState()
{
}

itemState::~itemState()
{
}

HRESULT itemState::init(tagItem* item)
{
	_item = item;
	return S_OK;
}

void itemState::release()
{
}

void itemState::update()
{
}

void itemState::render()
{
}

void itemState::jump()
{
}

void itemState::move()
{
}

//������������������������������� ������ ������ �� ����������������������������

void itemDrop::update()
{
	move();
	jump();
}

void itemDrop::render()
{
	IMAGEMANAGER->findImage(_item->imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _item->x, _item->y, _item->ani);
}

void itemDrop::jump()
{
	if (!_item->move) return;

	_item->y -= _item->jumpPower;
	_item->jumpPower -= _item->jumpGravity;
	/*_item->jumpGravity += 0.1f;*/
}

void itemDrop::move()
{
	if (!_item->move) return;

	_item->x += cosf(_item->angle) * _item->speed;
	_item->y += -sinf(_item->angle) * _item->speed;
	
	//0.25�ʰ� ������ ��� ������ ���°� �ȴ�
	if (_item->time + 0.25 <= TIMEMANAGER->getWorldTime())
	{
		_item->move = false;
		_item->drop = true;
	}
}

//������������������������������� ������ ȹ�� �� �� ����������������������������

void itemGain::update()
{
	move();
}

void itemGain::render()
{
	IMAGEMANAGER->findImage(_item->imageName)->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _item->x, _item->y, 0, 0, _item->alpha);
}

void itemGain::move()
{
	if (!_item->move)return;

	_item->x += cosf(_item->angle) * _item->speed;
	_item->y += -sinf(_item->angle) * _item->speed;
	_item->alpha += 15;

	if (_item->time + 0.25 <= TIMEMANAGER->getWorldTime())
	{
		_item->isClick = true;
		_item->move = true;
	}
}
