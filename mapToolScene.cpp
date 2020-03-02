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
	MapToolImage();		// �̹��� ����
	MapToolSetup();		// ���� ����
	CURSORMANAGER->setCursor();	// Ŀ�� ����
	return S_OK;
}

void mapToolScene::release()
{
}

void mapToolScene::update()
{
	saveLoadClick();          // ���̺� �ε�

	MapToolCollision();		  // Ÿ�� Ŭ�� 
	MapToolEraser();		  // Ÿ�� ����
}

void mapToolScene::render()
{
	CAMERAMANAGER->MapToolCameraRectUpdate(); // ī�޶� ��Ʈ 
	MapToolRender();						  // ����
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

	//���� �ҷο� ���� Ÿ���� �Ӽ��� �Ű��ش�
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

void mapToolScene::saveLoadClick()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//���̺� ��ư�� ������
		for (int i = 0; i < SAVESLOT; i++)
		{
			if (PtInRect(&_saveSlot[i].rc, _ptMouse))
			{
				_saveSlotDirection = i;
				break;
			}
		}
		// ��� ��ư ��Ȱ��ȭ
		for (int i = 0; i < SAVESLOT; i++)
		{
			_saveSlot[i].isClick = false;
		}
		// ��ư ����
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

		//���̺� ��ư�� ������ 
		if (PtInRect(&_saveButton.rc, _ptMouse))
		{
			this->save();
		}
		//�ε� ��ư�� ������
		if (PtInRect(&_loadButton.rc, _ptMouse))
		{
			this->load();
		}
		//������ ��ư�� ������
		if (PtInRect(&_exitButton.rc, _ptMouse))
		{
			//���� �޴���
			SCENEMANAGER->changeScene("MAINMENU");
		}
	}
}

