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
	void LandObjectRender();
	void ObejectRender();

	void setPlayerAddress(tagPlayer* player);
	void setPlayerTileColision(int idx, int idy);

	void setLandTile(int x,int y); // ���� ���̰� �ϱ� ���� �Լ�

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
};

