#include "stdafx.h"
#include "build.h"
#include "buildManager.h"

build::build()
{
}

build::~build()
{
}

HRESULT build::init()
{
	_listHeight = IMAGEMANAGER->findImage("bigLongBox")->getFrameHeight();
	_listWidth = IMAGEMANAGER->findImage("bigLongBox")->getFrameWidth();
	_isBuilding = false;		// 건물 설치중인지 아닌지 판단 
	_buildingDirection = 0;  // 지을 건물을 가리키고 있는 버튼 
	_farmingDirection = 0;
	//4가지 리스트 초기화 
	for (int i = 0; i < MAXLIST; i++)
	{
		_buildList[i].rc = RectMake(WINSIZEX - 250, 25 + (_listHeight + 10) * i, _listWidth, _listHeight);
		_buildList[i].isClick = false;
		_buildList[i].isEffect = false;
	}
	//산업 리스트 초기화   == 0번 
	for (int i = 0; i < MAXINDUSTRY; i++)
	{
		_industryList[i].rc = RectMake(WINSIZEX - 200, 10 + _buildList[0].rc.bottom + (IMAGEMANAGER->findImage("industry")->getFrameHeight() + 5) * i, 156, IMAGEMANAGER->findImage("industry")->getFrameHeight());
		_industryList[i].isClick = false;
		_industryList[i].isEffect = false;
	}
	//농업 리스트 초기화   == 1번
	for (int i = 0; i < MAXFARMING; i++)
	{
		_farmingList[i].rc = RectMake(WINSIZEX - 200, 10 + _buildList[1].rc.bottom + (IMAGEMANAGER->findImage("farming")->getFrameHeight() + 5) * i, 156, IMAGEMANAGER->findImage("farming")->getFrameHeight());
		_farmingList[i].isClick = false;
		_farmingList[i].isEffect = false;
	}

	_direction = 0;

	_buildManager = new buildManager;
	_buildManager->init();

	
	return S_OK;
}

void build::release()
{
}

void build::update()
{
	if(!_isBuilding) buttonClick();
	//industryCheck();
	//farmingCheck();
	buildingCheck();
	isClickBuild();
	cout << MAPMANAGER->getBuildTiles(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y) << endl;
}

void build::render()
{
}

void build::render(HDC hdc)
{

	for (int i = 0; i < 4; i++)
	{
		IMAGEMANAGER->findImage("bigLongBox")->frameRender(hdc, _buildList[i].rc.left, _buildList[i].rc.top, 0, i);
		//Rectangle(hdc, _buildList[i].rc);

		//char str[100];
		//sprintf_s(str, "참값 : %d", _buildList[i].isClick);
		//TextOut(hdc, _buildList[i].rc.left, _buildList[i].rc.top, str, strlen(str));
	}

	for (int i = 0; i < 3; i++)
	{
		if (!_buildList[0].isClick) break;
		IMAGEMANAGER->findImage("industry")->frameRender(hdc, _industryList[i].rc.left, _industryList[i].rc.top, 0, i);
		//Rectangle(hdc, _industryList[i].rc);

		if (_industryList[i].isClick)
		{
			if (!MAPMANAGER->getBuildTiles(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y))
			{
				//빨간색 이미지로 바꿀 예정 
				IMAGEMANAGER->findImage("building")->alphaFrameRender(hdc, _ptMouse.x - IMAGEMANAGER->findImage("building")->getFrameWidth() / 2, _ptMouse.y - IMAGEMANAGER->findImage("building")->getFrameHeight() / 2, i, 0, _industryList[i].alpha);
			}
			else
			{
				IMAGEMANAGER->findImage("building")->frameRender(hdc, _ptMouse.x - IMAGEMANAGER->findImage("building")->getFrameWidth() / 2, _ptMouse.y - IMAGEMANAGER->findImage("building")->getFrameHeight() / 2, i, 0);
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (!_buildList[1].isClick) break;
		IMAGEMANAGER->findImage("farming")->frameRender(hdc, _farmingList[i].rc.left, _farmingList[i].rc.top, 0, i);
		//Rectangle(hdc, _farmingList[i].rc);

		if (_farmingList[i].isClick)
		{
			if (!MAPMANAGER->getBuildTilesFarming(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y))
			{
				//빨간색 이미지로 바꿀 예정 
				IMAGEMANAGER->findImage("farmingImage")->alphaFrameRender(hdc, _ptMouse.x - IMAGEMANAGER->findImage("farmingImage")->getFrameWidth() / 2, _ptMouse.y - IMAGEMANAGER->findImage("farmingImage")->getFrameHeight() / 2, i, 0, _farmingList[i].alpha);
			}
			else
			{
				IMAGEMANAGER->findImage("farmingImage")->frameRender(hdc, _ptMouse.x - IMAGEMANAGER->findImage("farmingImage")->getFrameWidth() / 2, _ptMouse.y - IMAGEMANAGER->findImage("farmingImage")->getFrameHeight() / 2, i, 0);
			}
		}
	}


}

void build::buttonClick()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 2; i++)
		{
			//리스트 적용하기 
			if (PtInRect(&_buildList[i].rc, _ptMouse))
			{
				_isBuilding = false;
				_direction = i;


				if (!_buildList[_direction].isClick)
				{
					_buildList[_direction].isClick = true;
				}
				else _buildList[_direction].isClick = false;

				for (int i = 0; i < MAXLIST; i++)
				{
					if (_buildList[i].isClick && _direction != i) _buildList[i].isClick = false;
				}

				//서로 빌딩 초기화 
				_industryList[_buildingDirection].isClick = false;
				_farmingList[_farmingDirection].isClick = false;

				break;
			}
		}

		//산업 리스트 
		for (int i = 0; i < MAXINDUSTRY; i++)
		{
			if (_direction != 0) break;
			if (PtInRect(&_industryList[i].rc, _ptMouse))
			{
				_buildingDirection = i;

				_industryList[_buildingDirection].isClick = true;
				_industryList[_buildingDirection].alpha = 100;
				_isBuilding = true;

				for (int i = 0; i < MAXINDUSTRY; i++)
				{
					if (i == _buildingDirection) continue;
					_industryList[i].isClick = false;
				}
			}
		}

		//농경 리스트 
		for (int i = 0; i < MAXFARMING; i++)
		{
			if (_direction != 1) break;
			if (PtInRect(&_farmingList[i].rc, _ptMouse))
			{
				_farmingDirection = i;

				_farmingList[_farmingDirection].isClick = true;
				_farmingList[_farmingDirection].alpha = 100;
				_isBuilding = true;

				for (int i = 0; i < MAXFARMING; i++)
				{
					if (i == _farmingDirection) continue;
					_farmingList[i].isClick = false;
				}
			}
		}
		/*	for (int i = 0; i < MAXLIST; i++)
			{
				_buildList[i].isClick = false;
			}*/



			/*	for (int i = 0; i < MAXLIST; i++)
				{
					if (_direction == i)
					{
						_buildList[i].isClick = true;
					}
					else _buildList[i].isClick = false;
				}*/

		listOpen();
		//KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}
}

