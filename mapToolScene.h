#pragma once
#include "gameNode.h"

#define SAVESLOT 4
#define MAXSTYLE 6

class mapToolScene : public gameNode
{
	tagTile					     	_tiles[TILEX * TILEY];			//(45 X 36) Ÿ��
	
	tagPalette				 _terrainPalette[PALETTEX * PALETTEY];	//(7 X 7)	����
	tagPalette					_landPalette[PALETTEX * PALETTEY];	//(7 X 7)	��
	tagPalette		_landObjectPalette[LANDOBJECTX * LANDOBJECTY];	//(5 X 5)   �� ���� ������Ʈ
	tagPalette					_objectPalette[OBJECTX * OBJECTY];	//(7 X 4)   �Ĺ� ������Ʈ
	tagPalette				  _treePalette[TREETILEX * TREETILEY];	//(7 X 2)   ���� 
	tagPalette						_characterPalette[CHARACTERX];  //6         �÷��̾� �� ����
	tagPalette			_templeObjectPalette[PALETTEX * PALETTEY];	//(7 X 7)   ���� ������Ʈ

	tagButton	  _mapButton[9];	// MINIMAP 
	int			 _mapButtonSize;    // MAP��ư ������

	tagButton  _miniMap[TILEX * TILEY];		// (45 X 36) MINIMAP
	int				 _miniMapSizeWidth;		// ���� 
	float			_miniMapSizeHeight;		// ����


	tagButton	   _saveSlot[SAVESLOT];		// SAVE SLOT
	const char*				 _saveName;		// �������� ���� �̸� 
	int				_saveSlotDirection;		// �������� 
	int					_saveSlotWidth;		// ���� 
	int				   _saveSlotHeight;		// ���� 

	tagButton	_style[MAXSTYLE];	// 6  ��Ÿ�Ϲ�ư	
	tagButton			_type[7];   // 7  Ÿ�Թ�ư
	tagButton		 _saveButton;	//	  SAVE��ư
	tagButton		 _loadButton;	//	  LOAD��ư
	tagButton		 _exitButton;	//	  �������ư

	tagPalette		_currentTile;	// ���� ������ Ÿ��

public:
	mapToolScene();
	~mapToolScene();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void save();				//���̺�
	void load();				//�ε�
	void saveLoadClick();		//���̺�ε峪���� ��ư Ŭ��

	void MapToolImage();		// �����̹���
	void MapToolSetup();		// �����ʱ�ȭ

	void MapToolCollision();	// �����浹		 : ������ ��
	void MapToolUpdate();		// ����������Ʈ   : �����ϰ� ����  
	void MapToolEraser();		// ��������

	void MapToolRender();		// ��������

	//Ÿ�� �Ӽ��� ��ȯ�� �ִ� �Լ�
	TERRAIN			MapToolTerrainSelect(int frameX, int frameY);
	LAND			MapToolLandSelect(int frameX, int frameY);
	LANDOBJECT	    MapToolLandObjectSelect(int frameX, int frameY);
	OBJECT			MapToolObjectSelect(int frameX, int frameY);
	TREE			MapToolTreeSelect(int frameX, int frameY);
	CHARACTER		MapToolCharacterSelect(int frameX, int frameY);
	TEMPLEOBJECT	MapToolTempleObjectSelect(int frameX, int frameY);
};
