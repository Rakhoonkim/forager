#include "stdafx.h"
#include "mapToolScene.h"

mapToolScene::mapToolScene()
{
}

mapToolScene::~mapToolScene()
{
}

HRESULT mapToolScene::init()
{
	MapToolImage();
	MapToolSetup();
	return S_OK;
}

void mapToolScene::release()
{
}

void mapToolScene::update()
{
	//cout << "x:" << _ptMouse.x << "y:" << _ptMouse.y << endl;

	MapToolCollision();		// Ŭ�� 

}

void mapToolScene::render()
{
	MapToolRender();
}

void mapToolScene::MapToolImage()
{
	//�ܵ�
	IMAGEMANAGER->addFrameImage("grassTile", "./image/mapTool/grassTile.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grassTileLand", "./image/mapTool/grassTileLand.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grassTileObject", "./image/mapTool/grassTileObject.bmp", 300, 300, 5, 5, true, RGB(255, 0, 255));
	//�ܵ� �ȷ�Ʈ
	IMAGEMANAGER->addFrameImage("grassTilePalette", "./image/mapTool/grassTilePalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grassTileLandPalette", "./image/mapTool/grassTileLandPalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grassTileObjectPalette", "./image/mapTool/grassTileObjectPalette.bmp", 200, 200, 5, 5, true, RGB(255, 0, 255));
	//Button 
	IMAGEMANAGER->addImage("redButton", "./image/mapTool/redButton.bmp", 45, 45, true, RGB(255, 0, 255));
}

