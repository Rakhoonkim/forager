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
	void LandObjectRender();
	void ObejectRender();

	void setPlayerAddress(tagPlayer* player);
	void setPlayerTileColision(int idx, int idy);

	void setLandTile(int x,int y); // 땅을 보이게 하기 위한 함수

	vector<tagTile*> getVTiles()			{ return _vTiles; }
	vector<tagTile*>::iterator getViTiles() { return _viTiles; }
	
	tagTile* getTiles(int idx, int idy) { return &_tiles[idy * TILEX + idx]; }

	//건물 지을때 땅에 지정하기 위한 값
	bool getBuildTiles(int idx, int idy);	// 4칸 건물 
	void setBuildTiles(int idx, int idy);
	bool getBuildTilesFarming(int idx, int idy);  // 1칸 건물 
	void setBuildTilesFarming(int idx, int idy);

	void setRemoveWater(int idx,int idy);
	
	POINT randomObjectTile();
};

