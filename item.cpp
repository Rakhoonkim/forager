#include "stdafx.h"
#include "item.h"

item::item()
{
}

item::~item()
{
}

HRESULT item::init(const char* imageName, float x, float y)
{
	_item.imageName = imageName;
	_item.ani = KEYANIMANAGER->findAnimation(imageName);
	_item.ani->start();
	_item.x = x;
	_item.y = y;
	_item.speed = 5;
	_item.rc = RectMake(x, y, IMAGEMANAGER->findImage(imageName)->getFrameWidth(), IMAGEMANAGER->findImage(imageName)->getFrameHeight());
	_item.angle = RND->getFromFloatTo(0.00f, 6.28f);
	_item.move = true;
	_item.time = TIMEMANAGER->getWorldTime();
	_item.isClick = false;
	_item.drop = false;
	return S_OK;
}

void item::release()
{
}

void item::update()
{
	move();
	dropMove();
	_item.rc = RectMake(_item.x, _item.y, IMAGEMANAGER->findImage(_item.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_item.imageName)->getFrameHeight());

}

void item::render()
{
	IMAGEMANAGER->findImage(_item.imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _item.x, _item.y, _item.ani);
	Rectangle(CAMERAMANAGER->getWorldDC(), _item.rc);
}

void item::move()
{
	if (!_item.move) return;


	_item.x += cosf(_item.angle) * _item.speed;
	_item.y += -sinf(_item.angle) * _item.speed;

	if (_item.time + 0.2 <= TIMEMANAGER->getWorldTime())
	{
		_item.move = false;
	}
}

void item::dropMove()
{
	if (!_item.drop)return;

	_item.x += cosf(_item.angle) * _item.speed;
	_item.y += -sinf(_item.angle) * _item.speed;

	if (_item.time + 0.2 <= TIMEMANAGER->getWorldTime())
	{
		_item.isClick = true;
		_item.drop = true;

	}

}

void item::setDrop(float x, float y)
{
	_item.angle = getAngle(_item.x, _item.y, x, y);
	_item.time = TIMEMANAGER->getWorldTime();
	_item.drop = true;

}
