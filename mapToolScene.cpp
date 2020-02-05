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

	MapToolCollision();		// 클릭 
	MapToolEraser();
}

void mapToolScene::render()
{
	
	MapToolRender();
}

void mapToolScene::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("Loby_SaveFile.map", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void mapToolScene::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("Loby_SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//맵을 불로온 직후 타일의 속성을 매겨준다
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

void mapToolScene::SaveAndLoad()
{
	if (_saveButton.isClick)
	{
		this->save();
		_saveButton.isClick = false;
	}
	if (_loadButton.isClick)
	{
		this->load();
		_loadButton.isClick = false;
	}
}

void mapToolScene::MapToolImage()
{
	//TILE STYLE
	IMAGEMANAGER->addFrameImage("grassTileLand", "./image/mapTool/grassTileLand.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("grassTile", "./image/mapTool/grassTile.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grassTileObject", "./image/mapTool/grassTileObject.bmp", 300, 300, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("desertTile", "./image/mapTool/desertTile.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("desertTileObject", "./image/mapTool/desertTileObject.bmp", 300, 300, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("snowTile", "./image/mapTool/snowTile.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("snowTileObject", "./image/mapTool/snowTileObject.bmp", 300, 300, 5, 5, true, RGB(255, 0, 255));

	//PALETTE
	IMAGEMANAGER->addFrameImage("grassTileLandPalette", "./image/mapTool/grassTileLandPalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grassTilePalette", "./image/mapTool/grassTilePalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grassTileObjectPalette", "./image/mapTool/grassTileObjectPalette.bmp", 200, 200, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("desertTilePalette", "./image/mapTool/desertTilePalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("desertTileObjectPalette", "./image/mapTool/desertTileObjectPalette.bmp", 200, 200, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("snowTilePalette", "./image/mapTool/snowTilePalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("snowTileObjectPalette", "./image/mapTool/snowTileObjectPalette.bmp", 200, 200, 5, 5, true, RGB(255, 0, 255));
	
	//오프젝트
	IMAGEMANAGER->addFrameImage("objectTile", "./image/mapTool/objectTile.bmp", 420, 180, 7, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("objectTilePalette", "./image/mapTool/objectTilePalette.bmp", 280, 120, 7, 3, true, RGB(255, 0, 255));
	//나무타일 
	IMAGEMANAGER->addFrameImage("treeTile", "./image/mapTool/treeTile.bmp", 420, 240, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("treeTilePalette", "./image/mapTool/treeTilePalette.bmp", 280, 160, 7, 2, true, RGB(255, 0, 255));



	//Button 
	IMAGEMANAGER->addImage("redButton", "./image/mapTool/redButton.bmp", 45, 45, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap", "./image/mapTool/minimap.bmp", 3, 3, false, RGB(255, 0, 255));
}

void mapToolScene::MapToolSetup()
{
	// 현재 셋팅 
	_currentTile.type = TYPE::NONE;
	_currentTile.terrain = TERRAIN::GRASS;
	_currentTile.frameX = 0;
	_currentTile.frameY = 0;
	// 변수 세팅
	_mapButtonSize = 45;		// 맵 버튼 

	_miniMapSizeWidth = 3;		// MINIMAP 가로 
	_miniMapSizeHeight = 3.75;	// MINIMAP 세로 

	_saveSlotSizeWidth = 280;	// SAVE 가로 
	_saveSlotSizeHeight = 30;	// SAVE 세로 

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■본 MAP ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc, j * TILESIZE, i * TILESIZE,
				j * TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
			_tiles[i * TILEX + j].type = TYPE::NONE;
			_tiles[i * TILEX + j].terrain = TERRAIN::NONE;
			_tiles[i * TILEX + j].land = LAND::NONE;
			_tiles[i * TILEX + j].landObject = LANDOBJECT::NONE;
			_tiles[i * TILEX + j].object = OBJECT::NONE;
			_tiles[i * TILEX + j].tree = TREE::NONE;
			_tiles[i * TILEX + j].character = CHARACTER::NONE;
			_tiles[i * TILEX + j].terrainFrameX = 0;
			_tiles[i * TILEX + j].terrainFrameY = 0;
			_tiles[i * TILEX + j].objectFrameX = 0;
			_tiles[i * TILEX + j].objectFrameY = 0;
			_tiles[i * TILEX + j].characterFrameX = 0;
			_tiles[i * TILEX + j].characterFrameY = 0;
			_tiles[i * TILEX + j].landObjectFrameX = 0;
			_tiles[i * TILEX + j].landObjectFrameY = 0;
			_tiles[i * TILEX + j].treeFrameX = 0;
			_tiles[i * TILEX + j].treeFrameY = 0;
			_tiles[i * TILEX + j].idx = j;
			_tiles[i * TILEX + j].idy = i;
			_tiles[i * TILEX + j].isClick = false;
		}
	}

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 땅 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < PALETTEY; i++)
	{
		for (int j = 0;j < PALETTEX; j++)
		{
			SetRect(&_terrainPalette[i * PALETTEX + j].rc, WINSIZEX - IMAGEMANAGER->findImage("grassTilePalette")->getWidth() + (j * PALETTESIZE),
				i * PALETTESIZE, WINSIZEX - IMAGEMANAGER->findImage("grassTilePalette")->getWidth() + j * PALETTESIZE + PALETTESIZE, i * PALETTESIZE + PALETTESIZE);
			_landPalette[i * PALETTEY + j].rc = _terrainPalette[i * PALETTEY + j].rc;
			_terrainPalette[i * PALETTEX + j].frameX = _landPalette[i * PALETTEX + j].frameX = j;
			_terrainPalette[i * PALETTEX + j].frameY = _landPalette[i * PALETTEX + j].frameY = i;
		}
	}

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 땅 데코레이션 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < LANDOBJECTY; i++)
	{
		for (int j = 0;j < LANDOBJECTX; j++)
		{
			SetRect(&_landObjectPalette[i * LANDOBJECTX + j].rc, WINSIZEX - IMAGEMANAGER->findImage("grassTileObjectPalette")->getWidth() + (j * PALETTESIZE),
				i * PALETTESIZE, WINSIZEX - IMAGEMANAGER->findImage("grassTileObjectPalette")->getWidth() + j * PALETTESIZE + PALETTESIZE, i * PALETTESIZE + PALETTESIZE);
			_landObjectPalette[i * LANDOBJECTX + j].frameX = j;
			_landObjectPalette[i * LANDOBJECTX + j].frameY = i;
		}
	}

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 오브  젝트  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0;i < OBJECTY; i++)
	{
		for (int j = 0;j < OBJECTX; j++)
		{
			SetRect(&_objectPalette[i * OBJECTX + j].rc, WINSIZEX - IMAGEMANAGER->findImage("objectTilePalette")->getWidth() + (j * PALETTESIZE),
				i * PALETTESIZE, WINSIZEX - IMAGEMANAGER->findImage("objectTilePalette")->getWidth() + j * PALETTESIZE + PALETTESIZE, i * PALETTESIZE + PALETTESIZE);
			_objectPalette[i * OBJECTX + j].frameX = j;
			_objectPalette[i * OBJECTX + j].frameY = i;
		}
	}


	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 나무  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 
	for (int i = 0;i < TREETILEY; i++)
	{
		for (int j = 0;j < TREETILEX; j++)
		{
			SetRect(&_treePalette[i * TREETILEX + j].rc, WINSIZEX - IMAGEMANAGER->findImage("treeTilePalette")->getWidth() + (j * PALETTESIZE),
				i * 120, WINSIZEX - IMAGEMANAGER->findImage("treeTilePalette")->getWidth() + j * PALETTESIZE + PALETTESIZE, i *120 + 120);
			_treePalette[i * TREETILEX + j].frameX = j;
			_treePalette[i * TREETILEX + j].frameY = i;
		}
	}
	//스타일 
	for (int i = 0; i < 3; ++i)
	{
		SetRect(&_style[i].rc, 920 + i * 95, 285, 920 + i * 95 + 90, 305);
		_style[i].isClick = false;
	}
	_style[0].isClick = true;

	// 그림 TYPE
	for (int i = 0;i < 7;i++)
	{
		SetRect(&_type[i].rc, 920 + i * 40, 310, 920 + i * 40 + 40, 350);
	}

	// 위치를 나타내는 버튼 
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SetRect(&_mapButton[i * 3 + j].rc, 920 + j * _mapButtonSize, 360 + i * _mapButtonSize, 920 + j * _mapButtonSize + _mapButtonSize, 360 + i * _mapButtonSize + _mapButtonSize);
			_mapButton[i * 3 + j].isClick = false;
		}
	}
	_mapButton[0].isClick = true;
	// MINIMAP
	for (int i = 0; i < TILEY ; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_miniMap[i * (TILEX ) + j].rc, WINSIZEX - 140 + j * _miniMapSizeWidth, 360 + (i * _miniMapSizeHeight), WINSIZEX - 140 + (j * _miniMapSizeWidth) + _miniMapSizeWidth, 360 + (i * _miniMapSizeHeight) + _miniMapSizeHeight);
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
	_saveButton.isClick = false;
	_loadButton.isClick = false;
	_exitButton.isClick = false;
}

void mapToolScene::MapToolCollision()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		//미니맵 정의 
		for (int i = 0;i < 3;i++)
		{
			for (int j = 0;j < 3;j++)
			{
				if (PtInRect(&_mapButton[i * 3 + j].rc, _ptMouse))
				{
					for (int i = 0;i < 9;i++)
					{
						_mapButton[i].isClick = false;
					}
					if (!_mapButton[i * 3 + j].isClick)
					{
						_mapButton[i * 3 + j].isClick = true;
					}
					else _mapButton[i * 3 + j].isClick = false;
					CAMERAMANAGER->setMapToolCameraXY(900 * j, 720 * i);
					break;
				}
			}
		}

		// 스타일 클릭 
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_style[i].rc, _ptMouse))
			{
				for (int i = 0;i < 3;i++)
				{
					_style[i].isClick = false;
				}
				_style[i].isClick = true;
				break;
			}
		}


		//TYPE 정의
		for (int i = 0; i < 7; i++)
		{
			if (PtInRect(&_type[i].rc, _ptMouse))
			{
				switch (i)
				{
				case 0:
					_currentTile.type = TYPE::TERRAIN;			// 지형	
					break;
				case 1:
					_currentTile.type = TYPE::LAND;				// 땅 
					break;		
				case 2:
					_currentTile.type = TYPE::LANDOBJECT;       // 땅 데코 
					break;
				case 3:
					_currentTile.type = TYPE::OBJECT;			// 
					break;
				case 4:
					_currentTile.type = TYPE::TREE;				// 나무 
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

		MapToolUpdate(); // 왼쪽을 눌렀을 때 
	}
}

void mapToolScene::MapToolUpdate()
{
	cout << "X :" << _currentTile.frameX << "Y : " << _currentTile.frameY << endl;
	//오른쪽 클릭할 때 
	if (_currentTile.type == TYPE::TERRAIN || _currentTile.type == TYPE::LAND)
	{
		for (int i = 0; i < PALETTEY; ++i)
		{
			for (int j = 0;j < PALETTEX; ++j)
			{
				if (PtInRect(&_terrainPalette[i * PALETTEX + j].rc, _ptMouse))
				{
					// 타일의 스타일 정의
					_currentTile.frameX = j;
					_currentTile.frameY = i;
					break;
				}
			}
		}
	}
	else if (_currentTile.type == TYPE::LANDOBJECT)
	{
		for (int i = 0; i < LANDOBJECTY; ++i)
		{
			for (int j = 0;j < LANDOBJECTX; ++j)
			{
				if (PtInRect(&_landObjectPalette[i * LANDOBJECTX + j].rc, _ptMouse))
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
		for (int i = 0; i < OBJECTY; i++)
		{
			for (int j = 0; j < OBJECTX; j++)
			{
				if (PtInRect(&_objectPalette[i * OBJECTX + j].rc, _ptMouse))
				{
					_currentTile.frameX = j;
					_currentTile.frameY = i;
					break;
				}
			}
		}
	}
	else if (_currentTile.type == TYPE::TREE)
	{
		for (int i = 0; i < TREETILEY; i++)
		{
			for (int j = 0; j < TREETILEX; j++)
			{
				if (PtInRect(&_treePalette[i * TREETILEX + j].rc, PointMake(CAMERAMANAGER->getMapToolCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getMapToolCamera().cameraY + _ptMouse.y)))
				{
					_currentTile.frameX = j;
					_currentTile.frameY = i;
					break;
				}
			}
		}
	}

	cout << "X :" << _currentTile.frameX << "Y : " << _currentTile.frameY << endl;
	
	//왼쪽 클릭할 때 
	for (int i = 0;i < TILEY;i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (PtInRect(&_tiles[i * TILEX + j].rc, PointMake(CAMERAMANAGER->getMapToolCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getMapToolCamera().cameraY + _ptMouse.y)))
			{
				if (_ptMouse.x >= 900) return;
				_tiles[i * TILEX + j].isClick = true;
				cout << "값" << _tiles[i * TILEX + j].isClick << endl;
				if (_currentTile.type == TYPE::TERRAIN)
				{
					_tiles[i * TILEX + j].type = TYPE::TERRAIN;
					_tiles[i * TILEX + j].terrainFrameX = _currentTile.frameX;
					_tiles[i * TILEX + j].terrainFrameY = _currentTile.frameY;
					_tiles[i * TILEX + j].terrain = MapToolTerrainSelect(_tiles[i * TILEX + j].terrainFrameX, _tiles[i * TILEX + j].terrainFrameY);
				}
				else if (_currentTile.type == TYPE::LAND)
				{
					_tiles[i * TILEX + j].type = TYPE::LAND;
					_tiles[i * TILEX + j].landFrameX = _currentTile.frameX;
					_tiles[i * TILEX + j].landFrameY = _currentTile.frameY;
					_tiles[i * TILEX + j].land = MapToolLandSelect(_tiles[i * TILEX + j].landFrameX, _tiles[i * TILEX + j].landFrameY);
				}
				else if (_currentTile.type == TYPE::LANDOBJECT)
				{
					_tiles[i * TILEX + j].type = TYPE::LANDOBJECT;
					_tiles[i * TILEX + j].landObjectFrameX = _currentTile.frameX;
					_tiles[i * TILEX + j].landObjectFrameY = _currentTile.frameY;
					_tiles[i * TILEX + j].landObject = MapToolLandObjectSelect(_tiles[i * TILEX + j].landObjectFrameX, _tiles[i * TILEX + j].landObjectFrameY);
				}
				else if (_currentTile.type == TYPE::OBJECT)
				{
					_tiles[i * TILEX + j].type = TYPE::OBJECT;
					_tiles[i * TILEX + j].objectFrameX = _currentTile.frameX;
					_tiles[i * TILEX + j].objectFrameY = _currentTile.frameY;
					_tiles[i * TILEX + j].object = MapToolObjectSelect(_tiles[i * TILEX + j].objectFrameX, _tiles[i * TILEX + j].objectFrameY);
				}
				else if (_currentTile.type == TYPE::TREE)
				{
					_tiles[i * TILEX + j].type = TYPE::TREE;
					_tiles[i * TILEX + j].treeFrameX = _currentTile.frameX;
					_tiles[i * TILEX + j].treeFrameY = _currentTile.frameY;
					_tiles[i * TILEX + j].tree = MapToolTreeSelect(_tiles[i * TILEX + j].treeFrameX, _tiles[i * TILEX + j].treeFrameY);
				}
				break;
			}
		}
	}
}

void mapToolScene::MapToolEraser()
{
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0;i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				if (PtInRect(&_tiles[i * TILEX + j].rc, PointMake(CAMERAMANAGER->getMapToolCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getMapToolCamera().cameraY + _ptMouse.y))) // PointMake(CAMERAMANAGER->getMapToolCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getMapToolCamera().cameraY + _ptMouse.y)))
				{
					_tiles[i * TILEX + j].isClick = false;
					_tiles[i * TILEX + j].type = TYPE::NONE;
					_tiles[i * TILEX + j].terrain = TERRAIN::NONE;
					_tiles[i * TILEX + j].land = LAND::NONE;
					_tiles[i * TILEX + j].landObject = LANDOBJECT::NONE;
					_tiles[i * TILEX + j].object = OBJECT::NONE;
					_tiles[i * TILEX + j].tree = TREE::NONE;
					_tiles[i * TILEX + j].character = CHARACTER::NONE;
					_tiles[i * TILEX + j].terrainFrameX = 0;
					_tiles[i * TILEX + j].terrainFrameY = 0;
					_tiles[i * TILEX + j].objectFrameX = 0;
					_tiles[i * TILEX + j].objectFrameY = 0;
					_tiles[i * TILEX + j].characterFrameX = 0;
					_tiles[i * TILEX + j].characterFrameY = 0;
					_tiles[i * TILEX + j].landObjectFrameX = 0;
					_tiles[i * TILEX + j].landObjectFrameY = 0;
					_tiles[i * TILEX + j].treeFrameX = 0;
					_tiles[i * TILEX + j].treeFrameY = 0;
					break;
				}
			}
		}
	}
}


