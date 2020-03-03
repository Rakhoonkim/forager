#include "land.h"
#include "stdafx.h"

land::land()
{
}

land::~land()
{
}

HRESULT land::init()
{
	_isLand = false;

	_landImage = new image;
	_landImage->init(1800, 1440);
	_landDC = _landImage->getMemDC();

	_landX = _nextX = 900 - WINSIZEX / 2;
	_landY = _nextY = 720 - WINSIZEY / 2;

	_cameraSpeed = 10;

	MapLoad("inGameNumber1.map");		// 맵을 가져와서 
	landSetting();						// 세팅을 다시한다

	//this->mapBuy(0, 0);
	//this->mapBuy(0, 1);
	//this->mapBuy(0, 2);
	//this->mapBuy(1, 0);
	this->mapBuy(1, 1);
	//this->mapBuy(1, 2);
	//this->mapBuy(2, 0);
	//this->mapBuy(2, 1);
	//this->mapBuy(2, 2);

	_direction = 4;
	_playerCoin = 0;

	_cameraRect = RectMake(_landX, _landY, WINSIZEX, WINSIZEY);

	KEYANIMANAGER->findAnimation("landCursor")->start();
	return S_OK;
}

void land::release()
{
}

void land::update()
{
	mapMove(); //  수정예정

	// 카메라 렉트 갱신 
	_cameraRect = RectMake(_landX, _landY, WINSIZEX, WINSIZEY);
}

