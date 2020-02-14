#pragma once
#include "gameNode.h"

class mapToolScene : public gameNode
{
	tagTile			   _tiles[TILEX * TILEY];			// �׷����� Ÿ�� 
	
	tagPalette _terrainPalette[PALETTEX * PALETTEY];			// ���� Ÿ��  7 X 7
	tagPalette _landPalette[PALETTEX * PALETTEY];				// �� Ÿ��  7 X 7
	tagPalette _landObjectPalette[LANDOBJECTX * LANDOBJECTY];	// Ÿ�� ������Ʈ 5 X 5
	tagPalette _objectPalette[OBJECTX * OBJECTY];				// ������Ʈ Ÿ��
	tagPalette _treePalette[TREETILEX * TREETILEY];				// ���� Ÿ��


	//��ư RECT
	//X�� 920 ��������
	tagButton _mapButton[9];	//MAP ��ġ 
	int _mapButtonSize;

	tagButton _miniMap[TILEX * TILEY * 9];  // MINIMAP
	int		 _miniMapSizeWidth;			    // ���� 
	float	_miniMapSizeHeight;				// ����

	tagButton	   _saveSlot[5];			// SLOT
	const char* _saveName;

	int		 _saveSlotSizeWidth;			// ���� 
	int		_saveSlotSizeHeight;			// ���� 

	tagButton _style[3];	// 0,1,2	
	tagButton _type[7];     // 0,1,2,3,4
	tagButton _saveButton;	// SAVE 
	tagButton _loadButton;	// LOAD  
	tagButton _exitButton;	// ������ 

	tagPalette _currentTile;	// ���� Ÿ��

public:
	mapToolScene();
	~mapToolScene();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void save();
	void load();
	void SaveAndLoad();

	void MapToolImage();		// �����̹���
	void MapToolSetup();		// �����ʱ�ȭ

	void MapToolCollision();	// �����浹		 : ������ ��
	void MapToolUpdate();		// ����������Ʈ   : �����ϰ� ����  
	void MapToolEraser();		// ���� ����

	void MapToolRender();		// ��������

	//Ÿ�� �Ӽ� 
	TERRAIN MapToolTerrainSelect(int frameX, int frameY);
	LAND MapToolLandSelect(int frameX, int frameY);
	LANDOBJECT MapToolLandObjectSelect(int frameX, int frameY);
	OBJECT MapToolObjectSelect(int frameX, int frameY);
	TREE MapToolTreeSelect(int frameX, int frameY);
	//����
	CHARACTER MapToolCharacterSelect(int frameX, int frameY);
};
