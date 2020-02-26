#pragma once
#include "singletonBase.h"

class objectManager;

class mapManager : public singletonBase<mapManager>
{

private:
	tagTile _tiles[TILEX * TILEY];

	objectManager* _objectManager;

	//전체 맵 타일 
	vector<tagTile*>			_vTiles;
	vector<tagTile*>::iterator _viTiles;

	tagPlayer* _player;		// 플레이어의 주소값을 담는 

	int _MapCount;
public:
	mapManager();
	~mapManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void playerXYrender();

	void MapImage();
	void MapLoad(const char* fileName);

	void setObjectManager(objectManager* objectManager) { _objectManager = objectManager; }

	void TerrainRender();
	void LandRender();
	void LandObjectRender();

	int getMapCount() { return _MapCount; } // 전체 맵을 몇개 갖고 있는지 확인하기 위한 

	void setPlayerAddress(tagPlayer* player);
	void setEnemyAddress(tagObject* enemy, int idx, int idy);			// 몬스터 섬 충돌을 막기 위한 

	void setPlayerTileColision(int idx, int idy);

	void ObejectRender();

	void setLandTile(int x,int y); // 땅을 보이게 하기 위한 함수
	void setRemoveObject(int idx, int idy);

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

	void removeTiles();
};

