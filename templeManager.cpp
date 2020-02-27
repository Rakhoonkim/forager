#include "stdafx.h"
#include "templeManager.h"

templeManager::templeManager()
{
}

templeManager::~templeManager()
{
}

HRESULT templeManager::init()
{
	imageSetting();

	blindRoomSetting();
	return S_OK;
}

void templeManager::release()
{
}

void templeManager::update()
{
	vector<temple*>::iterator iter = _vTemple.begin();
	for (; iter != _vTemple.end(); iter++)
	{
		(*iter)->update();
	}
	blindRoomCollision();
}

void templeManager::render()
{
	vector<temple*>::iterator iter = _vTemple.begin();
	for (; iter != _vTemple.end(); iter++)
	{
		(*iter)->render();
	}


	for (int i = 0; i < 8; i++)
	{
		if (_room[i].isOpen) continue;
		Rectangle(CAMERAMANAGER->getWorldDC(), _room[i].rc);
	}
}

void templeManager::blindRoomSetting()
{
	for (int i = 0; i < 8; i++)
	{
		_room[i].isOpen = false;
	}
	_room[0].rc = RectMake(0, 0, 900, 720);			// 보스방 
	_room[1].rc = RectMake(900, 0, 900, 660);		// (1,0) 방
	_room[2].rc = RectMake(1800, 0, 780, 540);

	_room[3].rc = RectMake(360, 720, 600, 840);	// 왼쪽 긴
	
	_room[4].rc = RectMake(1020, 660, 720, 480);	// 중앙 위
	_room[5].rc = RectMake(1020, 1140, 720, 420);	// 중앙 아래

	_room[6].rc = RectMake(360, 1560, 660, 540);	// 왼쪽 아래 
	_room[7].rc = RectMake(1740, 1560,660, 540);	// 오른쪽 아래

}

void templeManager::blindRoomCollision()
{
	for (int i = 0;i < 8;i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->rc, &_room[i].rc))
		{
			_room[i].isOpen = true;
		}
	}
}

void templeManager::imageSetting()
{
	IMAGEMANAGER->addFrameImage("lantern", "./image/temple/lantern.bmp", 240, 102, 5, 1, true, RGB(255, 0, 255));
	KEYANIMANAGER->addDefaultFrameAnimation("lantern", "lantern", 10, false, true);

	IMAGEMANAGER->addFrameImage("cannon", "./image/temple/cannon.bmp", 216, 54, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("templeDoor", "./image/temple/templeDoor.bmp", 480, 120, 4, 1, true, RGB(255, 0, 255));

}

void templeManager::CreateCannon(int idx, int idy, int frameX)
{
	temple* tempCannon;
	tempCannon = new cannon;
	tempCannon->init("cannon", idx, idy);
	tempCannon->setFrameX(frameX);
	tempCannon->setBulletManager(_bulletManager);
	_vTemple.push_back(tempCannon);
}

void templeManager::CreateLantern(int idx, int idy)
{
	temple* tempLantern;
	tempLantern = new lantern;
	tempLantern->init("lantern", idx, idy);
	_vTemple.push_back(tempLantern);
}

void templeManager::CreateDoor(int idx, int idy, int frameX)
{
	temple* tempDoor;
	tempDoor = new door;
	tempDoor->init("templeDoor", idx, idy);
	tempDoor->setFrameX(frameX);
	_vTemple.push_back(tempDoor);
}