void mapToolScene::MapToolImage()
{
	//Ÿ��
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

	//������Ʈ
	IMAGEMANAGER->addFrameImage("objectTile", "./image/mapTool/objectTile.bmp", 420, 180, 7, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("objectTilePalette", "./image/mapTool/objectTilePalette.bmp", 280, 120, 7, 3, true, RGB(255, 0, 255));
	//����Ÿ�� 
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

	//�߰� 


	//Ÿ��
	IMAGEMANAGER->addFrameImage("graveTile", "./image/mapTool/graveTile.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("graveTilePalette", "./image/mapTool/graveTilePalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("volcanoTile", "./image/mapTool/volcanoTile.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("volcanoTilePalette", "./image/mapTool/volcanoTilePalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));
	//���� ������Ʈ
	IMAGEMANAGER->addFrameImage("graveTileObject", "./image/mapTool/graveTile.bmp", 300, 300, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("graveTileObjectPalette", "./image/mapTool/graveTileObjectPalette.bmp", 200, 200, 5, 5, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("volcanoTileObject", "./image/mapTool/volcanoTile.bmp", 300, 300, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("volcanoTileObjectPalette", "./image/mapTool/volcanoTileObjectPalette.bmp", 200, 200, 5, 5, true, RGB(255, 0, 255));
	//����
	IMAGEMANAGER->addFrameImage("graveTileLand", "./image/mapTool/graveTileLand.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("graveTileLandPalette", "./image/mapTool/graveTileLandPalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("characterTile", "./image/mapTool/characterTile.bmp", 420, 60, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("characterTilePalette", "./image/mapTool/characterTilePalette.bmp", 280, 40, 7, 1, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addFrameImage("fireTempleTile", "./image/mapTool/fireTempleTile.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fireTempleTilePalette", "./image/mapTool/fireTempleTilePalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("templeObject", "./image/mapTool/templeObject.bmp", 420, 420, 7, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("templeObjectPalette", "./image/mapTool/templeObjectPalette.bmp", 280, 280, 7, 7, true, RGB(255, 0, 255));
}

void mapToolScene::MapToolSetup()
{
	//������ Ÿ�� �ʱ�ȭ
	_currentTile.frameX = 0;
	_currentTile.frameY = 0;
	_currentTile.type = TYPE::NONE;
	_currentTile.terrain = TERRAIN::GRASS;

	_mapButtonSize = 45;		// �� ��ư ������ �ʱ�ȭ 
	_miniMapSizeWidth = 3;		// MINIMAP ���� 
	_miniMapSizeHeight = 3.75;	// MINIMAP ���� 

	_saveSlotDirection = 0;  //SAVESLOT ����
	_saveSlotWidth = 280;	 //���� 
	_saveSlotHeight = 30;	 //���� 

	_saveName = "inGameNumber1.map";  //�̹��� �̸� �ʱ�ȭ 

	//����������������������������������������� �� MAP ���������������������������������������
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
			_tiles[i * TILEX + j].landFrameX = 0;
			_tiles[i * TILEX + j].landFrameY = 0;
			_tiles[i * TILEX + j].landObjectFrameX = 0;
			_tiles[i * TILEX + j].landObjectFrameY = 0;
			_tiles[i * TILEX + j].objectFrameX = 0;
			_tiles[i * TILEX + j].objectFrameY = 0;
			_tiles[i * TILEX + j].treeFrameX = 0;
			_tiles[i * TILEX + j].treeFrameY = 0;
			_tiles[i * TILEX + j].characterFrameX = 0;
			_tiles[i * TILEX + j].characterFrameY = 0;
			_tiles[i * TILEX + j].templeObjectFrameX = 0;
			_tiles[i * TILEX + j].templeObjectFrameY = 0;
			_tiles[i * TILEX + j].idx = j;
			_tiles[i * TILEX + j].idy = i;
			_tiles[i * TILEX + j].isClick = false;
			_tiles[i * TILEX + j].isObject = false;
			_tiles[i * TILEX + j].isRender = false;
		}
	}

	//����������������������������������������� �� ���������������������������������������
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

	//��������������������������������� �� �� ������Ʈ ��������������������������������������
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

	//�������������������������������������� �Ĺ�  ��������������������������������������
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

	//����������������������������������������� ���� �������������������������������������� 
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

	//����������������������������������������� �ɸ��� �� ���� �������������������������������������� 
	for (int i = 0; i < CHARACTERX; i++)
	{
		SetRect(&_characterPalette[i].rc, WINSIZEX - IMAGEMANAGER->findImage("characterTilePalette")->getWidth() + (i * PALETTESIZE),
			0, WINSIZEX - IMAGEMANAGER->findImage("characterTilePalette")->getWidth() + (i * PALETTESIZE) + PALETTESIZE, PALETTESIZE);
		_characterPalette[i].frameX = i;
		_characterPalette[i].frameY = 0;
	}

	//����������������������������������������� templeObject  �������������������������������������� 
	for (int i = 0; i < PALETTEY; i++)
	{
		for (int j = 0;j < PALETTEX; j++)
		{
			SetRect(&_templeObjectPalette[i * PALETTEX + j].rc, WINSIZEX - IMAGEMANAGER->findImage("templeObjectPalette")->getWidth() + (j * PALETTESIZE),
				i * PALETTESIZE, WINSIZEX - IMAGEMANAGER->findImage("templeObjectPalette")->getWidth() + j * PALETTESIZE + PALETTESIZE, i * PALETTESIZE + PALETTESIZE);
			_templeObjectPalette[i * PALETTEX + j].frameX = j;
			_templeObjectPalette[i * PALETTEX + j].frameY = i;
		}
	}

	//����������������������������������������� Style��ư(90X20) ��������������������������������
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0;j < 3; ++j)
		{
			SetRect(&_style[i * 3 + j].rc, 920 + j * 95, 280 + (30 * i), 920 + j * 95 + 90, 310 + (30 * i));
			_style[i * 3 + j].isClick = false;
			_style[i * 3 + j].x = 0;
			_style[i * 3 + j].y = 0;
			_style[i * 3 + j].centerX = 0;
			_style[i * 3 + j].centerY = 0;
			_style[i * 3 + j].frameX = 0;
			_style[i * 3 + j].alpha = 0;
			_style[i * 3 + j].isClick = false;
			_style[i * 3 + j].isEffect = false;
		}
	}

	_style[0].isClick = true;

	//����������������������������������������� Type��ư ��������������������������
	for (int i = 0;i < 7;i++)
	{
		SetRect(&_type[i].rc, 920 + i * 40, 340, 920 + i * 40 + 40, 380);
		_type[i].isClick = false;
		_type[i].x = 0;
		_type[i].y = 0;
		_type[i].centerX = 0;
		_type[i].centerY = 0;
		_type[i].frameX = 0;
		_type[i].alpha = 0;
		_type[i].isClick = false;
		_type[i].isEffect = false;
	}

	//����������������������������������������� MiniMAP 
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SetRect(&_mapButton[i * 3 + j].rc, 920 + j * _mapButtonSize, 390 + i * _mapButtonSize, 920 + j * _mapButtonSize + _mapButtonSize, 390 + i * _mapButtonSize + _mapButtonSize);
			_mapButton[i * 3 + j].isClick = false;
		}
	}

	_mapButton[0].isClick = true;

	//����������������������������������������� MiniMAP 
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_miniMap[i * (TILEX)+j].rc, WINSIZEX - 140 + j * _miniMapSizeWidth, 390 + (i * _miniMapSizeHeight), WINSIZEX - 140 + (j * _miniMapSizeWidth) + _miniMapSizeWidth, 390 + (i * _miniMapSizeHeight) + _miniMapSizeHeight);
			_miniMap[i * (TILEX)+j].isClick = false;
		}
	}

	//����������������������������������������� SaveSlot
	for (int i = 0; i < SAVESLOT; i++)
	{
		SetRect(&_saveSlot[i].rc, 920, WINSIZEY - 180 + i * _saveSlotHeight, 920 + _saveSlotWidth, WINSIZEY - 180 + i * _saveSlotHeight + _saveSlotHeight);
		_saveSlot[i].isClick = false;
	}

	//����������������������������������������� SaveLoadExit
	SetRect(&_saveButton.rc, 920, 670, 1020, 710);     // 100 X 40
	SetRect(&_loadButton.rc, 1020, 670, 1120, 710);	   // 100 X 40
	SetRect(&_exitButton.rc, 1130, 670, 1190, 710);    // 60 X 40 
	_saveButton.isClick = false;
	_loadButton.isClick = false;
	_exitButton.isClick = false;
}