void mapToolScene::MapToolSetup()
{
	// ���� ���� 
	_currentTile.type = TYPE::NONE;
	_currentTile.frameX = 0;
	_currentTile.frameY = 0;
	// ���� ����
	_mapButtonSize = 45;		// �� ��ư 

	_miniMapSizeWidth = 3;		// MINIMAP ���� 
	_miniMapSizeHeight = 3.75;	// MINIMAP ���� 

	_saveSlotSizeWidth = 280;	// SAVE ���� 
	_saveSlotSizeHeight = 30;	// SAVE ���� 

	// ���� �׷����� Ÿ�� 
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc, j * TILESIZE, i * TILESIZE,
				j * TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
			_tiles[i * TILEX + j].type = TYPE::NONE;
			_tiles[i * TILEX + j].terrain = TERRAIN::NONE;
			_tiles[i * TILEX + j].object = OBJECT::NONE;
			_tiles[i * TILEX + j].character = CHARACTER::NONE;
			_tiles[i * TILEX + j].terrainFrameX = 0;
			_tiles[i * TILEX + j].terrainFrameY = 0;
			_tiles[i * TILEX + j].objectFrameX = 0;
			_tiles[i * TILEX + j].objectFrameY = 0;
			_tiles[i * TILEX + j].characterFrameX = 0;
			_tiles[i * TILEX + j].characterFrameY = 0;
		}
	}

	// ������ �׸����� Ÿ�� 
	// ����, �� �ʱ�ȭ 
	for (int i = 0; i < PALETTEY; i++)
	{
		for (int j = 0;j < PALETTEX; j++)
		{
			SetRect(&_terrainPalette[i * PALETTEY + j].rc, WINSIZEX - IMAGEMANAGER->findImage("grassTilePalette")->getWidth() + (j * PALETTESIZE),
				i * PALETTESIZE, WINSIZEX - IMAGEMANAGER->findImage("grassTilePalette")->getWidth() + j * PALETTESIZE + PALETTESIZE, i * PALETTESIZE + PALETTESIZE);
			_landPalette[i * PALETTEY + j].rc = _terrainPalette[i * PALETTEY + j].rc;
			_terrainPalette[i * PALETTEY + j].frameX = _landPalette[i * PALETTEY + j].frameX = j;
			_terrainPalette[i * PALETTEY + j].frameY = _landPalette[i * PALETTEY + j].frameY = i;
		}
	}
	//������Ʈ
	for (int i = 0; i < OBJECTY; i++)
	{
		for (int j = 0;j < OBJECTX; j++)
		{
			SetRect(&_objectPalette[i * OBJECTY + j].rc, WINSIZEX - IMAGEMANAGER->findImage("grassTileObjectPalette")->getWidth() + (j * PALETTESIZE),
				i * PALETTESIZE, WINSIZEX - IMAGEMANAGER->findImage("grassTileObjectPalette")->getWidth() + j * PALETTESIZE + PALETTESIZE, i * PALETTESIZE + PALETTESIZE);
			_objectPalette[i * OBJECTY + j].frameX = j;
			_objectPalette[i * OBJECTY + j].frameY = i;
		}
	}
	// �׸� TYPE
	for (int i = 0;i < 7;i++)
	{
		SetRect(&_type[i].rc, 920 + i * 40, 300, 920 + i * 40 + 40, 340);

	}

	// ��ġ�� ��Ÿ���� ��ư 
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SetRect(&_mapButton[i * 3 + j].rc, 920 + j * _mapButtonSize, 360 + i * _mapButtonSize, 920 + j * _mapButtonSize + _mapButtonSize, 360 + i * _mapButtonSize + _mapButtonSize);
			_mapButton[i * 3 + j].isClick = false;
		}
	}

	// MINIMAP
	for (int i = 0; i < TILEY * 3; i++)
	{
		for (int j = 0; j < TILEX * 3; j++)
		{
			SetRect(&_miniMap[i * (TILEX * 3) + j].rc, WINSIZEX - 140 + j * _miniMapSizeWidth, 360 + (i * _miniMapSizeHeight), WINSIZEX - 140 + (j * _miniMapSizeWidth) + _miniMapSizeWidth, 360 + (i * _miniMapSizeHeight) + _miniMapSizeHeight);
		}
	}

	// SAVESLOT
	for (int i = 0; i < 5; i++)
	{
		SetRect(&_saveSlot[i].rc, 920, WINSIZEY - 210 + i * _saveSlotSizeHeight, 920 + _saveSlotSizeWidth, WINSIZEY - 210 + i * _saveSlotSizeHeight + _saveSlotSizeHeight);
	}

	SetRect(&_saveButton.rc, 920, 670, 1020, 710);
	SetRect(&_loadButton.rc, 1020, 670, 1120, 710);
	SetRect(&_exitButton.rc, 1130, 670, 1190, 710);

}

void mapToolScene::MapToolCollision()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//�̴ϸ� ���� 
		for (int i = 0;i < 9;i++)
		{
			if (PtInRect(&_mapButton[i].rc, _ptMouse))
			{
				for (int i = 0;i < 9;i++)
				{
					_mapButton[i].isClick = false;
				}

				if (!_mapButton[i].isClick)
				{
					_mapButton[i].isClick = true;
				}
				else _mapButton[i].isClick = false;
			}
		}


		//TYPE ����
		for (int i = 0; i < 7; i++)
		{
			if (PtInRect(&_type[i].rc, _ptMouse))
			{
				switch (i)
				{
				case 0:
					_currentTile.type = TYPE::TERRAIN;
					break;
				case 1:
					_currentTile.type = TYPE::LAND;
					break;
				case 2:
					_currentTile.type = TYPE::OBJECT;
					break;
				case 3:

					break;
				case 4:

					break;
				case 5:

					break;
				case 6:

					break;
				default:
					break;
				}
			}
		}

		MapToolUpdate();
	}
}

