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

	tagInven _inven[INVENX * INVENY];		         // 인벤토리의 최대 가방 수 

	tagButton _useButton;  // 사용버튼
	tagButton _disButton;  // 버리기 버튼

	float _invenStartX;
	int _invenSize;			// 인벤슬롯이 가로 세로 크기(정사각형)
	int _direction;
	bool _invenItemSlot;
public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC hdc);

	void addInven(const char* imageName,int frameX, int frameY,int stemina,int heart,bool use);		// 인벤토리 추가 
	void removeInven(const char* imageName, int count);
	void InvenPointer();												// 마우스 포인터 

	void invenMove();
	void invenSetting();
	void invenClick();
	void invenItemCountRecder(HDC hdc);
	int  invenNumber();							// 인벤토리의 숫자 반환 값 
	map<const char*, tagInven> getInven() { return _mInven; }

	//recipes 레시피 
	bool foranceRecipes(FURNACERECIPE recipe, int count);
	bool forgeRecipes(FORGERECIPE recipe, int count);
	bool sewingRecipes(SEWINGRECIPE recipe, int count);

};