void mapToolScene::MapToolRender()
{
	PatBlt(CAMERAMANAGER->getMapToolDC(), CAMERAMANAGER->getMapToolCamera().cameraX, CAMERAMANAGER->getMapToolCamera().cameraY, CAMERAMANAGER->getMapToolCamera().cameraSizeX, CAMERAMANAGER->getMapToolCamera().cameraSizeY, BLACKNESS);

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■본 MAP  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■TERRAIN  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		char str[100];
		sprintf_s(str, "%d",i);
		//Rectangle(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc);
		TextOut(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
		if (_tiles[i].type == TYPE::NONE) continue;
		if (_tiles[i].terrain == TERRAIN::GRASS)
		{
			IMAGEMANAGER->findImage("grassTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}
		else if (_tiles[i].terrain == TERRAIN::DESERT)
		{
			IMAGEMANAGER->findImage("desertTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}
		else if (_tiles[i].terrain == TERRAIN::SNOW)
		{
			IMAGEMANAGER->findImage("snowTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}
	}
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ LAND ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].type == TYPE::NONE) continue;
		//Rectangle(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc);
		IMAGEMANAGER->findImage("grassTileLand")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landFrameX, _tiles[i].landFrameY);
	}
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ LAND OBJECT ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].type == TYPE::NONE) continue;
		//Rectangle(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc);
		if (_tiles[i].landObject == LANDOBJECT::GRASS)
		{
			IMAGEMANAGER->findImage("grassTileObject")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landObjectFrameX, _tiles[i].landObjectFrameY);
		}
		else if (_tiles[i].landObject == LANDOBJECT::DESERT)
		{
			IMAGEMANAGER->findImage("desertTileObject")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landObjectFrameX, _tiles[i].landObjectFrameY);
		}
		else if (_tiles[i].landObject == LANDOBJECT::SNOW)
		{
			IMAGEMANAGER->findImage("snowTileObject")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landObjectFrameX, _tiles[i].landObjectFrameY);
		}

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ OBJECT  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

		if (_tiles[i].object != OBJECT::NONE)
		{
			IMAGEMANAGER->findImage("objectTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objectFrameX, _tiles[i].objectFrameY);
		}

		//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ TREE ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		if (_tiles[i].tree != TREE::NONE)
		{
			IMAGEMANAGER->findImage("treeTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].treeFrameX, _tiles[i].treeFrameY);
		}


	}
	CAMERAMANAGER->getMapToolImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getMapToolCamera().cameraX, CAMERAMANAGER->getMapToolCamera().cameraY, CAMERAMANAGER->getMapToolCamera().cameraSizeX, CAMERAMANAGER->getMapToolCamera().cameraSizeY);

	//팔레트 타일 
	for (int i = 0;i < PALETTEX * PALETTEY; i++)
	{
		Rectangle(getMemDC(), _terrainPalette[i].rc);
	}

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■팔레트 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	if (_style[0].isClick)
	{
		// 오른쪽 
		if (_currentTile.type == TYPE::TERRAIN)
		{
			for (int i = 0;i < PALETTEX * PALETTEY; i++)
			{
				IMAGEMANAGER->findImage("grassTilePalette")->frameRender(getMemDC(), _terrainPalette[i].rc.left, _terrainPalette[i].rc.top, _terrainPalette[i].frameX, _terrainPalette[i].frameY);
			}
		}
		else if (_currentTile.type == TYPE::LANDOBJECT)
		{
			for (int i = 0;i < LANDOBJECTX * LANDOBJECTY; i++)
			{
				IMAGEMANAGER->findImage("grassTileObjectPalette")->frameRender(getMemDC(), _landObjectPalette[i].rc.left, _landObjectPalette[i].rc.top, _landObjectPalette[i].frameX, _landObjectPalette[i].frameY);
			}
		}
	}
	else if (_style[1].isClick)
	{
		// 오른쪽 
		if (_currentTile.type == TYPE::TERRAIN)
		{
			for (int i = 0;i < PALETTEX * PALETTEY; i++)
			{
				IMAGEMANAGER->findImage("desertTilePalette")->frameRender(getMemDC(), _terrainPalette[i].rc.left, _terrainPalette[i].rc.top, _terrainPalette[i].frameX, _terrainPalette[i].frameY);
			}
		}
		else if (_currentTile.type == TYPE::LANDOBJECT)
		{
			for (int i = 0;i < LANDOBJECTX * LANDOBJECTY; i++)
			{
				IMAGEMANAGER->findImage("desertTileObjectPalette")->frameRender(getMemDC(), _landObjectPalette[i].rc.left, _landObjectPalette[i].rc.top, _landObjectPalette[i].frameX, _landObjectPalette[i].frameY);
			}
		}
	}
	else if (_style[2].isClick)
	{
		// 오른쪽 
		if (_currentTile.type == TYPE::TERRAIN)
		{
			for (int i = 0;i < PALETTEX * PALETTEY; i++)
			{
				IMAGEMANAGER->findImage("snowTilePalette")->frameRender(getMemDC(), _terrainPalette[i].rc.left, _terrainPalette[i].rc.top, _terrainPalette[i].frameX, _terrainPalette[i].frameY);
			}
		}
		else if (_currentTile.type == TYPE::LANDOBJECT)
		{
			for (int i = 0;i < LANDOBJECTX * LANDOBJECTY; i++)
			{
				IMAGEMANAGER->findImage("snowTileObjectPalette")->frameRender(getMemDC(), _landObjectPalette[i].rc.left, _landObjectPalette[i].rc.top, _landObjectPalette[i].frameX, _landObjectPalette[i].frameY);
			}
		}
	}
	// 랜드는 다 합쳐져 있음 
	if (_currentTile.type == TYPE::LAND)
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
			IMAGEMANAGER->findImage("objectTilePalette")->frameRender(getMemDC(), _objectPalette[i].rc.left, _objectPalette[i].rc.top, _objectPalette[i].frameX, _objectPalette[i].frameY);
		}
	}
	else if (_currentTile.type == TYPE::TREE)
	{
		for (int i = 0;i < TREETILEX * TREETILEY; i++)
		{
			IMAGEMANAGER->findImage("treeTilePalette")->frameRender(getMemDC(), _treePalette[i].rc.left, _treePalette[i].rc.top, _treePalette[i].frameX, _treePalette[i].frameY);
		}
	}

	char str[128];
	sprintf_s(str, "클릭");
	SetTextColor(getMemDC(), RGB(255, 0, 0));

	//스타일 
	for (int i = 0; i < 3;i++)
	{
		Rectangle(getMemDC(), _style[i].rc);
		if (_style[i].isClick)
		{
			TextOut(getMemDC(), _style[i].rc.left, _style[i].rc.top, str, strlen(str));
		}
	}
	// TYPE
	for (int i = 0;i < 7;i++)
	{
		Rectangle(getMemDC(), _type[i].rc);
	}

	// 임시 텍스트 
	char tempStr1[100];
	char tempStr2[100];
	char tempStr3[100];
	char tempStr4[100];
	char tempStr5[100];
	char tempStr6[100];
	char tempStr7[100];
	sprintf_s(tempStr1, "표면");
	sprintf_s(tempStr2, "땅");
	sprintf_s(tempStr3, "데코");
	sprintf_s(tempStr4, "오브");
	sprintf_s(tempStr5, "나무");
	sprintf_s(tempStr6, "예비1");
	sprintf_s(tempStr7, "예비2");
	TextOut(getMemDC(), _type[0].rc.left, _type[0].rc.top, tempStr1, strlen(tempStr1));
	TextOut(getMemDC(), _type[1].rc.left, _type[1].rc.top, tempStr2, strlen(tempStr2));
	TextOut(getMemDC(), _type[2].rc.left, _type[2].rc.top, tempStr3, strlen(tempStr3));
	TextOut(getMemDC(), _type[3].rc.left, _type[3].rc.top, tempStr4, strlen(tempStr4));
	TextOut(getMemDC(), _type[4].rc.left, _type[4].rc.top, tempStr5, strlen(tempStr5));
	TextOut(getMemDC(), _type[5].rc.left, _type[5].rc.top, tempStr6, strlen(tempStr6));
	TextOut(getMemDC(), _type[6].rc.left, _type[6].rc.top, tempStr7, strlen(tempStr7));

	char str2[128];
	sprintf_s(str2, "클릭");
	SetTextColor(getMemDC(), RGB(255, 0, 0));
	// 위치 타일 
	for (int i = 0; i < 9; ++i)
	{
		Rectangle(getMemDC(), _mapButton[i].rc);
		if (_mapButton[i].isClick)
		{
			IMAGEMANAGER->findImage("redButton")->render(getMemDC(), _mapButton[i].rc.left, _mapButton[i].rc.top);
		}
	}

	// 미니맵 
	
	for (int i = 0;i < TILEX * TILEY ; i++)
	{
		Rectangle(getMemDC(), _miniMap[i].rc);
		if(_tiles[i].isClick) IMAGEMANAGER->findImage("minimap")->render(getMemDC(), _miniMap[i].rc.left, _miniMap[i].rc.top);
	}

	// 세이브 슬롯 
	for (int i = 0;i < 5; i++)
	{
		Rectangle(getMemDC(), _saveSlot[i].rc);
	}

	Rectangle(getMemDC(), _saveButton.rc);
	Rectangle(getMemDC(), _loadButton.rc);
	Rectangle(getMemDC(), _exitButton.rc);




	if (_currentTile.type == TYPE::CHARACTER)
	{
		for (int i = 0;i < 25; i++)
		{
			//IMAGEMANAGER->findImage("grassTileCharacterPalette")->frameRender(CAMERAMANAGER->getMapToolDC(), _terrainPalette[i].rc.left, _terrainPalette[i].rc.top, _terrainPalette[i].frameX, _terrainPalette[i].frameY);
		}
	}
}