void mapToolScene::MapToolUpdate()
{
	//������ Ŭ���� �� 
	if (_currentTile.type == TYPE::TERRAIN || _currentTile.type == TYPE::LAND)
	{
		for (int i = 0; i < PALETTEY; ++i)
		{
			for (int j = 0;j < PALETTEX; ++j)
			{
				if (PtInRect(&_terrainPalette[i * PALETTEY + j].rc, _ptMouse))
				{
					_currentTile.frameX = j;
					_currentTile.frameY = i;
					break;
				}
			}
		}
	}
	else if (_currentTile.type == TYPE::OBJECT)
	{
		for (int i = 0; i < OBJECTY; ++i)
		{
			for (int j = 0;j < OBJECTX; ++j)
			{
				if (PtInRect(&_objectPalette[i * OBJECTY + j].rc, _ptMouse))
				{
					_currentTile.frameX = j;
					_currentTile.frameY = i;
					break;
				}
			}
		}
	}

	cout << "X :" << _currentTile.frameX << "Y : " << _currentTile.frameY << endl;

	//���� Ŭ���� �� 
	for (int i = 0;i < TILEY;i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (PtInRect(&_tiles[i * TILEY + j].rc, _ptMouse))
			{
				if (_currentTile.type == TYPE::TERRAIN)
				{
					_tiles[i * TILEY + j].type = TYPE::TERRAIN;
					_tiles[i * TILEY + j].terrain = TERRAIN::GRASS;
					_tiles[i * TILEY + j].terrainFrameX = _currentTile.frameX;
					_tiles[i * TILEY + j].terrainFrameY = _currentTile.frameY;
					_tiles[i * TILEY + j].terrain = MapToolTerrainSelect(_tiles[i * TILEY + j].terrainFrameX, _tiles[i * TILEY + j].terrainFrameY);
					break;
				}
				else if (_currentTile.type == TYPE::LAND)
				{
					_tiles[i * TILEY + j].type = TYPE::LAND;
					_tiles[i * TILEY + j].land = LAND::GRASS;
					_tiles[i * TILEY + j].landFrameX = _currentTile.frameX;
					_tiles[i * TILEY + j].landFrameY = _currentTile.frameY;
					_tiles[i * TILEY + j].land = MapToolLandSelect(_tiles[i * TILEY + j].landFrameX, _tiles[i * TILEY + j].landFrameY);
					break;
				}
				else if (_currentTile.type == TYPE::OBJECT)
				{
					_tiles[i * TILEY + j].type = TYPE::OBJECT;
					_tiles[i * TILEY + j].object = OBJECT::GRASS;
					_tiles[i * TILEY + j].objectFrameX = _currentTile.frameX;
					_tiles[i * TILEY + j].objectFrameY = _currentTile.frameY;
					_tiles[i * TILEY + j].object = MapToolObjectSelect(_tiles[i * TILEY + j].objectFrameX, _tiles[i * TILEY + j].objectFrameY);
					break;
				}

			}
		}
	}
}

