#include "stdafx.h"
#include "building.h"

building::building()
{
}

building::~building()
{
}

HRESULT building::init(BUILDING building, const char* imageName, int idx, int idy)
{
	_building.object = OBJECT::NONE;
	_building.tree = TREE::NONE;

	_building.imageName = imageName;
	_building.building = building;
	_building.idx = idx;
	_building.idy = idy;
	_building.x = idx * 60 + 60;
	_building.y = idy * 60 + 60;
	_building.frameX = 0;
	_building.frameY = 0;

	// 건물마다 센터가 달라야 함
	_building.centerX = idx * 60 + 60;		// 4개 중 가운데 
	_building.centerY = idy * 60 + 60;		// 4개 중 


	//건물마다 달리해줘야 하는 값
	_building.hp = 0;
	_building.maxHp = 0;

	_building.isClick = false;

	_building.rc = RectMakeCenter(_building.x, _building.y, IMAGEMANAGER->findImage(imageName)->getWidth(), IMAGEMANAGER->findImage(imageName)->getHeight());
	return S_OK;
}

void building::release()
{
}

void building::update()
{
}

void building::render()
{
}

void building::setHp(int maxHp, int hp)
{
	_building.maxHp = maxHp;
	_building.hp = hp;
}

//■■■■■■■■■■■■■■■■■■■■■■ imageBuilding ■■■■■■■■■■■■■■■■■■■■■■

void imageBuilding::update()
{
}

void imageBuilding::render()
{
	IMAGEMANAGER->findImage(_building.imageName)->render(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage(_building.imageName)->getWidth() / 2), _building.y - (IMAGEMANAGER->findImage(_building.imageName)->getHeight() / 2)- 30);
	//Rectangle(CAMERAMANAGER->getWorldDC(), _building.rc);
}

//■■■■■■■■■■■■■■■■■■■■■■ frameBuilding ■■■■■■■■■■■■■■■■■■■■■■

void frameBuilding::update()
{
}

void frameBuilding::render()
{
	IMAGEMANAGER->findImage(_building.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _building.x -(IMAGEMANAGER->findImage(_building.imageName)->getFrameWidth() / 2), _building.y - (IMAGEMANAGER->findImage(_building.imageName)->getFrameHeight() / 2) - 15);

}
