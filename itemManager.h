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
	void Dropitem(const char* imageName, float x, float y);
	void Dropitem(OBJECT object, float x, float y);
	void Dropitem(TREE tree, float x, float y);

	void findItem();
	void removeItem();

	vector<item*> getVItem()			{ return _vItem; }
	vector<item*>::iterator getViItem() { return _viItem; }
};
