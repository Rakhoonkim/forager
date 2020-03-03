#pragma once
#include "singletonBase.h"

class objectManager;

class mapManager : public singletonBase<mapManager>
{

private:
	tagTile		  _tiles[TILEX * TILEY];  //타일 정보

	//전체 맵 타일 
	vector<tagTile*>			_vTiles;
	vector<tagTile*>::iterator _viTiles;

	objectManager*		 _objectManager;  // OBJECT MANAGER
	tagPlayer*					_player;  // PLAYER 

	vector<POINT>				  _vBuyLand;  // 구매한 토지

	int _MapCount;
public:
	mapManager();
	~mapManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void stageRender();		// 스테이지 렌더
	void bossRender();		// 보스렌더 

	void MapImage();		// 이미지 셋팅
	void MapLoad(const char* fileName);
	void BossMapLoad(const char* fileName);
	void playerXYrender();	// 플레이어 xy를 기준으로 출력 

	void setObjectManager(objectManager* objectManager) { _objectManager = objectManager; }
	
	//백터일 때 사용
	void TerrainRender();
	void LandRender();
	void LandObjectRender();

	int getMapCount()					{ return _MapCount; } // 전체 맵을 몇개 갖고 있는지 확인하기 위한 

	void setPlayerAddress(tagPlayer* player);
	void setEnemyAddress(tagObject* enemy, int idx, int idy);			// 몬스터 섬 충돌을 막기 위한 
	
	void setPlayerStageTileColision(int idx, int idy);
	bool setBulletBossTileCollision(int idx, int idy);
	void ObejectRender();

	void setLandTile(int x,int y); // 땅을 보이게 하기 위한 함수
	void setRemoveObject(int idx, int idy);

	vector<tagTile*> getVTiles()			{ return _vTiles; }
	vector<tagTile*>::iterator getViTiles() { return _viTiles; }
	tagTile* getTiles(int idx, int idy)	    { return &_tiles[idy * TILEX + idx]; }
	
	//건물 지을때 땅에 지정하기 위한 값
	bool getBuildTiles(int idx, int idy);	// 4칸 건물 
	void setBuildTiles(int idx, int idy);
	bool getBuildTilesFarming(int idx, int idy);  // 1칸 건물 
	void setBuildTilesFarming(int idx, int idy);

	void setRemoveWater(int idx,int idy);		//충돌 타일 지우기
	
	POINT randomObjectTile();

	void removeTiles();
	void addBuyLand(int x,int y) { _vBuyLand.push_back(PointMake(x,y)); }
	void setBuyLand();
};

