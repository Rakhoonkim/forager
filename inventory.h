#pragma once
#include "stdafx.h"

#define INVENX 8
#define INVENY 3
class inventory 
{
private:
	//���濡 �ִ� �����۵� 
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

	void addInven(const char* imageName,int frameX, int frameY);		// �κ��丮 �߰� 
	void removeInven(const char* imageName, int count);

	void invenSetting();
	void invenItemCountRecder(HDC hdc);
	map<const char*, tagInven> getInven() { return _mInven; }

	//recipes ������ 
	bool foranceRecipes(FURNACERECIPE recipe, int count);
	bool forgeRecipes(FORGERECIPE recipe, int count);
	bool sweingRecipes(SEWINGRECIPE recipe, int count);

};