TERRAIN mapToolScene::MapToolTerrainSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return TERRAIN::NONE;
	if (frameX == 6 && frameY == 6) return TERRAIN::NONE;
	if (_style[0].isClick)
	{
		return TERRAIN::GRASS;
	}
	else if (_style[1].isClick)
	{
		return TERRAIN::DESERT;
	}
	else if (_style[2].isClick)
	{
		return TERRAIN::SNOW;
	}

	return TERRAIN::GRASS;
}

LAND mapToolScene::MapToolLandSelect(int frameX, int frameY)
{

	if (_style[0].isClick)
	{
		if(frameY == 0 || frameY ==1) return LAND::GRASS;
	}
	else if (_style[1].isClick)
	{
		if (frameY == 2 || frameY == 3) return LAND::DESERT;
	}
	else if (_style[2].isClick)
	{
		if (frameY == 4 || frameY == 5) return LAND::SNOW;
	}

	return LAND::NONE;
}

LANDOBJECT mapToolScene::MapToolLandObjectSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return LANDOBJECT::NONE;
	for (int i = 1;i < 5; i++)	// 1,2,3,4
	{
		if (frameX == i && frameY == 4) return LANDOBJECT::NONE;
	}
	if (_style[0].isClick)
	{
		return LANDOBJECT::GRASS;
	}
	else if (_style[1].isClick)
	{
		return LANDOBJECT::DESERT;
	}
	else if (_style[2].isClick)
	{
		return LANDOBJECT::SNOW;
	}

	return LANDOBJECT::GRASS;
}

OBJECT mapToolScene::MapToolObjectSelect(int frameX, int frameY)
{
	if(frameX == 6 && frameY ==2 || frameX == 5 && frameY == 2) return OBJECT::NONE;
	for (int i = 0; i < OBJECTY; i++)
	{
		for (int j = 0;j < OBJECTX; j ++)
		{
			if ((frameY * OBJECTX + frameX) == (i * OBJECTX + j)) return (OBJECT)(frameX * OBJECTX + frameY);
		}
	}
	return OBJECT::NONE;
}

TREE mapToolScene::MapToolTreeSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return TREE::BASIC;
	if (frameX == 1 && frameY == 0) return TREE::RED;
	if (frameX == 2 && frameY == 0) return TREE::SNOW;
	if (frameX == 3 && frameY == 0) return TREE::CACTUS;
	return TREE::NONE;
}

CHARACTER mapToolScene::MapToolCharacterSelect(int frameX, int frameY)
{

	return CHARACTER::NONE;
}
