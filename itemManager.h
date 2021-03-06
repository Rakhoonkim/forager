#pragma once
#include "stdafx.h"
#include "singletonBase.h"
#include "item.h"
#include "inventory.h"

class itemManager : public singletonBase<itemManager> 
{
private:
	vector<item*>			_vItem;
	vector<item*>::iterator _viItem;

	inventory* _inven;
public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();

	//ITEM
	void Dropitem(const char* imageName, float x, float y);
	void Dropitem(OBJECT object, float x, float y );
	void Dropitem(TREE tree, float x, float y);

	//RECIPE
	void DropFurnaceItem(FURNACERECIPE recipe, float x, float y, int num);
	void DropForgeItem(FORGERECIPE recipe, float x, float y, int num);
	void DropsewingItem(SEWINGRECIPE recipe, float x, float y, int num);
	void DropEnemyItem(ENEMY enemy, float x, float y);  // ENEMY
	void DropFishTrapItem(float x, float y);		    // FISHTRAP

	void removeItem();

	vector<item*> getVItem()			{ return _vItem; }
	vector<item*>::iterator getViItem() { return _viItem; }

	inventory* getInventory() { return _inven; }
};

