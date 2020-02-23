#include "stdafx.h"
#include "cursorManager.h"

cursorManager::cursorManager()
{
}

cursorManager::~cursorManager()
{
}

HRESULT cursorManager::init()
{
	imageSetting();

	_cursor = new cursor;
	_cursor->init();

	_cursorBasic = new cursorBasic;

	_cursorPoint = new cursorPoint;

	_cursorBuild = new cursorBuild;

	_cursorFarming = new cursorFarming;

	_cursorEnemyBoss = new cursorEnemyBoss;

	_cursorInven = new cursorInven;

	_cursor = _cursorBasic;

	return S_OK;
}

void cursorManager::release()
{
	_cursor->release();
}

void cursorManager::update()
{
	_cursor->update();
}

void cursorManager::render()
{
	_cursor->render();
}

void  cursorManager::imageSetting()
{
	IMAGEMANAGER->addImage("cursor", "./image/cursor/mouseCursor.bmp", 24, 24, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("1x1cursor", "./image/cursor/1x1cursor.bmp", 400, 40, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1x1cursorB", "./image/cursor/1x1cursorB.bmp", 640, 64, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2x2cursor", "./image/cursor/2x2cursor.bmp", 1100, 110, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("3x3cursor", "./image/cursor/3x3cursor.bmp", 1800, 180, 10, 1, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("invenSlotCursor", "./image/cursor/invenSlotCursor.bmp", 860, 90, 10, 1, true, RGB(255, 0, 255));
	KEYANIMANAGER->addDefaultFrameAnimation("invenSlotCursor", "invenSlotCursor", 10, false, true);


	KEYANIMANAGER->addDefaultFrameAnimation("1x1cursor", "1x1cursor", 10, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("1x1cursorB", "1x1cursorB", 10, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("2x2cursor", "2x2cursor", 10, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("3x3cursor", "3x3cursor", 10, false, true);

	IMAGEMANAGER->addFrameImage("landCursor", "./image/cursor/landCursor.bmp", 4000, 400, 10, 1, true, RGB(255, 0, 255));
	KEYANIMANAGER->addDefaultFrameAnimation("landCursor", "landCursor", 10, false, true);
}

void cursorManager::setCropsPoint()
{
	_cursor = _cursorPoint;
	_cursor->imageChange();
}

void cursorManager::setBuildPoint()
{
	_cursor = _cursorBuild;
	_cursor->imageChange();
}

void cursorManager::setBridgePoint()
{
	_cursor = _cursorFarming;
	_cursor->imageChange();
}

void cursorManager::setBossPoint()
{
	_cursor = _cursorEnemyBoss;
	_cursor->imageChange();
}

void cursorManager::setCursor()
{
	_cursor = _cursorBasic;
	_cursor->imageChange();
}

void cursorManager::setInvenCursor()
{
	_cursor = _cursorInven;
	_cursor->imageChange();
}