//�ȷ�Ʈ ����
void mapToolScene::MapToolCollision()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		//�̴ϸ� Ŭ��
		for (int i = 0;i < 3;i++)
		{
			for (int j = 0;j < 3;j++)
			{
				if (PtInRect(&_mapButton[i * 3 + j].rc, _ptMouse))
				{
					//�̴ϸʹ�ư ��ġ �ʱ�ȭ 
					for (int i = 0; i < 9; i++)
					{
						_mapButton[i].isClick = false;
					}
					_mapButton[i * 3 + j].isClick = true;

					//���� ī�޶� ��ġ ����
					CAMERAMANAGER->setMapToolCameraXY(900 * j, 720 * i);
					break;
				}
			}
		}

		//��Ÿ�� Ŭ�� 
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

		//Ÿ�� ��ư Ŭ��
		for (int i = 0; i < 7; i++)
		{
			if (PtInRect(&_type[i].rc, _ptMouse))
			{
				switch (i)
				{
				case 0:
					_currentTile.type = TYPE::TERRAIN;			// ����	
					break;
				case 1:
					_currentTile.type = TYPE::LAND;				// �� 
					break;
				case 2:
					_currentTile.type = TYPE::LANDOBJECT;       // �� �� ������Ʈ 
					break;
				case 3:
					_currentTile.type = TYPE::OBJECT;			// ������Ʈ 
					break;
				case 4:
					_currentTile.type = TYPE::TREE;				// ���� 
					break;
				case 5:
					_currentTile.type = TYPE::CHARACTER;		// �ɸ��� �� �ֳʹ� 
					break;
				case 6:
					_currentTile.type = TYPE::TEMPLEOBJECT;     // ���� ������Ʈ
					break;
				default:
					break;
				}
			}
		}

		MapToolUpdate(); // ������ ������ �� 
	}
}

