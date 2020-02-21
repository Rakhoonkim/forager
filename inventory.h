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

	tagInven _inven[INVENX * INVENY];		         // �κ��丮�� �ִ� ���� �� 

	tagButton _useButton;  // ����ư
	tagButton _disButton;  // ������ ��ư

	float _invenStartX;
	int _invenSize;			// �κ������� ���� ���� ũ��(���簢��)
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

	void addInven(const char* imageName,int frameX, int frameY,int stemina,int heart,bool use);		// �κ��丮 �߰� 
	void removeInven(const char* imageName, int count);
	void InvenPointer();												// ���콺 ������ 

	void invenMove();
	void invenSetting();
	void invenClick();
	void invenItemCountRecder(HDC hdc);
	int  invenNumber();							// �κ��丮�� ���� ��ȯ �� 
	map<const char*, tagInven> getInven() { return _mInven; }

	//recipes ������ 
	bool foranceRecipes(FURNACERECIPE recipe, int count);
	bool forgeRecipes(FORGERECIPE recipe, int count);
	bool sewingRecipes(SEWINGRECIPE recipe, int count);

};

