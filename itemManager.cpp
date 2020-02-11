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
	IMAGEMANAGER->addFrameImage("woodDrop", "./image/item/woodDrop.bmp", 720, 36, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("beetDrop", "./image/item/beetDrop.bmp", 600, 30, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("berryDrop", "./image/item/berryDrop.bmp", 720, 32, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("cactusDrop", "./image/item/cactusDrop.bmp", 720, 36, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("cinderbloomDrop", "./image/item/cinderbloomDrop.bmp", 480, 30, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("citrusDrop", "./image/item/citrusDrop.bmp", 680, 36, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("coalDrop", "./image/item/coalDrop.bmp", 600, 24, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("fiberDrop", "./image/item/fiberDrop.bmp", 640, 30, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("flowerDrop", "./image/item/flowerDrop.bmp", 440, 30, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("goldOreDrop", "./image/item/goldOreDrop.bmp", 600, 24, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("hotPepperDrop", "./image/item/hotPepperDrop.bmp", 640, 28, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ironOreDrop", "./image/item/ironOreDrop.bmp", 520, 24, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("lavenderDrop", "./image/item/lavenderDrop.bmp", 480, 28, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("nightshadeDrop", "./image/item/nightshadeDrop.bmp", 600, 26, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("pumpkinDrop", "./image/item/pumpkinDrop.bmp", 680, 34, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("stoneDrop", "./image/item/stoneDrop.bmp", 600, 24, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("wheatDrop", "./image/item/wheatDrop.bmp", 720, 36, 20, 1, true, RGB(255, 0, 255), true);


	KEYANIMANAGER->addDefaultFrameAnimation("flowerDrop", "flowerDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("beetDrop", "beetDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("cinderbloomDrop", "cinderbloomDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("citrusDrop", "citrusDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("fiberDrop", "fiberDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("hotPepperDrop", "hotPepperDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("lavenderDrop", "lavenderDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("nightshadeDrop", "nightshadeDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("pumpkinDrop", "pumpkinDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("wheatDrop", "wheatDrop", 30, false, true);
	// 돌
	KEYANIMANAGER->addDefaultFrameAnimation("goldOreDrop", "goldOreDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("ironOreDrop", "ironOreDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("coalDrop", "coalDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("stoneDrop", "stoneDrop", 30, false, true);
	//나무 
	KEYANIMANAGER->addDefaultFrameAnimation("woodDrop", "woodDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("cactusDrop", "cactusDrop", 30, false, true);
	//두개다 
	KEYANIMANAGER->addDefaultFrameAnimation("berryDrop", "berryDrop", 30, false, true);
}

void itemManager::Dropitem(const char* imageName, float x, float y)
{
	item* tempItem;
	tempItem = new item;
	tempItem->init(imageName, x, y);
	_vItem.push_back(tempItem);
}

void itemManager::Dropitem(OBJECT object, float x, float y)
{
	if (object == OBJECT::BEET)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("beetDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::COTTON)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("fiberDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::WHEAT)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("wheatDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::BUSH)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("berryDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::FLOWER_1 ||
		object == OBJECT::FLOWER_2 ||
		object == OBJECT::FLOWER_3)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("flowerDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::HOT_PEPPER)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("hotPepperDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::PUMPKIN)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("pumpkinDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::LAVENDER)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("lavenderDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::CINDERBLOOM)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("cinderbloomDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::NIGHTSHADE)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("nightshadeDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}


	if (object == OBJECT::ROCK)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("stoneDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::COAL ||
		object == OBJECT::VOLCANIC_COAL)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("coalDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::GOLD ||
		object == OBJECT::VOLCANIC_GOLD)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("goldOreDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
	else if (object == OBJECT::IRON || object == OBJECT::VOLCANIC_IRON)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("ironOreDrop", x, y);
			tempItem->setObject(object);
			_vItem.push_back(tempItem);
		}
		return;
	}
}

void itemManager::Dropitem(TREE tree, float x, float y)
{
	if (tree == TREE::BASIC || tree == TREE::RED || tree == TREE::SNOW)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			if (RND->getInt(7) == 1)
			{
				item* tempItem;
				tempItem = new item;
				tempItem->init("citrusDrop", x, y);
				tempItem->setTree(tree);
				_vItem.push_back(tempItem);
			}
			else
			{
				item* tempItem;
				tempItem = new item;
				tempItem->init("woodDrop", x, y);
				tempItem->setTree(tree);
				_vItem.push_back(tempItem);
			}
		}
	}
	else if (tree == TREE::CACTUS)
	{
		for (int i = 0; i < RND->getInt(5) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("cactusDrop", x, y);
			tempItem->setTree(tree);
			_vItem.push_back(tempItem);
		}
	}
}

void itemManager::removeItem()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem)->getItem()->isClick)
		{
			//인벤토리 증가 예정 
			_vItem.erase(_viItem);
			break;
		}
	}
}
