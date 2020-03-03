#pragma once
#include "itemState.h"

class item 
{
private:
	tagItem			  _item;  //ITEM ����ü

	itemState*	 _itemState;  //ITEM ����
	itemDrop*	  _itemDrop;  //DROP ������ ������ ��
	itemGain*	  _itemGain;  //GAIN ������ ���� ��
public:
	item();
	~item();

	HRESULT init(const char* imageName, float x, float y);
	void release();
	void update();
	void render();
	//Ÿ�� ����
	void setObject(OBJECT object)	{ _item.object = object; }
	void setTree(TREE tree)			{ _item.tree = tree; }

	void setGain(float x, float y);				 //�÷��̾� ��ġ�� �̵���Ű��
	void setIvenFrame(int x,int y);				 //�κ� ������ 
	void setSteminaHeart(int stemina, int heart) { _item.stemina = stemina; _item.heart = heart; }  // ü�� �����
	void setGain()								 { _item.isClick = true; }		
	void setItemUse()							 { _item.isUse = true; }
	
	itemState* getItemState()					 { return _itemState; }
	itemGain* getItemGain()						 { return _itemGain;}
	tagItem* getItem()							 { return &_item; }
};

