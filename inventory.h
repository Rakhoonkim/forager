#pragma once
#include "stdafx.h"

#define INVENX 8
#define INVENY 3
class inventory 
{
private:
	//가방에 있는 아이템들 
	map<const char*, tagInven>			   _mInven;  // INVEN
	map<const char*, tagInven>::iterator  _miInven;

	tagInven _inven[INVENX * INVENY];		

	int _invenSize;
public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC hdc);

	void addInven(const char* imageName,int frameX, int frameY);		// 인벤토리 추가 
	void removeInven(const char* imageName, int count);

	void invenSetting();
	void invenItemCountRecder(HDC hdc);
	map<const char*, tagInven> getInven() { return _mInven; }

	//recipes 레시피 
	bool foranceRecipes(FURNACERECIPE recipe, int count);
	bool forgeRecipes(FORGERECIPE recipe, int count);
	bool sweingRecipes(SEWINGRECIPE recipe, int count);

};

