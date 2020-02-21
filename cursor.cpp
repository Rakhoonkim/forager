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
	_cursor.x = CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x;
	_cursor.y = CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y;
	_cursor.idx = _cursor.x / 60;
	_cursor.idy = _cursor.y / 60;
	//cout << " idx : " << _cursor.idx << " idy " << _cursor.idy << endl;
}

void cursor::render()
{
}

void cursor::imageChange()
{
}

void cursor::imageChangeInven()
{
}

void cursor::imageChange3x3()
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

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■buildcursor■■■■■■■■■■■■■■■■■■■■■■■■■■

cursorBuild::~cursorBuild()
{
}

void cursorBuild::render()
{
	_cursor.image->aniRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + _cursor.x, CAMERAMANAGER->getWorldCamera().cameraY + _cursor.y + 10, _cursor.ani);
}

void cursorBuild::imageChange()
{
	if (!_change) return;
	_ObjectPoint = true;	//오브젝트를 가리킨다 
	_cursor.image = IMAGEMANAGER->findImage("2x2cursor");
	_cursor.ani = KEYANIMANAGER->findAnimation("2x2cursor");
	_cursor.ani->start();
	_change = false;
}

void cursorBuild::setCursorXY(float x, float y)
{
	_cursor.x = x - _cursor.image->getFrameWidth() / 2;
	_cursor.y = y - _cursor.image->getFrameHeight() / 2;
}


//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■buildcursor■■■■■■■■■■■■■■■■■■■■■■■■■■

cursorFarming::~cursorFarming()
{
}

void cursorFarming::render()
{
	_cursor.image->aniRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + _cursor.x, CAMERAMANAGER->getWorldCamera().cameraY + _cursor.y + 10, _cursor.ani);
}

void cursorFarming::imageChange()
{
	if (!_change) return;
	_ObjectPoint = true;	//오브젝트를 가리킨다 
	_cursor.image = IMAGEMANAGER->findImage("1x1cursorB");
	_cursor.ani = KEYANIMANAGER->findAnimation("1x1cursorB");
	_cursor.ani->start();
	_change = false;
}

void cursorFarming::setCursorXY(float x, float y)
{
	_cursor.x = x - _cursor.image->getFrameWidth() / 2;
	_cursor.y = y - _cursor.image->getFrameHeight() / 2;
}


//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■EnemyBoss■■■■■■■■■■■■■■■■■■■■■■■■■■


cursorEnemyBoss::~cursorEnemyBoss()
{
}

void cursorEnemyBoss::render()
{
	_cursor.image->aniRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + _cursor.x, CAMERAMANAGER->getWorldCamera().cameraY + _cursor.y + 10, _cursor.ani);
}

void cursorEnemyBoss::imageChange()
{
	if (!_change) return;
	_ObjectPoint = true;	//오브젝트를 가리킨다 
	_cursor.image = IMAGEMANAGER->findImage("3x3cursor");
	_cursor.ani = KEYANIMANAGER->findAnimation("3x3cursor");
	_cursor.ani->start();
	_change = false;
}

void cursorEnemyBoss::setCursorXY(float x, float y)
{
	_cursor.x = x - _cursor.image->getFrameWidth() / 2;
	_cursor.y = y - _cursor.image->getFrameHeight() / 2;
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■Invencursor■■■■■■■■■■■■■■■■■■■■■■■■■■

cursorInven::~cursorInven()
{
}

void cursorInven::render()
{
	_cursor.image->aniRender(_backBuffer->getMemDC(), _cursor.x,  _cursor.y, _cursor.ani);
}

void cursorInven::imageChange()
{
	if (!_change) return;
	_ObjectPoint = false;	//오브젝트를 가리킨다 
	_cursor.image = IMAGEMANAGER->findImage("invenSlotCursor");
	_cursor.ani = KEYANIMANAGER->findAnimation("invenSlotCursor");
	_cursor.ani->start();
	_change = false;
}

void cursorInven::setCursorXY(float x, float y)
{
	_cursor.x = x - _cursor.image->getFrameWidth() / 2;
	_cursor.y = y - _cursor.image->getFrameHeight() / 2;
}