void land::MapLoad(const char* fileName)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(fileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//맵을 불로온 직후 타일의 속성을 매겨준다
	ReadFile(file, _landTiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	
	CloseHandle(file);
}

void land::render(HDC hdc)
{
	//PatBlt(_landImage->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	IMAGEMANAGER->findImage("background")->render(_landImage->getMemDC(), _landX, _landY);

	//맵 렌더 
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_landTiles[i].type == TYPE::NONE) continue;
		if (!_landTiles[i].isRender) continue;
		RECT temp;
		if (!IntersectRect(&temp, &_cameraRect, &_landTiles[i].rc)) continue;

		if (_landTiles[i].land != LAND::NONE)
		{
			if (_landTiles[i].land == LAND::GRASS || _landTiles[i].land == LAND::DESERT || _landTiles[i].land == LAND::SNOW)
			{
				IMAGEMANAGER->findImage("grassTileLandPalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].landFrameX, _landTiles[i].landFrameY);
			}
			else if (_landTiles[i].land == LAND::GRAVE || _landTiles[i].land == LAND::VOLCANO)
			{
				IMAGEMANAGER->findImage("graveTileLandPalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].landFrameX, _landTiles[i].landFrameY);
			}
		}
		if (_landTiles[i].terrain != TERRAIN::NONE)
		{
			if (_landTiles[i].terrain == TERRAIN::GRASS)
			{
				IMAGEMANAGER->findImage("grassTilePalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].terrainFrameX, _landTiles[i].terrainFrameY);
			}
			else if (_landTiles[i].terrain == TERRAIN::DESERT)
			{
				IMAGEMANAGER->findImage("desertTilePalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].terrainFrameX, _landTiles[i].terrainFrameY);
			}
			else if (_landTiles[i].terrain == TERRAIN::SNOW)
			{
				IMAGEMANAGER->findImage("snowTilePalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].terrainFrameX, _landTiles[i].terrainFrameY);
			}
			else if (_landTiles[i].terrain == TERRAIN::GRAVE)
			{
				IMAGEMANAGER->findImage("graveTilePalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].terrainFrameX, _landTiles[i].terrainFrameY);
			}
			else if (_landTiles[i].terrain == TERRAIN::VOLCANO)
			{
				IMAGEMANAGER->findImage("volcanoTilePalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].terrainFrameX, _landTiles[i].terrainFrameY);
			}
		}
		if (_landTiles[i].landObject != LANDOBJECT::NONE)
		{
			if (_landTiles[i].landObject == LANDOBJECT::GRASS)
			{
				IMAGEMANAGER->findImage("grassTileObjectPalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].landObjectFrameX, _landTiles[i].landObjectFrameY);
			}
			else if (_landTiles[i].landObject == LANDOBJECT::DESERT)
			{
				IMAGEMANAGER->findImage("desertTileObjectPalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].landObjectFrameX, _landTiles[i].landObjectFrameY);
			}
			else if (_landTiles[i].landObject == LANDOBJECT::SNOW)
			{
				IMAGEMANAGER->findImage("snowTileObjectPalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].landObjectFrameX, _landTiles[i].landObjectFrameY);
			}
			else if (_landTiles[i].landObject == LANDOBJECT::GRAVE)
			{
				IMAGEMANAGER->findImage("graveTilePalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].landObjectFrameX, _landTiles[i].landObjectFrameY);
			}
			else if (_landTiles[i].landObject == LANDOBJECT::VOLCANO)
			{
				IMAGEMANAGER->findImage("volcanoTilePalette")->frameRender(_landImage->getMemDC(), _landTiles[i].rc.left, _landTiles[i].rc.top, _landTiles[i].landObjectFrameX, _landTiles[i].landObjectFrameY);
			}
		}
		//Rectangle(_landImage->getMemDC(), _landTiles[i].rc);
	}

	for (int i = 0; i < MAXLAND;i++)
	{
		if (_land[i].isClick) continue;

		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 구매 가능한지 아닌지 
		if (_playerCoin >= _land[i].alpha)
		{
			//구매가능
			//IMAGEMANAGER->findImage("landBuy")->alphaFrameRender(_landImage->getMemDC(), _land[i].centerX - IMAGEMANAGER->findImage("landBuy")->getFrameWidth() / 2, _land[i].centerY - IMAGEMANAGER->findImage("landBuy")->getFrameHeight() / 2, 1, 0, 50);
			IMAGEMANAGER->findImage("landBuy")->frameRender(_landImage->getMemDC(), _land[i].centerX - IMAGEMANAGER->findImage("landBuy")->getFrameWidth() / 2, _land[i].centerY - IMAGEMANAGER->findImage("landBuy")->getFrameHeight() / 2, 1, 0);

		}
		else
		{
			//구매 불가능
			//IMAGEMANAGER->findImage("landBuy")->alphaFrameRender(_landImage->getMemDC(), _land[i].centerX - IMAGEMANAGER->findImage("landBuy")->getFrameWidth() / 2, _land[i].centerY - IMAGEMANAGER->findImage("landBuy")->getFrameHeight() /2, 0, 0, 50);
			IMAGEMANAGER->findImage("landBuy")->frameRender(_landImage->getMemDC(), _land[i].centerX - IMAGEMANAGER->findImage("landBuy")->getFrameWidth() / 2, _land[i].centerY - IMAGEMANAGER->findImage("landBuy")->getFrameHeight() / 2, 0, 0);

		}
		//Rectangle(_landImage->getMemDC(), _land[i].rc);

		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 가격 출력
		float imageX = _land[i].centerX + 80;
		float imageY = _land[i].centerY + 40;
		if (_land[i].alpha < 10)
		{
			IMAGEMANAGER->findImage("landNum")->frameRender(_landImage->getMemDC(), imageX, imageY, _land[i].alpha, 0);
		}
		else if (_land[i].alpha < 100)
		{
			IMAGEMANAGER->findImage("landNum")->frameRender(_landImage->getMemDC(), imageX, imageY, _land[i].alpha % 10, 0);
			IMAGEMANAGER->findImage("landNum")->frameRender(_landImage->getMemDC(), imageX - 30, imageY, (_land[i].alpha / 10) % 10, 0);
		}
		else if (_land[i].alpha < 1000)
		{
			IMAGEMANAGER->findImage("landNum")->frameRender(_landImage->getMemDC(), imageX, imageY, _land[i].alpha % 10, 0);
			IMAGEMANAGER->findImage("landNum")->frameRender(_landImage->getMemDC(), imageX - 30, imageY, (_land[i].alpha / 10) % 10, 0);
			IMAGEMANAGER->findImage("landNum")->frameRender(_landImage->getMemDC(), imageX - 60, imageY, _land[i].alpha / 100, 0);
		}


		// 포인터 출력 
		//Rectangle(_landImage->getMemDC(), _land[i].rc);
		IMAGEMANAGER->findImage("landCursor")->aniRender(_landImage->getMemDC(), _land[_direction].centerX - IMAGEMANAGER->findImage("landCursor")->getFrameWidth() / 2, _land[_direction].centerY - IMAGEMANAGER->findImage("landCursor")->getFrameHeight() / 2, KEYANIMANAGER->findAnimation("landCursor"));
	}

	//Rectangle(_landImage->getMemDC(), _land[6].rc);
	//이미지 출력 
	_landImage->render(hdc, 0, 0, _landX, _landY, WINSIZEX, WINSIZEY);

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 코인 출력
	// 코인수 출력하기 
	IMAGEMANAGER->findImage("invenItem")->frameRender(hdc, 20, WINSIZEY - 100, 0, 3);

	//코인의 갯수를 출력 	
	if (_playerCoin < 10)
	{
		IMAGEMANAGER->findImage("whiteNum")->frameRender(hdc, 40, WINSIZEY - 50, _playerCoin, 0);
	}
	else if (_playerCoin < 100)
	{
		IMAGEMANAGER->findImage("whiteNum")->frameRender(hdc, 50, WINSIZEY - 50, _playerCoin % 10, 0);
		IMAGEMANAGER->findImage("whiteNum")->frameRender(hdc, 30, WINSIZEY - 50, (_playerCoin / 10) % 10, 0);
	}
	else if (_playerCoin < 1000)
	{
		IMAGEMANAGER->findImage("whiteNum")->frameRender(hdc, 60, WINSIZEY - 50, _playerCoin % 10, 0);
		IMAGEMANAGER->findImage("whiteNum")->frameRender(hdc, 40, WINSIZEY - 50, (_playerCoin / 10) % 10, 0);
		IMAGEMANAGER->findImage("whiteNum")->frameRender(hdc, 20, WINSIZEY - 50, _playerCoin / 100, 0);
	}


}

void land::mapMove() // 카메라 셋팅 예정
{
	if (!_isLand) return;
	for (int i = 0; i < MAXLAND; i++)
	{
		if (PtInRect(&_land[i].rc, PointMake(_landX + _ptMouse.x, _landY + _ptMouse.y)))
		{
			_direction = i;

			//if (!_land[i].isClick) _land[i].isClick = true;
			break;
		}
	}

	// 구매 버튼식 
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < LANDY; i++)
		{
			for (int j = 0; j < LANDX; j++)
			{
				if (_land[i * 3 + j].isClick) continue;
				if (PtInRect(&_land[i * 3 + j].rc, PointMake(_landX + _ptMouse.x, _landY + _ptMouse.y)))
				{
					if (_playerCoin >= _land[i * 3 + j].alpha)
					{
						_playerCoin -= _land[i * 3 + j].alpha;				
						this->mapBuy(j, i);
						MAPMANAGER->setLandTile(j, i);
						UIMANAGER->getInven()->removeInven("coinDrop", _land[i * 3 + j].alpha);
						_land[i * 3 + j].isClick = true;
					}
					break;
				}
			}
		}
	}

	_nextX = _land[_direction].centerX - WINSIZEX / 2;
	_nextY = _land[_direction].centerY - WINSIZEY / 2;

	if (_landX < _nextX)
	{
		_landX += _cameraSpeed;
	}
	else if (_landX > _nextX)
	{
		_landX -= _cameraSpeed;
	}

	if (_landY < _nextY)
	{
		_landY += _cameraSpeed;
	}
	else if (_landY > _nextY)
	{
		_landY -= _cameraSpeed;
	}

	if (_landX < 0) _landX = 0;
	if (_landY < 0) _landY = 0;
	if (_landX + WINSIZEX > 1800) _landX = 1800 - WINSIZEX;
	if (_landY + WINSIZEY > 1440) _landY = 1440 - WINSIZEY;


	//cout << "x : " << _ptMouse.x << "y : " << _ptMouse.y << endl;
	//cout << "_landX : " << _landX << "_landY : " << _landY << endl;

	//_landY = _ptMouse.y - WINSIZEY / 2;


}

void land::mapBuy(int x, int y)
{
	int tilex = 15;
	int tiley = 12;

	int startX = x * 15;   // 0 , 15 , 30
	int startY = y * 12;   // 0 , 12 , 24 

	int endX = startX + tilex;
	int endY = startY + tiley;

	for (int i = startY;i < endY; i++)
	{
		for (int j = startX; j < endX; j++)
		{

			_landTiles[i * TILEX + j].isRender = true;
			//_vTiles.push_back(&_tiles[startY * TILEX + startX]);
		}
	}
}

void land::landSetting()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_landTiles[i * TILEX + j].rc, j * LANDTILESIZE, i * LANDTILESIZE,
				j * LANDTILESIZE + LANDTILESIZE, i * LANDTILESIZE + LANDTILESIZE);
			_landTiles[i * TILEX + j].idx = j;
			_landTiles[i * TILEX + j].idy = i;
			_landTiles[i * TILEX + j].isClick = false;
			_landTiles[i * TILEX + j].isObject = false;
			_landTiles[i * TILEX + j].isRender = false;
		}
	}

	for (int i = 0;i < LANDY; i++)
	{
		for (int j = 0;j < LANDX; j++)
		{
			_land[i * 3 + j].rc = RectMakeCenter(300 + j * 600, 240 + i * 480, 390, 330);
			//SetRect(&_land[i * 3 + j].rc, 0 + 600 * j, 0 + 480 * i, 0 + 600 * j + 600, 0 + 480 * i + 480);
			_land[i * 3 + j].isClick = false;
			_land[i * 3 + j].isEffect = false;
			_land[i * 3 + j].centerX = 300 + j * 600;  //(_land[i * 3 + j].rc.left + _land[i * 3 + j].rc.right) / 2;
			_land[i * 3 + j].centerY = 240 + i * 480;//(_land[i * 3 + j].rc.top + _land[i * 3 + j].rc.bottom) / 2;
		}
	}
	_land[4].isClick = true;

	//coin 가격을 alpha 값으로 대체 
	_land[0].alpha = 7;
	_land[1].alpha = 5;
	_land[2].alpha = 7;
	_land[3].alpha = 5;
	// 4는 기본 
	_land[5].alpha = 3;
	_land[6].alpha = 8;
	_land[7].alpha = 5;
	_land[8].alpha = 8;
}
