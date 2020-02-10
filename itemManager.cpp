#include "stdafx.h"
#include "itemManager.h"

itemManager::itemManager()
{
}

itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	imageSetting();
	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->update();
	}
	removeItem();
}

void itemManager::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->render();
	}
}

void itemManager::imageSetting()
{
	IMAGEMANAGER->addFrameImage("woodDrop", "./image/item/woodDrop.bmp", 720, 36, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("beetDrop", "./image/item/beetDrop.bmp", 600, 30, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("berryDrop", "./image/item/berryDrop.bmp", 720, 32, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cactusDrop", "./image/item/cactusDrop.bmp", 720, 36, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cinderbloomDrop", "./image/item/cinderbloomDrop.bmp", 480, 30, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("citrusDrop", "./image/item/citrusDrop.bmp", 680, 36, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coalDrop", "./image/item/coalDrop.bmp", 520, 24, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fiberDrop", "./image/item/fiberDrop.bmp", 640, 30, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("flowerDrop", "./image/item/flowerDrop.bmp", 440, 30, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("goldOreDrop", "./image/item/goldOreDrop.bmp", 600, 24, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hotPepperDrop", "./image/item/hotPepperDrop.bmp", 640, 28, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ironOreDrop", "./image/item/ironOreDrop.bmp", 600, 24, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lavenderDrop", "./image/item/lavenderDrop.bmp", 480, 28, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("nightshadeDrop", "./image/item/nightshadeDrop.bmp", 600, 26, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pumpkinDrop", "./image/item/pumpkinDrop.bmp", 680, 34, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("stoneDrop", "./image/item/stoneDrop.bmp", 600, 24, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wheatDro", "./image/item/wheatDrop.bmp", 720, 36, 20, 1, true, RGB(255, 0, 255));

	KEYANIMANAGER->addDefaultFrameAnimation("woodDrop", "woodDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("beetDrop", "beetDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("berryDrop", "berryDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("cactusDrop", "cactusDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("cinderbloomDrop", "cinderbloomDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("citrusDrop", "citrusDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("coalDrop", "coalDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("fiberDrop", "fiberDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("goldOreDrop", "goldOreDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("hotPepperDrop", "hotPepperDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("ironOreDrop", "ironOreDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("lavenderDrop", "lavenderDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("nightshadeDrop", "nightshadeDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("pumpkinDrop", "pumpkinDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("stoneDrop", "stoneDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("wheatDro", "wheatDro", 30, false, true);


}

void itemManager::Dropitem(const char* imageName, float x, float y)
{
	item* tempItem;
	tempItem = new item;
	tempItem->init(imageName, x, y);
	//tagItem* item;
	//item = new tagItem;
	//item->imageName = imageName;
	//item->ani = KEYANIMANAGER->findAnimation(imageName);
	//item->isClick = false;
	//item->x = x;
	//item->y = y;
	//item->rc = RectMake(x, y, IMAGEMANAGER->findImage(imageName)->getFrameWidth(), IMAGEMANAGER->findImage(imageName)->getFrameHeight());
	//item->ani->start();
	_vItem.push_back(tempItem);
}

void itemManager::removeItem()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem)->getItem()->isClick)
		{

			_vItem.erase(_viItem);
			break;
		}
	}
}
