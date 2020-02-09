#pragma once
#include "gameNode.h"
#include "crops.h"
// ��ӹ��� Ŭ���� 
//
//

class cropsManager:public gameNode
{
private:
	vector<crops*>			 _vCrops;
	vector<crops*>::iterator _viCrops;


	crops* _crops;			// �������� 

public:
	cropsManager();
	~cropsManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();
	void createImageCrops(OBJECT object,int idx,int idy);
	void createFrameCrops(OBJECT object,int idx, int idy);

	vector<crops*>				getVCrops()	 { return _vCrops; }
	vector<crops*>::iterator	getViCrops() { return _viCrops; }

	void removeCrops(int arrNum) { _vCrops.erase(_vCrops.begin() + arrNum);}
	void removeCrops();
};

