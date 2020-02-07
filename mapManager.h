#pragma once
#include "singletonBase.h"
class mapManager : public singletonBase<mapManager>
{

private:
	tagTile _tiles[TILEX * TILEY];

	//전체 맵 타일 
	vector<tagTile*>			_vTiles;
	vector<tagTile*>::iterator _viTiles;

	//오브젝트 타일 ?    //오브젝트를 가져오기 
	vector<tagTile*>			_vObjectTiles;
	vector<tagTile*>::iterator _viObjectTiles;

	tagPlayer* _player;		// 플레이어의 주소값을 담는 
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

