#pragma once
#include "singletonBase.h"
class mapManager : public singletonBase<mapManager>
{

private:
	tagTile _tiles[TILEX * TILEY];

	//��ü �� Ÿ�� 
	vector<tagTile*>			_vTiles;
	vector<tagTile*>::iterator _viTiles;

	//������Ʈ Ÿ�� ?    //������Ʈ�� �������� 
	vector<tagTile*>			_vObjectTiles;
	vector<tagTile*>::iterator _viObjectTiles;

	tagPlayer* _player;		// �÷��̾��� �ּҰ��� ��� 
public:
	mapManager();
	~mapManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void MapImage();
	void MapLoad(const char* fileName);

	void TerrainRender();
	void LandRender();
	void LadnObjectRender();
	void ObejectRender();


	void setPlayerAddress();
	
};

