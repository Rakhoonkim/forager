#pragma once
#include "itemState.h"

class item 
{
private:
	tagItem			  _item;  //ITEM 구조체

	itemState*	 _itemState;  //ITEM 상태
	itemDrop*	  _itemDrop;  //DROP 아이템 떨어질 때
	itemGain*	  _itemGain;  //GAIN 아이템 얻을 때
public:
	item();
	~item();

	HRESULT init(const char* imageName, float x, float y);
	void release();
	void update();
	void render();
	//타입 정의
	void setObject(OBJECT object)	{ _item.object = object; }
	void setTree(TREE tree)			{ _item.tree = tree; }

	void setGain(float x, float y);				 //플레이어 위치로 이동시키기
	void setIvenFrame(int x,int y);				 //인벤 프레임 
	void setSteminaHeart(int stemina, int heart) { _item.stemina = stemina; _item.heart = heart; }  // 체력 생명력
	void setGain()								 { _item.isClick = true; }		
	void setItemUse()							 { _item.isUse = true; }
	
	itemState* getItemState()					 { return _itemState; }
	itemGain* getItemGain()						 { return _itemGain;}
	tagItem* getItem()							 { return &_item; }
};

