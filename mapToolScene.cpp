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
	MapToolImage();		// 이미지 셋팅
	MapToolSetup();		// 맵툴 셋팅
	CURSORMANAGER->setCursor();	// 커서 셋팅
	return S_OK;
}

void mapToolScene::release()
{
}

void mapToolScene::update()
{
	SaveAndLoad();          // 세이브 로드

	MapToolCollision();		// 클릭 
	MapToolEraser();
}

void mapToolScene::render()
{
	MapToolRender();		// 렌더
	CAMERAMANAGER->MapToolCameraRectUpdate();
}

void mapToolScene::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile(_saveName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void mapToolScene::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile(_saveName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//맵을 불로온 직후 타일의 속성을 매겨준다
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

void mapToolScene::SaveAndLoad()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//버튼 
		for (int i = 0; i < SAVESLOT; i++)
		{
			if (PtInRect(&_saveSlot[i].rc, _ptMouse))
			{
				_saveSlotDirection = i;
				break;
			}
		}

		if (PtInRect(&_saveButton.rc, _ptMouse))
		{
			this->save();
		}
		if (PtInRect(&_loadButton.rc, _ptMouse))
		{
			this->load();
		}
		if (PtInRect(&_exitButton.rc, _ptMouse))
		{
			SCENEMANAGER->changeScene("MAINMENU");
		}

	}

	for (int i = 0; i < SAVESLOT; i++)
	{
		_saveSlot[i].isClick = false;
	}

	switch (_saveSlotDirection)
	{
	case 0:
		_saveName = "inGameNumber1.map";
		_saveSlot[_saveSlotDirection].isClick = true;
		break;
	case 1:
		_saveName = "inGameNumber2.map";
		_saveSlot[_saveSlotDirection].isClick = true;
		break;
	case 2:
		_saveName = "inGameNumber3.map";
		_saveSlot[_saveSlotDirection].isClick = true;
		break;
	case 3:
		_saveName = "inGameNumber4.map";
		_saveSlot[_saveSlotDirection].isClick = true;
		break;
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

	IMAGEMANAGER->addImage("rect", "./image/mapTool/rect.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rect2", "./image/mapTool/rect2.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("typeButton", "./image/mapTool/typeButton.bmp", 280, 40, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("styleButton", "./image/mapTool/styleButton.bmp", 180, 180, 2, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("saveSlotButton", "./image/mapTool/saveSlotButton.bmp", 280, 60, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("redButtonRect", "./image/mapTool/redButtonRect.bmp", 45, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimapBackground", "./image/mapTool/minimapBackground.bmp", 135, 135, false, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("saveLoad", "./image/mapTool/saveLoad.bmp", 100, 80, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("exit", "./image/mapTool/exit.bmp", 60, 40, true, RGB(255, 0, 255));

	//추가 


	//타일
	IMAGEMANAGER->addFrameImage("graveTile", "./image/mapTool/graveTile.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("graveTilePalette", "./image/mapTool/graveTilePalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("volcanoTile", "./image/mapTool/volcanoTile.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("volcanoTilePalette", "./image/mapTool/volcanoTilePalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));
	//랜드 오브젝트
	IMAGEMANAGER->addFrameImage("graveTileObject", "./image/mapTool/graveTile.bmp", 300, 300, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("graveTileObjectPalette", "./image/mapTool/graveTileObjectPalette.bmp", 200, 200, 5, 5, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("volcanoTileObject", "./image/mapTool/volcanoTile.bmp", 300, 300, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("volcanoTileObjectPalette", "./image/mapTool/volcanoTileObjectPalette.bmp", 200, 200, 5, 5, true, RGB(255, 0, 255));
	//랜드
	IMAGEMANAGER->addFrameImage("graveTileLand", "./image/mapTool/graveTileLand.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("graveTileLandPalette", "./image/mapTool/graveTileLandPalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("characterTile", "./image/mapTool/characterTile.bmp", 420, 60, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("characterTilePalette", "./image/mapTool/characterTilePalette.bmp", 280, 40, 7, 1, true, RGB(255, 0, 255));

	//던전
	IMAGEMANAGER->addFrameImage("fireTempleTile", "./image/mapTool/fireTempleTile.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fireTempleTilePalette", "./image/mapTool/fireTempleTilePalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("templeObject", "./image/mapTool/templeObject.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("templeObjectPalette", "./image/mapTool/templeObjectPalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));
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
	_saveSlotDirection = 0;
	// 이미지이름
	_saveName = "inGameNumber1.map";

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 본 MAP ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
			_tiles[i * TILEX + j].templeObject = TEMPLEOBJECT::NONE;
			_tiles[i * TILEX + j].building = BUILDING::NONE;
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
			_tiles[i * TILEX + j].templeObjectFrameX = 0;
			_tiles[i * TILEX + j].templeObjectFrameY = 0;
			_tiles[i * TILEX + j].idx = j;
			_tiles[i * TILEX + j].idy = i;
			_tiles[i * TILEX + j].isClick = false;
			_tiles[i * TILEX + j].isObject = false;
			_tiles[i * TILEX + j].isRender = false;
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
				i * 120, WINSIZEX - IMAGEMANAGER->findImage("treeTilePalette")->getWidth() + j * PALETTESIZE + PALETTESIZE, i * 120 + 120);
			_treePalette[i * TREETILEX + j].frameX = j;
			_treePalette[i * TREETILEX + j].frameY = i;
		}
	}
	
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 케릭터 및 애너미  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 
	for (int i = 0; i < CHARACTERX; i++)
	{
		SetRect(&_characterPalette[i].rc, WINSIZEX - IMAGEMANAGER->findImage("characterTilePalette")->getWidth() + (i * PALETTESIZE),
			0, WINSIZEX - IMAGEMANAGER->findImage("characterTilePalette")->getWidth() + (i * PALETTESIZE) + PALETTESIZE, PALETTESIZE);
		_characterPalette[i].frameX = i;
		_characterPalette[i].frameY = 0;
	}
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ templeObject  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 

	for (int i = 0; i < PALETTEY; i++)
	{
		for (int j = 0;j < PALETTEX; j++)
		{
			SetRect(&_templeObjectPalette[i * PALETTEX + j].rc, WINSIZEX - IMAGEMANAGER->findImage("templeObjectPalette")->getWidth() + (j * PALETTESIZE),
				i * PALETTESIZE, WINSIZEX - IMAGEMANAGER->findImage("templeObjectPalette")->getWidth() + j * PALETTESIZE + PALETTESIZE, i * PALETTESIZE + PALETTESIZE);
			_templeObjectPalette[i * PALETTEX + j].frameX =  j;
			_templeObjectPalette[i * PALETTEX + j].frameY =  i;
		}
	}
	//스타일 (90X20)
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0;j < 3; ++j)
		{
			SetRect(&_style[i * 3 + j].rc, 920 + j * 95, 280 + (30 * i), 920 + j * 95 + 90, 310 + (30 * i));
			_style[i * 3 + j].isClick = false;
		}
	}
	_style[0].isClick = true;
	/*for (int i = 0; i < 3; ++i)
	{
		SetRect(&_style[i].rc, 920 + i * 95, 285, 920 + i * 95 + 90, 305);
		_style[i].isClick = false;
	}
	_style[0].isClick = true;*/

	// 그림 TYPE     (40X40)
	//  0 지형 1 랜드 2 오프젝트 
	// 
	for (int i = 0;i < 7;i++)
	{
		SetRect(&_type[i].rc, 920 + i * 40, 340, 920 + i * 40 + 40, 380);
	}

	// 위치를 나타내는 버튼 
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SetRect(&_mapButton[i * 3 + j].rc, 920 + j * _mapButtonSize, 390 + i * _mapButtonSize, 920 + j * _mapButtonSize + _mapButtonSize, 390 + i * _mapButtonSize + _mapButtonSize);
			_mapButton[i * 3 + j].isClick = false;
		}
	}
	_mapButton[0].isClick = true;
	// MINIMAP
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_miniMap[i * (TILEX)+j].rc, WINSIZEX - 140 + j * _miniMapSizeWidth, 390 + (i * _miniMapSizeHeight), WINSIZEX - 140 + (j * _miniMapSizeWidth) + _miniMapSizeWidth, 390 + (i * _miniMapSizeHeight) + _miniMapSizeHeight);
		}
	}

	// SAVESLOT
	for (int i = 0; i < SAVESLOT; i++)
	{
		SetRect(&_saveSlot[i].rc, 920, WINSIZEY - 180 + i * _saveSlotSizeHeight, 920 + _saveSlotSizeWidth, WINSIZEY - 180 + i * _saveSlotSizeHeight + _saveSlotSizeHeight);
		_saveSlot[i].isClick = false;
	}

	SetRect(&_saveButton.rc, 920, 670, 1020, 710);    // 100 X 40
	SetRect(&_loadButton.rc, 1020, 670, 1120, 710);
	SetRect(&_exitButton.rc, 1130, 670, 1190, 710);     // 60 X 40 
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
		for (int i = 0; i < MAXSTYLE; i++)
		{
			if (PtInRect(&_style[i].rc, _ptMouse))
			{
				for (int i = 0;i < MAXSTYLE;i++)
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
					_currentTile.type = TYPE::OBJECT;			// 오브젝트 
					break;
				case 4:
					_currentTile.type = TYPE::TREE;				// 나무 
					break;
				case 5:
					_currentTile.type = TYPE::CHARACTER;		// 케릭터 및 애너미 
					break;
				case 6:
					_currentTile.type = TYPE::TEMPLEOBJECT;
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
	if (_currentTile.type == TYPE::TERRAIN || _currentTile.type == TYPE::LAND || _currentTile.type == TYPE::TEMPLEOBJECT)
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
	else if (_currentTile.type == TYPE::CHARACTER)
	{
		for (int i = 0; i < CHARACTERX; i++)
		{
			if (PtInRect(&_characterPalette[i].rc, PointMake(CAMERAMANAGER->getMapToolCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getMapToolCamera().cameraY + _ptMouse.y)))
			{
				_currentTile.frameX = i;
				_currentTile.frameY = 0;
				break;
			}
		}
	}


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
				else if (_currentTile.type == TYPE::CHARACTER)
				{
					_tiles[i * TILEX + j].type = TYPE::CHARACTER;
					_tiles[i * TILEX + j].characterFrameX = _currentTile.frameX;
					_tiles[i * TILEX + j].characterFrameY = _currentTile.frameY;
					_tiles[i * TILEX + j].character = MapToolCharacterSelect(_tiles[i * TILEX + j].characterFrameX, _tiles[i * TILEX + j].characterFrameY);
				}
				else if (_currentTile.type == TYPE::TEMPLEOBJECT)
				{
					_tiles[i * TILEX + j].type = TYPE::TEMPLEOBJECT;
					_tiles[i * TILEX + j].templeObjectFrameX = _currentTile.frameX;
					_tiles[i * TILEX + j].templeObjectFrameY = _currentTile.frameY;
					_tiles[i * TILEX + j].templeObject = MapToolTempleObjectSelect(_tiles[i * TILEX + j].templeObjectFrameX, _tiles[i * TILEX + j].templeObjectFrameY);
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
					_tiles[i * TILEX + j].building = BUILDING::NONE;	//빌딩 추가 
					_tiles[i * TILEX + j].templeObject = TEMPLEOBJECT::NONE;
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
					_tiles[i * TILEX + j].landFrameX = 0;
					_tiles[i * TILEX + j].landFrameY = 0;
					_tiles[i * TILEX + j].templeObjectFrameX = 0;
					_tiles[i * TILEX + j].templeObjectFrameY = 0;
					_tiles[i * TILEX + j].isRender = false;
					_tiles[i * TILEX + j].isObject = false;
					cout << "타입:" << (int)_tiles[i * TILEX + j].type << endl;
					cout << "지형:" << (int)_tiles[i * TILEX + j].terrain << endl;


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

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//인덱스 디버깅용
		//char str[100];
		//sprintf_s(str, "%d",i);
		//Rectangle(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc);
		//TextOut(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));


		//배경 렉트 그리기 
		IMAGEMANAGER->findImage("rect2")->render(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top);

		RECT temp;
		if (!IntersectRect(&temp, &CAMERAMANAGER->getWorldRect(), &_tiles[i].rc)) continue;

		//타입이 NONE이면 다음으로
		if (_tiles[i].type == TYPE::NONE) continue;

		//만약 화면 렉트와 충돌되지 않으면 그리지 않는다.

		//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■TERRAIN  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		if (_tiles[i].terrain != TERRAIN::NONE)
		{
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
			else if (_tiles[i].terrain == TERRAIN::GRAVE)
			{
				IMAGEMANAGER->findImage("graveTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
			}
			else if (_tiles[i].terrain == TERRAIN::VOLCANO)
			{
				IMAGEMANAGER->findImage("volcanoTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
			}
			else if (_tiles[i].terrain == TERRAIN::FIRETEMPLE)
			{
				IMAGEMANAGER->findImage("fireTempleTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
			}
		}

		//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ LAND ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		if (_tiles[i].land != LAND::NONE)
		{
			if (_tiles[i].land == LAND::GRASS || _tiles[i].land == LAND::DESERT || _tiles[i].land == LAND::SNOW)
			{
				IMAGEMANAGER->findImage("grassTileLand")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landFrameX, _tiles[i].landFrameY);
			}
			else if (_tiles[i].land == LAND::GRAVE || _tiles[i].land == LAND::VOLCANO)
			{
				IMAGEMANAGER->findImage("graveTileLand")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landFrameX, _tiles[i].landFrameY);
			}
			//Rectangle(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc);
		}

		//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ LAND OBJECT ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		if (_tiles[i].landObject != LANDOBJECT::NONE)
		{
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
			else if (_tiles[i].landObject == LANDOBJECT::GRAVE)
			{
				IMAGEMANAGER->findImage("graveTileObject")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landObjectFrameX, _tiles[i].landObjectFrameY);
			}
			else if (_tiles[i].landObject == LANDOBJECT::VOLCANO)
			{
				IMAGEMANAGER->findImage("volcanoTileObject")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landObjectFrameX, _tiles[i].landObjectFrameY);
			}
		}

		//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ OBJECT  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		if (_tiles[i].object != OBJECT::NONE)
		{
			IMAGEMANAGER->findImage("objectTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objectFrameX, _tiles[i].objectFrameY);
		}
	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ TREE ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		if (_tiles[i].type == TYPE::NONE) continue;
		if (_tiles[i].tree != TREE::NONE)
		{
			IMAGEMANAGER->findImage("treeTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].treeFrameX, _tiles[i].treeFrameY);
		}
		if (_tiles[i].character != CHARACTER::NONE)
		{
			IMAGEMANAGER->findImage("characterTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].characterFrameX, _tiles[i].characterFrameY);
		}
		if (_tiles[i].templeObject != TEMPLEOBJECT::NONE)
		{
			IMAGEMANAGER->findImage("templeObject")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].templeObjectFrameX, _tiles[i].templeObjectFrameY);
		}
	}
	////■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ LAND ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	//if (_tiles[i].type == TYPE::NONE) continue;
	//	if (_tiles[i].land == LAND::NONE) continue;
	//	//Rectangle(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc);
	//	IMAGEMANAGER->findImage("grassTileLand")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landFrameX, _tiles[i].landFrameY);
	//}
	////■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ LAND OBJECT ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
		//if (_tiles[i].type == TYPE::NONE) continue;
		////Rectangle(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc);
		//if (_tiles[i].landObject == LANDOBJECT::GRASS)
		//{
		//	IMAGEMANAGER->findImage("grassTileObject")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landObjectFrameX, _tiles[i].landObjectFrameY);
		//}
		//else if (_tiles[i].landObject == LANDOBJECT::DESERT)
		//{
		//	IMAGEMANAGER->findImage("desertTileObject")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landObjectFrameX, _tiles[i].landObjectFrameY);
		//}
		//else if (_tiles[i].landObject == LANDOBJECT::SNOW)
		//{
		//	IMAGEMANAGER->findImage("snowTileObject")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landObjectFrameX, _tiles[i].landObjectFrameY);
		//}

	//	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ OBJECT  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	//	if (_tiles[i].object != OBJECT::NONE)
	//	{
	//		IMAGEMANAGER->findImage("objectTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objectFrameX, _tiles[i].objectFrameY);
	//	}

	//	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ TREE ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	//	if (_tiles[i].tree != TREE::NONE)
	//	{
	//		IMAGEMANAGER->findImage("treeTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].treeFrameX, _tiles[i].treeFrameY);
	//	}


	//}
	CAMERAMANAGER->getMapToolImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getMapToolCamera().cameraX, CAMERAMANAGER->getMapToolCamera().cameraY, CAMERAMANAGER->getMapToolCamera().cameraSizeX, CAMERAMANAGER->getMapToolCamera().cameraSizeY);

	//팔레트 타일 
	for (int i = 0;i < PALETTEX * PALETTEY; i++)
	{
		Rectangle(getMemDC(), _terrainPalette[i].rc);
	}

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■팔레트 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	int palletteWidth = IMAGEMANAGER->findImage("grassTilePalette")->getWidth();
	int palletteObjectWidth = IMAGEMANAGER->findImage("grassTileObjectPalette")->getWidth();
	if (_style[0].isClick) // grass
	{
		//// 오른쪽 
		if (_currentTile.type == TYPE::TERRAIN)
		{
			IMAGEMANAGER->findImage("grassTilePalette")->render(getMemDC(), WINSIZEX - palletteWidth, 0);
		}
		else if (_currentTile.type == TYPE::LANDOBJECT)
		{
			IMAGEMANAGER->findImage("grassTileObjectPalette")->render(getMemDC(), WINSIZEX - palletteObjectWidth, 0);
		}
	}
	else if (_style[1].isClick) // desert
	{
		// 오른쪽 
		if (_currentTile.type == TYPE::TERRAIN)
		{
			IMAGEMANAGER->findImage("desertTilePalette")->render(getMemDC(), WINSIZEX - palletteWidth, 0);
		}
		else if (_currentTile.type == TYPE::LANDOBJECT)
		{
			IMAGEMANAGER->findImage("desertTileObjectPalette")->render(getMemDC(), WINSIZEX - palletteObjectWidth, 0);
		}
	}
	else if (_style[2].isClick) // winter
	{
		// 오른쪽 
		if (_currentTile.type == TYPE::TERRAIN)
		{
			IMAGEMANAGER->findImage("snowTilePalette")->render(getMemDC(), WINSIZEX - palletteWidth, 0);
		}
		else if (_currentTile.type == TYPE::LANDOBJECT)
		{
			IMAGEMANAGER->findImage("snowTileObjectPalette")->render(getMemDC(), WINSIZEX - palletteObjectWidth, 0);
		}
	}
	else if (_style[3].isClick) // grave
	{
		if (_currentTile.type == TYPE::TERRAIN)
		{
			IMAGEMANAGER->findImage("graveTilePalette")->render(getMemDC(), WINSIZEX - palletteWidth, 0);
		}
		else if (_currentTile.type == TYPE::LANDOBJECT)
		{
			IMAGEMANAGER->findImage("graveTileObjectPalette")->render(getMemDC(), WINSIZEX - palletteObjectWidth, 0);
		}
	}
	else if (_style[4].isClick) // volcano
	{
		if (_currentTile.type == TYPE::TERRAIN)
		{
			IMAGEMANAGER->findImage("volcanoTilePalette")->render(getMemDC(), WINSIZEX - palletteWidth, 0);
		}
		else if (_currentTile.type == TYPE::LANDOBJECT)
		{
			IMAGEMANAGER->findImage("volcanoTileObjectPalette")->render(getMemDC(), WINSIZEX - palletteObjectWidth, 0);
		}
	}
	else if (_style[5].isClick) // volcano
	{
		if (_currentTile.type == TYPE::TERRAIN)
		{
			IMAGEMANAGER->findImage("fireTempleTilePalette")->render(getMemDC(), WINSIZEX - palletteWidth, 0);
		}
		else if (_currentTile.type == TYPE::LANDOBJECT)
		{
			//IMAGEMANAGER->findImage("volcanoTileObjectPalette")->render(getMemDC(), WINSIZEX - palletteObjectWidth, 0);
		}
	}

	// 랜드는 다 합쳐져 있음 
	if (_currentTile.type == TYPE::LAND)
	{
		if (_style[0].isClick || _style[1].isClick || _style[2].isClick)  // gress, desert, winter
		{
			IMAGEMANAGER->findImage("grassTileLandPalette")->render(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("grassTileLandPalette")->getWidth(), 0);
		}
		else if (_style[3].isClick || _style[4].isClick)  // grave, volcano
		{
			IMAGEMANAGER->findImage("graveTileLandPalette")->render(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("grassTileLandPalette")->getWidth(), 0);
		}
	}
	else if (_currentTile.type == TYPE::OBJECT)
	{
		IMAGEMANAGER->findImage("objectTilePalette")->render(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("objectTilePalette")->getWidth(), 0);
	}
	else if (_currentTile.type == TYPE::TREE)
	{
		IMAGEMANAGER->findImage("treeTilePalette")->render(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("treeTilePalette")->getWidth(), 0);
	}
	else if (_currentTile.type == TYPE::CHARACTER)
	{
		IMAGEMANAGER->findImage("characterTilePalette")->render(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("characterTilePalette")->getWidth(), 0);
	}
	else if (_currentTile.type == TYPE::TEMPLEOBJECT)
	{
		IMAGEMANAGER->findImage("templeObjectPalette")->render(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("templeObjectPalette")->getWidth(), 0);
	}

	char str[128];
	sprintf_s(str, "클릭");
	SetTextColor(getMemDC(), RGB(255, 0, 0));



	// 임시 텍스트 
	//char tempStr1[100];
	//char tempStr2[100];
	//char tempStr3[100];
	//char tempStr4[100];
	//char tempStr5[100];
	//char tempStr6[100];
	//char tempStr7[100];
	//sprintf_s(tempStr1, "표면");
	//sprintf_s(tempStr2, "땅");
	//sprintf_s(tempStr3, "데코");
	//sprintf_s(tempStr4, "오브");
	//sprintf_s(tempStr5, "나무");
	//sprintf_s(tempStr6, "예비1");
	//sprintf_s(tempStr7, "예비2");
	//TextOut(getMemDC(), _type[0].rc.left, _type[0].rc.top, tempStr1, strlen(tempStr1));
	//TextOut(getMemDC(), _type[1].rc.left, _type[1].rc.top, tempStr2, strlen(tempStr2));
	//TextOut(getMemDC(), _type[2].rc.left, _type[2].rc.top, tempStr3, strlen(tempStr3));
	//TextOut(getMemDC(), _type[3].rc.left, _type[3].rc.top, tempStr4, strlen(tempStr4));
	//TextOut(getMemDC(), _type[4].rc.left, _type[4].rc.top, tempStr5, strlen(tempStr5));
	//TextOut(getMemDC(), _type[5].rc.left, _type[5].rc.top, tempStr6, strlen(tempStr6));
	//TextOut(getMemDC(), _type[6].rc.left, _type[6].rc.top, tempStr7, strlen(tempStr7));

	//char str2[128];
	//sprintf_s(str2, "클릭");
	//SetTextColor(getMemDC(), RGB(255, 0, 0));





	for (int i = 0; i < 9; i++)
	{
		//스타일 
		if (i < MAXSTYLE)
		{
			if (_style[i].isClick)
			{
				IMAGEMANAGER->findImage("styleButton")->frameRender(getMemDC(), _style[i].rc.left, _style[i].rc.top, 1, i);
			}
			else
			{
				IMAGEMANAGER->findImage("styleButton")->frameRender(getMemDC(), _style[i].rc.left, _style[i].rc.top, 0, i);
			}
			//Rectangle(getMemDC(), _style[i].rc); //  임시렉트 
		}
		//세이브 슬롯 
		if (i < SAVESLOT)
		{
			if (_saveSlot[i].isClick)
			{
				IMAGEMANAGER->findImage("saveSlotButton")->frameRender(getMemDC(), _saveSlot[i].rc.left, _saveSlot[i].rc.top, 0, 0);
			}
			else
			{
				IMAGEMANAGER->findImage("saveSlotButton")->frameRender(getMemDC(), _saveSlot[i].rc.left, _saveSlot[i].rc.top, 0, 1);
			}
			//Rectangle(getMemDC(), _saveSlot[i].rc);
		}

		// TYPE
		if (i < 7)
		{
			IMAGEMANAGER->findImage("typeButton")->frameRender(getMemDC(), _type[i].rc.left, _type[i].rc.top, i, 0);
			//Rectangle(getMemDC(), _type[i].rc);
		}

		// 위치 타일 
		if (i < 9)
		{
			IMAGEMANAGER->findImage("redButtonRect")->render(getMemDC(), _mapButton[i].rc.left, _mapButton[i].rc.top);
			if (_mapButton[i].isClick)
			{
				IMAGEMANAGER->findImage("redButton")->render(getMemDC(), _mapButton[i].rc.left, _mapButton[i].rc.top);
			}
			//Rectangle(getMemDC(), _mapButton[i].rc);
		}
	}


	// 미니맵 
	IMAGEMANAGER->findImage("minimapBackground")->render(getMemDC(), _miniMap[0].rc.left, _miniMap[0].rc.top);
	for (int i = 0;i < TILEX * TILEY; i++)
	{
		//Rectangle(getMemDC(), _miniMap[i].rc);
		if (_tiles[i].isClick) IMAGEMANAGER->findImage("minimap")->render(getMemDC(), _miniMap[i].rc.left, _miniMap[i].rc.top);
	}


	IMAGEMANAGER->findImage("saveLoad")->frameRender(getMemDC(), _saveButton.rc.left, _saveButton.rc.top, 0, 0);
	IMAGEMANAGER->findImage("saveLoad")->frameRender(getMemDC(), _loadButton.rc.left, _loadButton.rc.top, 0, 1);
	IMAGEMANAGER->findImage("exit")->render(getMemDC(), _exitButton.rc.left, _exitButton.rc.top);
	/*Rectangle(getMemDC(), _saveButton.rc);
	Rectangle(getMemDC(), _loadButton.rc);*/
	//Rectangle(getMemDC(), _exitButton.rc);

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
	else if (_style[3].isClick)
	{
		return TERRAIN::GRAVE;
	}
	else if (_style[4].isClick)
	{
		return TERRAIN::VOLCANO;
	}
	else if (_style[5].isClick)
	{
		return TERRAIN::FIRETEMPLE;
	}

	return TERRAIN::GRASS;
}

LAND mapToolScene::MapToolLandSelect(int frameX, int frameY)
{
	if (frameY == 6) return LAND::WATER;
	if (_style[0].isClick)
	{
		if (frameY == 0 || frameY == 1) return LAND::GRASS;
	}
	else if (_style[1].isClick)
	{
		if (frameY == 2 || frameY == 3) return LAND::DESERT;
	}
	else if (_style[2].isClick)
	{
		if (frameY == 4 || frameY == 5) return LAND::SNOW;
	}
	else if (_style[3].isClick)
	{
		if (frameY == 0 || frameY == 1) return LAND::GRAVE;
	}
	else if (_style[4].isClick)
	{
		if (frameY == 2 || frameY == 3) return LAND::VOLCANO;
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
	else if (_style[3].isClick)
	{
		return LANDOBJECT::GRAVE;
	}
	else if (_style[4].isClick)
	{
		return LANDOBJECT::VOLCANO;
	}

	return LANDOBJECT::GRASS;
}

OBJECT mapToolScene::MapToolObjectSelect(int frameX, int frameY)
{
	if (frameX == 6 && frameY == 2 || frameX == 5 && frameY == 2) return OBJECT::NONE;
	for (int i = 0; i < OBJECTY; i++)
	{
		for (int j = 0;j < OBJECTX; j++)
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
	if (frameX == 0 && frameY == 0) return CHARACTER::PLAYER;
	if (frameX == 1 && frameY == 0) return CHARACTER::SLIME;
	if (frameX == 2 && frameY == 0) return CHARACTER::BOAR;
	if (frameX == 3 && frameY == 0) return CHARACTER::DEMON;
	if (frameX == 4 && frameY == 0) return CHARACTER::SKULL;
	if (frameX == 5 && frameY == 0) return CHARACTER::DEMON_BOSS;

	return CHARACTER::NONE;
}

TEMPLEOBJECT mapToolScene::MapToolTempleObjectSelect(int frameX, int frameY)
{
	//0 building 
	if (frameX == 0 && frameY == 0) return TEMPLEOBJECT::FURNACE;
	if (frameX == 1 && frameY == 0) return TEMPLEOBJECT::FORGE;
	if (frameX == 2 && frameY == 0) return TEMPLEOBJECT::FURNACE;
	if (frameX == 3 && frameY == 0) return TEMPLEOBJECT::BRIDGE;
	if (frameX == 4 && frameY == 0) return TEMPLEOBJECT::FISHTRAP;

	if (frameX == 0 && frameY == 1) return TEMPLEOBJECT::DRUIDTREE;
	if (frameX == 1 && frameY == 1) return TEMPLEOBJECT::RAINBOW;
	if (frameX == 2 && frameY == 1) return TEMPLEOBJECT::TREASURECHEST;

	if (frameX == 0 && frameY == 2) return TEMPLEOBJECT::TEMPLE_ENTRANCE;
	if (frameX == 1 && frameY == 2) return TEMPLEOBJECT::TEMPLE_LANTERN;
	if (frameX == 2 && frameY == 2) return TEMPLEOBJECT::TEMPLE_DOOR_BOSS;

	for (int i = 3; i < 7;i++)  // y 
	{
		if(frameX == 0 && frameY == i) return TEMPLEOBJECT::TEMPLE_CANNON;
		if (frameX == 1 && frameY == i) return TEMPLEOBJECT::TEMPLE_DOOR;
		if (frameX == 2 && frameY == i) return TEMPLEOBJECT::TEMPLE_DOOR_BLUE;
		if (frameX == 3 && frameY == i) return TEMPLEOBJECT::TEMPLE_DOOR_GREEN;
		if (frameX == 4 && frameY == i) return TEMPLEOBJECT::TEMPLE_DOOR_RED;
	}
	


	return TEMPLEOBJECT::NONE;
}
