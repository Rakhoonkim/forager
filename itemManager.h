#pragma once
#include "stdafx.h"
#include "singletonBase.h"
#include "item.h"

class itemManager : public singletonBase<itemManager> 
{
private:
	vector<item*>			_vItem;
	vector<item*>::iterator _viItem;


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

	void removeItem();

	vector<item*> getVItem()			{ return _vItem; }
	vector<item*>::iterator getViItem() { return _viItem; }
};