void mapToolScene::MapToolUpdate()
{
	//����� ���� Ŭ���� �ȷ�Ʈ�� XY��
	//cout << "X :" << _currentTile.frameX << "Y : " << _currentTile.frameY << endl;

	//�ȷ�Ʈ Ŭ�� 
	if (_currentTile.type == TYPE::TERRAIN || _currentTile.type == TYPE::LAND || _currentTile.type == TYPE::TEMPLEOBJECT)
	{
		for (int i = 0; i < PALETTEY; ++i)
		{
			for (int j = 0;j < PALETTEX; ++j)
			{
				if (PtInRect(&_terrainPalette[i * PALETTEX + j].rc, _ptMouse))
				{
					// Ÿ���� ��Ÿ�� ����
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
				if (PtInRect(&_treePalette[i * TREETILEX + j].rc, _ptMouse))
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
			if (PtInRect(&_characterPalette[i].rc, _ptMouse))
			{
				_currentTile.frameX = i;
				_currentTile.frameY = 0;
				break;
			}
		}
	}


	//���� Ŭ���� �� 
	for (int i = 0;i < TILEY;i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (PtInRect(&_tiles[i * TILEX + j].rc, PointMake(CAMERAMANAGER->getMapToolCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getMapToolCamera().cameraY + _ptMouse.y)))
			{
				if (_ptMouse.x >= 900) return;		// ����ó��

				_tiles[i * TILEX + j].isClick = true; // �̴ϸ� Ȱ��ȭ 

				//cout << "��" << _tiles[i * TILEX + j].isClick << endl;
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
	//������ ��ư�� ������ Ÿ�� �ʱ�ȭ
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0;i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				if (PtInRect(&_tiles[i * TILEX + j].rc, PointMake(CAMERAMANAGER->getMapToolCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getMapToolCamera().cameraY + _ptMouse.y))) // PointMake(CAMERAMANAGER->getMapToolCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getMapToolCamera().cameraY + _ptMouse.y)))
				{
					_tiles[i * TILEX + j].type = TYPE::NONE;
					_tiles[i * TILEX + j].terrain = TERRAIN::NONE;
					_tiles[i * TILEX + j].land = LAND::NONE;
					_tiles[i * TILEX + j].landObject = LANDOBJECT::NONE;
					_tiles[i * TILEX + j].object = OBJECT::NONE;
					_tiles[i * TILEX + j].tree = TREE::NONE;
					_tiles[i * TILEX + j].character = CHARACTER::NONE;
					_tiles[i * TILEX + j].building = BUILDING::NONE;
					_tiles[i * TILEX + j].templeObject = TEMPLEOBJECT::NONE;
					_tiles[i * TILEX + j].terrainFrameX = 0;
					_tiles[i * TILEX + j].terrainFrameY = 0;
					_tiles[i * TILEX + j].landFrameX = 0;
					_tiles[i * TILEX + j].landFrameY = 0;
					_tiles[i * TILEX + j].landObjectFrameX = 0;
					_tiles[i * TILEX + j].landObjectFrameY = 0;
					_tiles[i * TILEX + j].objectFrameX = 0;
					_tiles[i * TILEX + j].objectFrameY = 0;
					_tiles[i * TILEX + j].treeFrameX = 0;
					_tiles[i * TILEX + j].treeFrameY = 0;
					_tiles[i * TILEX + j].characterFrameX = 0;
					_tiles[i * TILEX + j].characterFrameY = 0;
					_tiles[i * TILEX + j].templeObjectFrameX = 0;
					_tiles[i * TILEX + j].templeObjectFrameY = 0;
					_tiles[i * TILEX + j].isClick = false;
					_tiles[i * TILEX + j].isObject = false;
					_tiles[i * TILEX + j].isRender = false;
					//������
					//cout << "Ÿ��:" << (int)_tiles[i * TILEX + j].type << endl;
					//cout << "����:" << (int)_tiles[i * TILEX + j].terrain << endl;
					break;
				}
			}
		}
	}
}

void mapToolScene::MapToolRender()
{
	PatBlt(CAMERAMANAGER->getMapToolDC(), CAMERAMANAGER->getMapToolCamera().cameraX, CAMERAMANAGER->getMapToolCamera().cameraY, CAMERAMANAGER->getMapToolCamera().cameraSizeX, CAMERAMANAGER->getMapToolCamera().cameraSizeY, BLACKNESS);

	//������������������������������������������ẻ MAP  ���������������������������������������
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//��� ��Ʈ �׸��� 
		IMAGEMANAGER->findImage("rect2")->render(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top);

		//�ε��� ������

		//Ŭ���� ����RECT�� �浹���� ������ ��������
		RECT temp;
		if (!IntersectRect(&temp, &CAMERAMANAGER->getMapToolRect(), &_tiles[i].rc)) continue;

		//Ÿ���� NONE�̸� ��������
		if (_tiles[i].type == TYPE::NONE) continue;

		//������������������������������������������ LAND ���������������������������������������
		if (_tiles[i].land != LAND::NONE)
		{
			if (_tiles[i].land == LAND::GRASS || _tiles[i].land == LAND::DESERT || _tiles[i].land == LAND::SNOW)
			{
				IMAGEMANAGER->findImage("grassTileLand")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landFrameX, _tiles[i].landFrameY);
			}
			else if (_tiles[i].land == LAND::GRAVE || _tiles[i].land == LAND::VOLCANO || _tiles[i].land == LAND::WATER)
			{
				IMAGEMANAGER->findImage("graveTileLand")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landFrameX, _tiles[i].landFrameY);
			}
			//Rectangle(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc);
		}

		//������������������������������������������TERRAIN  ���������������������������������������
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

			//������
			if (KEYMANAGER->isToggleKey(VK_F3))
			{
				//�浹��Ʈ 
				if (_tiles[i].land == LAND::WATER)
				{
					IMAGEMANAGER->findImage("graveTileLand")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].landFrameX, _tiles[i].landFrameY);
				}
				//�ε��� ������
				char str[100];
				sprintf_s(str, "%d", i);
				TextOut(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
			}
		}

		//������������������������������������������ LAND OBJECT ���������������������������������������
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

		//������������������������������������������ OBJECT  ���������������������������������������
		if (_tiles[i].object != OBJECT::NONE)
		{
			IMAGEMANAGER->findImage("objectTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objectFrameX, _tiles[i].objectFrameY);
		}

		if (_tiles[i].templeObject != TEMPLEOBJECT::NONE)
		{
			IMAGEMANAGER->findImage("templeObject")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].templeObjectFrameX, _tiles[i].templeObjectFrameY);
		}

		if (_tiles[i].character != CHARACTER::NONE)
		{
			IMAGEMANAGER->findImage("characterTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].characterFrameX, _tiles[i].characterFrameY);
		}
	}


	//������ ��Ʈ ������ �ΰ��� ���� �׷���� �Ѵ�.
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//������������������������������������������ TREE ���������������������������������������
		if (_tiles[i].type == TYPE::NONE) continue;

		if (_tiles[i].tree != TREE::NONE)
		{
			IMAGEMANAGER->findImage("treeTile")->frameRender(CAMERAMANAGER->getMapToolDC(), _tiles[i].rc.left, _tiles[i].rc.top - 60, _tiles[i].treeFrameX, _tiles[i].treeFrameY);
		}
	}

	//�׸���
	CAMERAMANAGER->getMapToolImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getMapToolCamera().cameraX, CAMERAMANAGER->getMapToolCamera().cameraY, CAMERAMANAGER->getMapToolCamera().cameraSizeX, CAMERAMANAGER->getMapToolCamera().cameraSizeY);

	//�������������������������������������������� �ȷ�Ʈ ���������������������������������������
	//�ȷ�Ʈ ���� ������ ����
	int palletteWidth = IMAGEMANAGER->findImage("grassTilePalette")->getWidth();
	int palletteObjectWidth = IMAGEMANAGER->findImage("grassTileObjectPalette")->getWidth();
	
	//��ư�� ���� ������ Ÿ�� �׸���
	if (_style[0].isClick) // grass
	{
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

	// ����� �� ������ ���� 
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

	//������ ��ư�� �ִ� �� 9
	for (int i = 0; i < 9; i++)
	{
		//��Ÿ�� 
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
			//Rectangle(getMemDC(), _style[i].rc); //  �ӽ÷�Ʈ 
		}
		//���̺� ���� 
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
		// ��ġ Ÿ�� 
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

	// �̴ϸ� 
	IMAGEMANAGER->findImage("minimapBackground")->render(getMemDC(), _miniMap[0].rc.left, _miniMap[0].rc.top);
	for (int i = 0;i < TILEX * TILEY; i++)
	{
		//Rectangle(getMemDC(), _miniMap[i].rc);
		if (_tiles[i].isClick) IMAGEMANAGER->findImage("minimap")->render(getMemDC(), _miniMap[i].rc.left, _miniMap[i].rc.top);
	}

	//���̺�ε峪����
	IMAGEMANAGER->findImage("saveLoad")->frameRender(getMemDC(), _saveButton.rc.left, _saveButton.rc.top, 0, 0);
	IMAGEMANAGER->findImage("saveLoad")->frameRender(getMemDC(), _loadButton.rc.left, _loadButton.rc.top, 0, 1);
	IMAGEMANAGER->findImage("exit")->render(getMemDC(), _exitButton.rc.left, _exitButton.rc.top);
	//Rectangle(getMemDC(), _saveButton.rc);
	//Rectangle(getMemDC(), _loadButton.rc);
	//Rectangle(getMemDC(), _exitButton.rc);
}

TERRAIN mapToolScene::MapToolTerrainSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return TERRAIN::NONE;
	if (frameX == 6 && frameY == 6) return TERRAIN::NONE;
	//��Ÿ�Ͽ� ���� ���� Ÿ���� ��ȯ
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

	//��Ÿ�� ��ư�� ���� ���� Ÿ���� ��ȯ
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

	for (int i = 1; i < 5; i++)	// 1,2,3,4
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

	for (int i = 3; i < 7;i++)  // Y��
	{
		if (frameX == 0 && frameY == i) return TEMPLEOBJECT::TEMPLE_CANNON;
		if (frameX == 1 && frameY == i) return TEMPLEOBJECT::TEMPLE_DOOR;
		if (frameX == 2 && frameY == i) return TEMPLEOBJECT::TEMPLE_DOOR_BLUE;
		if (frameX == 3 && frameY == i) return TEMPLEOBJECT::TEMPLE_DOOR_GREEN;
		if (frameX == 4 && frameY == i) return TEMPLEOBJECT::TEMPLE_DOOR_RED;
	}

	return TEMPLEOBJECT::NONE;
}
