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

	_inven = new inventory;
	_inven->init();

	UIMANAGER->setInven(_inven);
	
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
	IMAGEMANAGER->addFrameImage("ironOreDrop", "./image/item/ironOreDrop.bmp", 600, 24, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("coalDrop", "./image/item/coalDrop.bmp", 520, 24, 20, 1, true, RGB(255, 0, 255), true);
	
	
	IMAGEMANAGER->addFrameImage("woodDrop", "./image/item/woodDrop.bmp", 720, 36, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("beetDrop", "./image/item/beetDrop.bmp", 600, 30, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("berryDrop", "./image/item/berryDrop.bmp", 720, 32, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("cactusDrop", "./image/item/cactusDrop.bmp", 720, 36, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("cinderbloomDrop", "./image/item/cinderbloomDrop.bmp", 480, 30, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("citrusDrop", "./image/item/citrusDrop.bmp", 680, 36, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("fiberDrop", "./image/item/fiberDrop.bmp", 640, 30, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("flowerDrop", "./image/item/flowerDrop.bmp", 440, 30, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("goldOreDrop", "./image/item/goldOreDrop.bmp", 600, 24, 20, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("hotPepperDrop", "./image/item/hotPepperDrop.bmp", 640, 28, 20, 1, true, RGB(255, 0, 255), true);
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


	//buildManger  드랍 아이템 이미지
	IMAGEMANAGER->addFrameImage("breadDrop", "./image/item/buildItem/breadDrop.bmp", 720, 30, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("brickDrop", "./image/item/buildItem/brickDrop.bmp", 560, 26, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cookedFishDrop", "./image/item/buildItem/cookedFishDrop.bmp", 600, 30, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cookedMeatDrop", "./image/item/buildItem/cookedMeatDrop.bmp", 600, 30, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("goldingotDrop", "./image/item/buildItem/goldingotDrop.bmp", 560, 26, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grassDrop", "./image/item/buildItem/grassDrop.bmp", 560, 28, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ironingotDrop", "./image/item/buildItem/ironingotDrop.bmp", 560, 26, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("steelDrop", "./image/item/buildItem/steelDrop.bmp", 640, 22, 20, 1, true, RGB(255, 0, 255));

	//forge
	IMAGEMANAGER->addFrameImage("bottleDrop", "./image/item/buildItem/forge/bottleDrop.bmp", 640, 36, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coinDrop", "./image/item/buildItem/forge/coinDrop.bmp", 560, 28, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pickaxeDrop", "./image/item/buildItem/forge/pickaxeDrop.bmp",680, 34, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shovleDrop", "./image/item/buildItem/forge/shovleDrop.bmp", 720, 36, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("swordDrop", "./image/item/buildItem/forge/swordDrop.bmp", 640, 32, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("keyDrop", "./image/item/buildItem/forge/keyDrop.bmp", 440, 36, 20, 1, true, RGB(255, 0, 255));


	//sewing
	IMAGEMANAGER->addFrameImage("mediumBackpackDrop", "./image/item/buildItem/sweing/mediumBackpackDrop.bmp", 640, 34, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slimeWalletDrop", "./image/item/buildItem/sweing/slimeWalletDrop.bmp", 640, 32, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smallBackpackDrop", "./image/item/buildItem/sweing/smallBackpackDrop.bmp", 640, 32, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smallWalletDrop", "./image/item/buildItem/sweing/smallWalletDrop.bmp", 480, 30, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("threadDrop", "./image/item/buildItem/sweing/threadDrop.bmp", 720, 36, 20, 1, true, RGB(255, 0, 255));

	//buildManger 
	KEYANIMANAGER->addDefaultFrameAnimation("breadDrop", "breadDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("brickDrop", "brickDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("cookedFishDrop" ,"cookedFishDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("cookedMeatDrop", "cookedMeatDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("goldingotDrop", "goldingotDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("grassDrop", "grassDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("ironingotDrop", "ironingotDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("steelDrop", "steelDrop", 30, false, true);
	//forge
	KEYANIMANAGER->addDefaultFrameAnimation("bottleDrop", "bottleDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("coinDrop", "coinDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("pickaxeDrop", "pickaxeDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("shovleDrop", "shovleDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("swordDrop", "swordDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("keyDrop", "keyDrop", 30, false, true);
	//sewing
	KEYANIMANAGER->addDefaultFrameAnimation("mediumBackpackDrop", "mediumBackpackDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("slimeWalletDrop", "slimeWalletDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("smallBackpackDrop", "smallBackpackDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("smallWalletDrop", "smallWalletDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("threadDrop", "threadDrop", 30, false, true);


	//fishtrap
	IMAGEMANAGER->addFrameImage("fishDrop", "./image/item/buildItem/fishtrap/fishDrop.bmp", 600, 30, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("seaweedDrop", "./image/item/buildItem/fishtrap/seaweedDrop.bmp", 680, 32, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sandDrop", "./image/item/buildItem/fishtrap/sandDrop.bmp", 720, 26, 20, 1, true, RGB(255, 0, 255));

	KEYANIMANAGER->addDefaultFrameAnimation("sandDrop", "sandDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("seaweedDrop", "seaweedDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("fishDrop", "fishDrop", 30, false, true);


	//enemyItem
	IMAGEMANAGER->addFrameImage("jellyDrop", "./image/item/enemyItem/jellyDrop.bmp", 640, 32, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("meatDrop", "./image/item/enemyItem/meatDrop.bmp", 600, 30, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("demonHornDrop", "./image/item/enemyItem/demonHornDrop.bmp", 560, 30, 20, 1, true, RGB(255, 0, 255));
	KEYANIMANAGER->addDefaultFrameAnimation("jellyDrop", "jellyDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("meatDrop", "meatDrop", 30, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("demonHornDrop", "demonHornDrop", 30, false, true);

	//enemyInven
	//jelly 7, 1 


	

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
			tempItem->setIvenFrame(2, 1);
			tempItem->setObject(object);
			tempItem->setSteminaHeart(15, 0);
			tempItem->setItemUse();
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
			tempItem->setIvenFrame(5, 1);
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
			tempItem->setIvenFrame(4, 1);
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
			tempItem->setIvenFrame(3, 1);
			tempItem->setObject(object);
			tempItem->setSteminaHeart(15, 0);
			tempItem->setItemUse();
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
			tempItem->setIvenFrame(6, 1);
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
			tempItem->setIvenFrame(9, 0);
			tempItem->setObject(object);
			tempItem->setSteminaHeart(10, 0);
			tempItem->setItemUse();
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
			tempItem->setIvenFrame(0, 1);
			tempItem->setObject(object);
			tempItem->setSteminaHeart(10, 0);
			tempItem->setItemUse();
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
			tempItem->setIvenFrame(1, 1);
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
			tempItem->setIvenFrame(4, 0);
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
			tempItem->setIvenFrame(5, 0);
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
			tempItem->setIvenFrame(0, 0);
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
			tempItem->setIvenFrame(1, 0);
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
			tempItem->setIvenFrame(2, 0);
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
			tempItem->setIvenFrame(3, 0);
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
				tempItem->setIvenFrame(6, 0);
				tempItem->setTree(tree);
				tempItem->setSteminaHeart(10, 0);
				tempItem->setItemUse();
				_vItem.push_back(tempItem);
			}
			else
			{
				item* tempItem;
				tempItem = new item;
				tempItem->init("woodDrop", x, y);
				tempItem->setIvenFrame(8, 0);
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
			tempItem->setIvenFrame(7, 0);
			tempItem->setTree(tree);
			tempItem->setSteminaHeart(10, 0);
			tempItem->setItemUse();
			_vItem.push_back(tempItem);
		}
	}
}

void itemManager::DropFurnaceItem(FURNACERECIPE recipe, float x, float y, int num)
{
	if (recipe == FURNACERECIPE::COAL)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("coalDrop", x, y);
			tempItem->setIvenFrame(1, 0);
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FURNACERECIPE::BRICK)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("brickDrop", x, y);
			tempItem->setIvenFrame(0, 2);   // 수정 
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FURNACERECIPE::IRON)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("ironingotDrop", x, y);
			tempItem->setIvenFrame(1, 2);   // 수정 
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FURNACERECIPE::GOLD)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("goldingotDrop", x, y);
			tempItem->setIvenFrame(2, 2);   // 수정 
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FURNACERECIPE::STEEL)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("steelDrop", x, y);
			tempItem->setIvenFrame(3, 2);   // 수정 
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FURNACERECIPE::GLASS)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("grassDrop", x, y);
			tempItem->setIvenFrame(4, 2);   // 수정 
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FURNACERECIPE::BREAD)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("breadDrop", x, y);
			tempItem->setIvenFrame(5, 2);   // 수정 
			tempItem->setSteminaHeart(20, 1);
			tempItem->setItemUse();
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FURNACERECIPE::FISH)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("cookedFishDrop", x, y);
			tempItem->setIvenFrame(6, 2);   // 수정 
			tempItem->setSteminaHeart(20, 1);
			tempItem->setItemUse();
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FURNACERECIPE::MEAT)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("cookedMeatDrop", x, y);
			tempItem->setIvenFrame(7, 2);   // 수정
			tempItem->setSteminaHeart(20,1);
			tempItem->setItemUse();
			_vItem.push_back(tempItem);
		}
	}
	

}

void itemManager::DropForgeItem(FORGERECIPE recipe, float x, float y, int num)
{
	if (recipe == FORGERECIPE::COIN)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("coinDrop", x, y);		
			tempItem->setIvenFrame(0, 3);			
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FORGERECIPE::KEY)
	{
		item* tempItem;
		tempItem = new item;
		tempItem->init("keyDrop", x, y);
		tempItem->setIvenFrame(8, 2);
		_vItem.push_back(tempItem);
	}
	else if (recipe == FORGERECIPE::SHOVEL)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("shovleDrop", x, y);		
			tempItem->setIvenFrame(1, 3);			 
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FORGERECIPE::SWORD)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("swordDrop", x, y);		
			tempItem->setIvenFrame(2, 3);			 
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FORGERECIPE::PICKAXE)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("pickaxeDrop", x, y);	
			tempItem->setIvenFrame(3, 3);			
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == FORGERECIPE::BOTTLE)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("bottleDrop", x, y);		
			tempItem->setIvenFrame(4, 3);			
			_vItem.push_back(tempItem);
		}
	}
}

void itemManager::DropsewingItem(SEWINGRECIPE recipe, float x, float y, int num)
{
	if (recipe == SEWINGRECIPE::THREAD)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("threadDrop", x, y);	
			tempItem->setIvenFrame(0, 4);			
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == SEWINGRECIPE::SMALL_BACKPACK)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("smallBackpackDrop", x, y);
			tempItem->setIvenFrame(1, 4);
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == SEWINGRECIPE::MEDIUM_BACKPACK)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("mediumBackpackDrop", x, y);
			tempItem->setIvenFrame(2, 4);
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == SEWINGRECIPE::SMALL_WALLET)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("smallWalletDrop", x, y);
			tempItem->setIvenFrame(3, 4);
			_vItem.push_back(tempItem);
		}
	}
	else if (recipe == SEWINGRECIPE::SLIME_WALLET)
	{
		for (int i = 0; i < num; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("slimeWalletDrop", x, y);
			tempItem->setIvenFrame(4, 4);
			_vItem.push_back(tempItem);
		}
	}

}

void itemManager::DropFishTrapItem(float x, float y)
{
	int rndNum;
	rndNum = RND->getFromIntTo(0, 10);

	if (rndNum <= 5)
	{
		item* tempItem;
		tempItem = new item;
		tempItem->init("fishDrop", x, y);
		tempItem->setSteminaHeart(10, 0);
		tempItem->setItemUse();
		tempItem->setIvenFrame(7, 3);
		_vItem.push_back(tempItem);
	}
	else if (rndNum > 5 && rndNum < 7)
	{
		item* tempItem;
		tempItem = new item;
		tempItem->init("seaweedDrop", x, y);
		tempItem->setIvenFrame(6, 3);
		_vItem.push_back(tempItem);
	}
	else
	{
		item* tempItem;
		tempItem = new item;
		tempItem->init("sandDrop", x, y);
		tempItem->setIvenFrame(5, 3);
		_vItem.push_back(tempItem);
	}
}

void itemManager::DropEnemyItem(ENEMY enemy, float x, float y)
{
	if (enemy == ENEMY::SLIME)
	{
		for (int i = 0; i < RND->getInt(2) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("jellyDrop", x, y);
			tempItem->setIvenFrame(7, 1);
			_vItem.push_back(tempItem);
		}
	}
	else if (enemy == ENEMY::BOAR)
	{
		for (int i = 0; i < RND->getInt(2) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("meatDrop", x, y);
			tempItem->setIvenFrame(8, 1);
			_vItem.push_back(tempItem);
		}
	}
	else if (enemy == ENEMY::DEMON || enemy == ENEMY::SKULL)
	{
		for (int i = 0; i < RND->getInt(2) + 1; i++)
		{
			item* tempItem;
			tempItem = new item;
			tempItem->init("demonHornDrop", x, y);
			tempItem->setIvenFrame(9, 1);
			_vItem.push_back(tempItem);
		}
	}
	else if (enemy == ENEMY::DEMON_BOSS)
	{
		for (int i = 0; i < RND->getInt(10) + 1; i++)
		{
			if (RND->getInt(2) == 1)
			{
				item* tempItem;
				tempItem = new item;
				tempItem->init("demonHornDrop", x, y);
				tempItem->setIvenFrame(9, 1);
				_vItem.push_back(tempItem);
			}
			else 
			{
				item* tempItem;
				tempItem = new item;
				tempItem->init("meatDrop", x, y);
				tempItem->setIvenFrame(8, 1);
				_vItem.push_back(tempItem);
			}

		}
	}
}

void itemManager::findItem()
{
}

void itemManager::removeItem()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem)->getItem()->isClick)
		{
			//인벤토리 증가 예정 
			//아이템의 프레임 x y 만들 예정 
			//_inven->addInven((*_viItem)->getItem()->imageName, (*_viItem)->getItem()->frameX, (*_viItem)->getItem()->frameY);
			UIMANAGER->getInven()->addInven((*_viItem)->getItem()->imageName, (*_viItem)->getItem()->frameX, (*_viItem)->getItem()->frameY, (*_viItem)->getItem()->stemina, (*_viItem)->getItem()->heart, (*_viItem)->getItem()->isUse);
			_vItem.erase(_viItem);
			break;
		}
	}
}
