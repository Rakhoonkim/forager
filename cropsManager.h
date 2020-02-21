#pragma once
#include "gameNode.h"
#include "crops.h"
#include "alphaEffect.h"
// 상속받은 클래스 

class player;
class cropsManager:public gameNode
{
private:
	vector<crops*>			 _vCrops;
	vector<crops*>::iterator _viCrops;

	alphaEffect* _effect;
	player* _player;
public:
	cropsManager();
	~cropsManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();
	
	//맞을때
	void imageIsHit();

	void createImageCrops(OBJECT object,int idx,int idy);
	void createFrameCrops(OBJECT object,int idx, int idy);
	void createimageFrameCrops(OBJECT object, int idx, int idy);
	void craateTreeCrops(TREE tree, int idx, int idy);
	
	vector<crops*>				getVCrops()	 { return _vCrops; }
	vector<crops*>::iterator	getViCrops() { return _viCrops; }

	void removeCrops(int arrNum) { _vCrops.erase(_vCrops.begin() + arrNum);}
	void removeCrops();

	void setPlayer(player* player) { _player = player; }
};

