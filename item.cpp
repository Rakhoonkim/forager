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
	_item.speed = 4;

	_item.angle = RND->getFromFloatTo(0.00f, 6.28f);
	_item.time = TIMEMANAGER->getWorldTime();

	_item.alpha = 0;
	_item.frameX = 0;
	_item.frameY = 0;

	_item.move = true;
	_item.isClick = false;
	_item.drop = false;

	_item.stemina = 0;
	_item.heart = 0;
	_item.isUse = false;
	_item.rc = RectMake(x, y, IMAGEMANAGER->findImage(imageName)->getFrameWidth(), IMAGEMANAGER->findImage(imageName)->getFrameHeight());

	_item.object = OBJECT::NONE;
	_item.tree = TREE::NONE;

	//jump
	_item.jumpPower = 10;
	_item.jumpGravity = 1.2;

	_itemState = new itemState;
	_itemState->init(&_item);

	_itemDrop = new itemDrop(&_item);

	_itemGain = new itemGain(&_item);

	_itemState = _itemDrop;

	return S_OK;
}

void item::release()
{
}

void item::update()
{
	_itemState->update();

	_item.rc = RectMake(_item.x, _item.y, IMAGEMANAGER->findImage(_item.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_item.imageName)->getFrameHeight());
}

void item::render()
{
	_itemState->render();
}

void item::setGain(float x, float y)
{
	if (_itemState == _itemGain) return;
	_itemState = _itemGain;
	_item.angle = getAngle(_item.x, _item.y, x, y);
	_item.time = TIMEMANAGER->getWorldTime();
	_item.move = true;
}

void item::setIvenFrame(int x, int y)
{
	_item.frameX = x;
	_item.frameY = y;
}
