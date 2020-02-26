#pragma once
#include "singletonBase.h"

class objectManager;

class mapManager : public singletonBase<mapManager>
{

private:
	tagTile _tiles[TILEX * TILEY];

	objectManager* _objectManager;

	//��ü �� Ÿ�� 
	vector<tagTile*>			_vTiles;
	vector<tagTile*>::iterator _viTiles;

	tagPlayer* _player;		// �÷��̾��� �ּҰ��� ��� 

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

	int getMapCount() { return _MapCount; } // ��ü ���� � ���� �ִ��� Ȯ���ϱ� ���� 

	void setPlayerAddress(tagPlayer* player);
	void setEnemyAddress(tagObject* enemy, int idx, int idy);			// ���� �� �浹�� ���� ���� 

	void setPlayerTileColision(int idx, int idy);

	void ObejectRender();

	void setLandTile(int x,int y); // ���� ���̰� �ϱ� ���� �Լ�
	void setRemoveObject(int idx, int idy);

	vector<tagTile*> getVTiles()			{ return _vTiles; }
	vector<tagTile*>::iterator getViTiles() { return _viTiles; }
	
	tagTile* getTiles(int idx, int idy) { return &_tiles[idy * TILEX + idx]; }

	//�ǹ� ������ ���� �����ϱ� ���� ��
	bool getBuildTiles(int idx, int idy);	// 4ĭ �ǹ� 
	void setBuildTiles(int idx, int idy);
	bool getBuildTilesFarming(int idx, int idy);  // 1ĭ �ǹ� 
	void setBuildTilesFarming(int idx, int idy);

	void setRemoveWater(int idx,int idy);
	
	POINT randomObjectTile();

	void removeTiles();
};