void mapToolScene::MapToolRender()
{
	//TERRAIN������ 
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//Rectangle(getMemDC(), _tiles[i].rc);
		if (_tiles[i].terrain == TERRAIN::NONE) continue;
		IMAGEMANAGER->findImage("grassTile")->frameRender(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}
	//LAND������ 
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//Rectangle(getMemDC(), _tiles[i].rc);
		if (_tiles[i].land == LAND::NONE) continue;
		IMAGEMANAGER->findImage("grassTileLand")->frameRender(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landFrameX, _tiles[i].landFrameY);
	}
	//OBJECT������
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//Rectangle(getMemDC(), _tiles[i].rc);
		if (_tiles[i].object == OBJECT::NONE) continue;
		IMAGEMANAGER->findImage("grassTileObject")->frameRender(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objectFrameX, _tiles[i].objectFrameY);
	}




	//�ȷ�Ʈ Ÿ�� 
	for (int i = 0;i < PALETTEX * PALETTEY; i++)
	{
		Rectangle(getMemDC(), _terrainPalette[i].rc);
	}

	// TYPE
	for (int i = 0;i < 7;i++)
	{
		Rectangle(getMemDC(), _type[i].rc);
	}

	char str[128];
	sprintf_s(str, "Ŭ��");
	SetTextColor(getMemDC(), RGB(255, 0, 0));
	// ��ġ Ÿ�� 
	for (int i = 0; i < 9; ++i)
	{
		Rectangle(getMemDC(), _mapButton[i].rc);

		if (_mapButton[i].isClick)
		{
			TextOut(getMemDC(), _mapButton[i].rc.left, _mapButton[i].rc.top, str, strlen(str));
		}
	}

	// �̴ϸ� 
	for (int i = 0;i < TILEX * TILEY * 9; i++)
	{

		Rectangle(getMemDC(), _miniMap[i].rc);
	}

	// ���̺� ���� 
	for (int i = 0;i < 5; i++)
	{
		Rectangle(getMemDC(), _saveSlot[i].rc);
	}

	Rectangle(getMemDC(), _saveButton.rc);
	Rectangle(getMemDC(), _loadButton.rc);
	Rectangle(getMemDC(), _exitButton.rc);



	// ������ 
	if (_currentTile.type == TYPE::TERRAIN)
	{
		for (int i = 0;i < PALETTEX * PALETTEY; i++)
		{
			IMAGEMANAGER->findImage("grassTilePalette")->frameRender(getMemDC(), _terrainPalette[i].rc.left, _terrainPalette[i].rc.top, _terrainPalette[i].frameX, _terrainPalette[i].frameY);
		}
	}
	else if (_currentTile.type == TYPE::LAND)
	{
		for (int i = 0;i < PALETTEX * PALETTEY; i++)
		{
			IMAGEMANAGER->findImage("grassTileLandPalette")->frameRender(getMemDC(), _landPalette[i].rc.left, _landPalette[i].rc.top, _landPalette[i].frameX, _landPalette[i].frameY);
		}
	}
	else if (_currentTile.type == TYPE::OBJECT)
	{
		for (int i = 0;i < OBJECTX * OBJECTY; i++)
		{
			IMAGEMANAGER->findImage("grassTileObjectPalette")->frameRender(getMemDC(), _objectPalette[i].rc.left, _objectPalette[i].rc.top, _objectPalette[i].frameX, _objectPalette[i].frameY);
		}
	}
	else if (_currentTile.type == TYPE::CHARACTER)
	{
		for (int i = 0;i < 25; i++)
		{
			//IMAGEMANAGER->findImage("grassTileCharacterPalette")->frameRender(getMemDC(), _terrainPalette[i].rc.left, _terrainPalette[i].rc.top, _terrainPalette[i].frameX, _terrainPalette[i].frameY);
		}

	}

}

void mapToolScene::MapPalette()
{
}

TERRAIN mapToolScene::MapToolTerrainSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return TERRAIN::NONE;
	if (frameX == 6 && frameY == 6) return TERRAIN::NONE;

	return TERRAIN::GRASS;
}

LAND mapToolScene::MapToolLandSelect(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 0 || frameX == 3 && frameY == 0 || frameX == 4 && frameY == 0
		|| frameX == 0 && frameY == 1 || frameX == 1 && frameY == 1 || frameX == 4 && frameY == 1
		|| frameX == 1 && frameY == 2) return LAND::GRASS;
	if (frameX == 4 && frameY == 3 || frameX == 5 && frameY == 3 || frameX == 6 && frameY == 3) return LAND::GRASS;
	if (frameX == 2 && frameY == 6 || frameX == 4 && frameY == 6 || frameX == 5 && frameY == 6) return LAND::GRASS;

	return LAND::NONE;
}

OBJECT mapToolScene::MapToolObjectSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return OBJECT::NONE;
	for (int i = 1;i < 5; i++)	// 1,2,3,4
	{
		if (frameX == i && frameY == 4) return OBJECT::NONE;
	}

	return OBJECT::GRASS;
}

CHARACTER mapToolScene::MapToolCharacterSelect(int frameX, int frameY)
{

	return CHARACTER::NONE;
}
