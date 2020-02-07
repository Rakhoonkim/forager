#include "stdafx.h"
#include "mapManager.h"

mapManager::mapManager()
{
}

mapManager::~mapManager()
{
}

HRESULT mapManager::init()
{
	MapImage();
	return S_OK;
}

void mapManager::release()
{
}

void mapManager::update()
{
}

void mapManager::render()
{
	for (_viTiles = _vTiles.begin(); _viTiles != _vTiles.end(); ++_viTiles)
	{
		// 예외처리 
		if((*_viTiles)->type == TYPE::NONE) continue;
		//LAND
		if ((*_viTiles)->land != LAND::NONE)
		{
			LandRender();
		}
		//TERRAIN
		if ((*_viTiles)->terrain != TERRAIN::NONE)
		{
			TerrainRender();
		}
		//TERRAIN OBJECT
		if ((*_viTiles)->landObject != LANDOBJECT::NONE)
		{
			LadnObjectRender();
		}
	}
}

void mapManager::MapImage()
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

	//background
	IMAGEMANAGER->addImage("background", "./image/background.bmp", 1200, 720, false, RGB(255, 0, 255));
}

void mapManager::MapLoad(const char* fileName)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(fileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//맵을 불로온 직후 타일의 속성을 매겨준다
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].type != TYPE::NONE)
		{
			_vTiles.push_back(&_tiles[i]);
		}
	}

	CloseHandle(file);
}

void mapManager::TerrainRender()
{
	if ((*_viTiles)->terrain == TERRAIN::GRASS)
	{
		IMAGEMANAGER->findImage("grassTile")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTiles)->rc.left, (*_viTiles)->rc.top, (*_viTiles)->terrainFrameX, (*_viTiles)->terrainFrameY);
	}
	else if ((*_viTiles)->terrain == TERRAIN::DESERT)
	{
		IMAGEMANAGER->findImage("desertTile")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTiles)->rc.left, (*_viTiles)->rc.top, (*_viTiles)->terrainFrameX, (*_viTiles)->terrainFrameY);
	}
	else if ((*_viTiles)->terrain == TERRAIN::SNOW)
	{
		IMAGEMANAGER->findImage("snowTile")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTiles)->rc.left, (*_viTiles)->rc.top, (*_viTiles)->terrainFrameX, (*_viTiles)->terrainFrameY);
	}
}

void mapManager::LandRender()
{
	IMAGEMANAGER->findImage("grassTileLand")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTiles)->rc.left, (*_viTiles)->rc.top, (*_viTiles)->landFrameX, (*_viTiles)->landFrameY);
}

void mapManager::LadnObjectRender()
{
	if ((*_viTiles)->landObject == LANDOBJECT::GRASS)
	{
		IMAGEMANAGER->findImage("grassTileObject")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTiles)->rc.left, (*_viTiles)->rc.top, (*_viTiles)->landObjectFrameX, (*_viTiles)->landObjectFrameY);
	}
	else if ((*_viTiles)->landObject == LANDOBJECT::DESERT)
	{
		IMAGEMANAGER->findImage("desertTileObject")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTiles)->rc.left, (*_viTiles)->rc.top, (*_viTiles)->landObjectFrameX, (*_viTiles)->landObjectFrameY);
	}
	else if ((*_viTiles)->landObject == LANDOBJECT::SNOW)
	{
		IMAGEMANAGER->findImage("snowTileObject")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTiles)->rc.left, (*_viTiles)->rc.top, (*_viTiles)->landObjectFrameX, (*_viTiles)->landObjectFrameY);
	}
}

void mapManager::ObejectRender()
{
}

void mapManager::setPlayerAddress()
{
}
