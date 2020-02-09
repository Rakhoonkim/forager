#include "stdafx.h"
#include "cursor.h"
#include "gameNode.h"

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■cursor■■■■■■■■■■■■■■■■■■■■■■■■■■

cursor::cursor()
{
}

cursor::~cursor()
{
}

HRESULT cursor::init()
{
	_cursor.image = IMAGEMANAGER->findImage("cursor");
	_cursor.x = 0;
	_cursor.y = 0;
	_change = false;
	_ObjectPoint = false;
	return S_OK;
}

void cursor::release()
{

}

void cursor::update()
{

}

void cursor::render()
{
}

void cursor::imageChange()
{
}

void cursor::setCursorXY(float x, float y)
{
}

void cursor::setCursorChange()
{
	_change = true;
}


// ■■■■■■■■■■■■■■■■■■■■■■■■■■cursorBasic■■■■■■■■■■■■■■■■■■■■■■■■■■

cursorBasic::~cursorBasic()
{
}

void cursorBasic::update()
{
}

void cursorBasic::render()
{
	IMAGEMANAGER->findImage("cursor")->render(_backBuffer->getMemDC(), _ptMouse.x, _ptMouse.y);
}

void cursorBasic::imageChange()
{
	if (!_change) return;
	_ObjectPoint = false;
	_cursor.image = IMAGEMANAGER->findImage("cursor");
	_change = false;
}


// ■■■■■■■■■■■■■■■■■■■■■■■■■■cursorPoint■■■■■■■■■■■■■■■■■■■■■■■■■■

cursorPoint::~cursorPoint()
{
}

void cursorPoint::update()
{
}

void cursorPoint::render()
{
	// 임시로 y값 10만큼 증가 시켜놓음 
	_cursor.image->aniRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + _cursor.x, CAMERAMANAGER->getWorldCamera().cameraY + _cursor.y + 10,_cursor.ani);
}

void cursorPoint::imageChange()
{
	if (!_change) return;
	_ObjectPoint = true;	//오브젝트를 가리킨다 
	_cursor.image = IMAGEMANAGER->findImage("1x1cursor");
	_cursor.ani = KEYANIMANAGER->findAnimation("1x1cursor");
	_cursor.ani->start();
	_change = false;
}

void cursorPoint::setCursorXY(float x, float y)
{
	_cursor.x = x - _cursor.image->getFrameWidth() / 2;
	_cursor.y = y - _cursor.image->getFrameHeight() / 2;
}