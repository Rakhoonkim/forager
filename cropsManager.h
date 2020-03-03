#pragma once
#include "gameNode.h"
#include "crops.h"
#include "alphaEffect.h"

class player;

class cropsManager:public gameNode
{
private:
	vector<crops*>			 _vCrops;
	vector<crops*>::iterator _viCrops;

	player* _player;
	alphaEffect* _effect;

	//랜덤 출현하기 위한 시간 값
	float _cropsTimer;
	float _cropsTimer2;
	float _rockTimer;
	float _treeTimer;
	int _maxCrops;
public:
	cropsManager();
	~cropsManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();
	
	//농작물 생성 함수
	void createImageCrops(OBJECT object,int idx,int idy);
	void createFrameCrops(OBJECT object,int idx, int idy);
	void createimageFrameCrops(OBJECT object, int idx, int idy);
	void craateTreeCrops(TREE tree, int idx, int idy);
	
	void CropsMakeUpdate();   // 작물을 만드는 

	vector<crops*>				getVCrops()	 { return _vCrops; }
	vector<crops*>::iterator	getViCrops() { return _viCrops; }

	void removeCrops(int arrNum) { _vCrops.erase(_vCrops.begin() + arrNum);}
	void removeCrops();

	void setPlayer(player* player) { _player = player; }
};