void build::listOpen()
{
	for (int i = 0; i < MAXLIST; i++)
	{
		_buildList[i].rc = RectMake(WINSIZEX - 250, 25 + (_listHeight + 10) * i, _listWidth, _listHeight);
	}

	if (_buildList[0].isClick)
	{
		for (int i = 0; i < MAXLIST; i++)
		{
			if (i == 0) continue;
			_buildList[i].rc = RectMake(WINSIZEX - 250, 20 + _industryList[2].rc.bottom + (_listHeight + 10) * (i - 1), _listWidth, _listHeight);
		}
	}
	else if (_buildList[1].isClick)
	{
		for (int i = 0; i < MAXLIST; i++)
		{
			if (i == 0) continue;
			if (i == 1) continue;
			_buildList[i].rc = RectMake(WINSIZEX - 250, 20 + _farmingList[1].rc.bottom + (_listHeight + 10) * (i - 2), _listWidth, _listHeight);
		}
	}
}

void build::industryCheck()
{
	if (!(_buildList[0].isClick)) return;
	for (int i = 0; i < MAXINDUSTRY; i++)
	{
		if (_industryList[i].isClick)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
			{
				_isBuilding = false;
				_industryList[i].isClick = false;
				break;
			}
		}
	}
}

void build::farmingCheck()
{
	if (!(_buildList[1].isClick)) return;
	for (int i = 0; i < MAXFARMING;i++)
	{
		if (_farmingList[i].isClick)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
			{
				_isBuilding = false;
				_farmingList[i].isClick = false;
				break;
			}
		}
	}
}

void build::buildingCheck()
{
	if (!_isBuilding) return;

	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		this->setClickInit();
	}

}

void build::setClickInit()
{
	_isBuilding = false;

	for (int i = 0; i < MAXINDUSTRY; i++)
	{
		_industryList[i].isClick = false;
		if (i == 2) break;
		_farmingList[i].isClick = false;
	}
}

void build::isClickBuild() // 4개 범위랑랑 1개 범위를 구별할 것  
{
	if (!_isBuilding) return;
	if (_industryList[0].isClick)
	{
		if (!MAPMANAGER->getBuildTiles(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y)) return;

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_buildManager->createImageBuilding(BUILDING::FURNACE, CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y);
			MAPMANAGER->setBuildTiles(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y);
		}
	}
	else if (_industryList[1].isClick)
	{
		if (!MAPMANAGER->getBuildTiles(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y)) return;

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_buildManager->createImageBuilding(BUILDING::FORGE, CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y);
			MAPMANAGER->setBuildTiles(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y);
		}
	}
	else if (_industryList[2].isClick)
	{
		if (!MAPMANAGER->getBuildTiles(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y)) return;

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_buildManager->createImageBuilding(BUILDING::SEWING_STATION, CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y);
			MAPMANAGER->setBuildTiles(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y);
		}

	}
	else if (_farmingList[0].isClick)
	{
		if (!MAPMANAGER->getBuildTilesFarming(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y)) return;

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_buildManager->createImageBuilding(BUILDING::BRIDGE, CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y);
			MAPMANAGER->setBuildTilesFarming(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y);
		}
	}
	else if (_farmingList[1].isClick)
	{
		if (!MAPMANAGER->getBuildTilesFarming(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y)) return;

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_buildManager->createImageBuilding(BUILDING::FISHTRAP, CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y);
			MAPMANAGER->setBuildTilesFarming(CURSORMANAGER->getCursor()->getCursorIdXY().x, CURSORMANAGER->getCursor()->getCursorIdXY().y);
		}
	}
}
