#pragma once
#include "itemState.h"

class item 
{
private:
	tagItem _item;

	itemState* _itemState;
	itemDrop* _itemDrop;
	itemGain* _itemGain;
public:
	item();
	~item();

	HRESULT init(const char* imageName, float x, float y);
	void release();
	void update();
	void render();

	void setObject(OBJECT object)	{ _item.object = object; }
	void setTree(TREE tree)			{ _item.tree = tree; }

	void setGain(float x, float y);

	tagItem* getItem() { return &_item; }
};

