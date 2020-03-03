#include "stdafx.h"
#include "crops.h"

crops::crops()
{
}

crops::~crops()
{
}

//enum class OBJECT
//{
//	ROCK, COAL, IRON, GOLD, VOLCANIC_COAL, VOLCANIC_IRON, VOLCANIC_GOLD,  		// 잔디형식 
//	COTTON, BEET, WHEAT, BUSH, FLOWER_1, FLOWER_2, FLOWER_3,
//	HOT_PEPPER, PUMPKIN, LAVENDER, CINDERBLOOM, NIGHTSHADE,
//	NONE,
//};

// ■■■■■■■■■■■■■■■■■■■■■■■ OBJECT ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
HRESULT crops::init(OBJECT object, const char* imageName, int idx, int idy)
{
	_crops.object = object;					// 속성 
	_crops.imageName = imageName;			// 이미지 이름
	_crops.tree = TREE::NONE;
	_crops.building = BUILDING::NONE;

	_crops.idx = idx;
	_crops.idy = idy;
	_crops.x = idx * 60 + 30 - IMAGEMANAGER->findImage(_crops.imageName)->getWidth() / 2;
	_crops.y = idy * 60 + 30 - IMAGEMANAGER->findImage(_crops.imageName)->getHeight() / 2;
	_crops.centerX = idx * 60 + 30;
	_crops.centerY = idy * 60 + 30;
	
	_crops.hp = 1;
	_crops.maxHp = 1;
	_crops.hitTime = 0;
	_crops.hitCount = 0;
	_crops.frameX = _crops.frameY = 0;
	_crops.exp = 0;
	_crops.alpha = 0;
	_crops.hpBar = 0;

	_crops.isClick = false;
	_crops.isEffect = false;
	_crops.isHit = false;
	_crops.rc = RectMake(_crops.x, _crops.y, IMAGEMANAGER->findImage(_crops.imageName)->getWidth(), IMAGEMANAGER->findImage(_crops.imageName)->getHeight());
	return S_OK;
}
// ■■■■■■■■■■■■■■■■■■■■■■■ TREE ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
HRESULT crops::init(TREE tree, const char* imageName, int idx, int idy)
{
	_crops.tree = tree;
	_crops.object = OBJECT::NONE;
	_crops.building = BUILDING::NONE;		
	_crops.imageName = imageName;			//이미지 이름

	_crops.idx = idx;
	_crops.idy = idy;
	_crops.x = idx * 60 + 30 - IMAGEMANAGER->findImage(_crops.imageName)->getWidth() / 2;
	_crops.y = idy * 60 + 30 - IMAGEMANAGER->findImage(_crops.imageName)->getHeight() / 2;
	_crops.centerX = idx * 60 + 30;
	_crops.centerY = idy * 60 + 30;

	_crops.hp = 0;
	_crops.maxHp = 0;
	_crops.hitTime = 0;
	_crops.hitCount = 0;
	_crops.hpBar = 0;
	_crops.frameX = _crops.frameY = 0;
	_crops.exp = 0;
	_crops.alpha = 0;

	_crops.isClick = false;
	_crops.isEffect = false;
	_crops.isHit = false;
	_crops.rc = RectMake(_crops.x, _crops.y, IMAGEMANAGER->findImage(_crops.imageName)->getWidth(), IMAGEMANAGER->findImage(_crops.imageName)->getHeight());

	return S_OK;
}

void crops::release()
{
}

void crops::update()
{
}

void crops::render()
{
}

//체력 설정
void crops::setHp(int maxHp, int hp)
{
	_crops.maxHp = maxHp;
	_crops.hp = hp;
	//cout << _crops.maxHp << _crops.hp << endl;
}

//■■■■■■■■■■■■■■■■■■■■■■ imageCrops ■■■■■■■■■■■■■■■■■■■■■■

imageCrops::imageCrops()
{
}

imageCrops::~imageCrops()
{
}

void imageCrops::update()
{
	_crops.rc = RectMake(_crops.x, _crops.y, IMAGEMANAGER->findImage(_crops.imageName)->getWidth(), IMAGEMANAGER->findImage(_crops.imageName)->getHeight());
}

void imageCrops::render()
{
	if (_crops.isHit)
	{
		IMAGEMANAGER->findImage(_crops.imageName)->alphaRender(CAMERAMANAGER->getWorldDC(), _crops.x, _crops.y, _crops.alpha);
	}
	else
	{
		IMAGEMANAGER->findImage(_crops.imageName)->render(CAMERAMANAGER->getWorldDC(), _crops.x, _crops.y);
	}
	// 체력이 달면 게이지를 출력한다.
	if (_crops.maxHp > _crops.hp)
	{
		_crops.hpBar = ((float)_crops.hp / (float)_crops.maxHp) * 41;
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 22, _crops.centerY + 30, 0, 0, 45, 12);
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 20, _crops.centerY + 32, 0, 72, _crops.hpBar, 8);
	}
	//Rectangle(CAMERAMANAGER->getWorldDC(), _crops.rc);
}

//■■■■■■■■■■■■■■■■■■■■■■ frameCrops ■■■■■■■■■■■■■■■■■■■■■■

void frameCrops::update()
{
	//최대 프레임이면 리턴
	if (_crops.frameX == IMAGEMANAGER->findImage(_crops.imageName)->getMaxFrameX()) return;
	//시간이 지나면 프레임을 돌린다.
	if (_crops.time + _crops.speed <= TIMEMANAGER->getWorldTime())
	{
		_crops.frameX++;
		_crops.speed += _crops.speed;
		if (_crops.frameX >= IMAGEMANAGER->findImage(_crops.imageName)->getMaxFrameX())
		{
			_crops.frameX = IMAGEMANAGER->findImage(_crops.imageName)->getMaxFrameX();
			_crops.isClick = true;
		}
	}
	_crops.rc = RectMake(_crops.centerX - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth() / 2), _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() / 2), IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight());
}

void frameCrops::render()
{
	if (_crops.isHit)
	{
		IMAGEMANAGER->findImage(_crops.imageName)->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _crops.centerX - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth() / 2), _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() / 2), _crops.frameX, _crops.frameY, _crops.alpha);
	}
	else
	{
		IMAGEMANAGER->findImage(_crops.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _crops.centerX - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth() / 2), _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() / 2), _crops.frameX, _crops.frameY);
	}
	//체력이 달면 게이지를 출력한다.
	if (_crops.maxHp > _crops.hp)
	{
		_crops.hpBar = ((float)_crops.hp / (float)_crops.maxHp) * 41;
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 22, _crops.centerY + 30, 0, 0, 45, 12);
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 20, _crops.centerY + 32, 0, 72, _crops.hpBar, 8);
	}
	//Rectangle(CAMERAMANAGER->getWorldDC(), _crops.rc);
}

//■■■■■■■■■■■■■■■■■■■■■■ imageFrameCrops ■■■■■■■■■■■■■■■■■■■■■■

void imageFrameCrops::update()
{
	_crops.rc = RectMake(_crops.centerX - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth() / 2), _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() / 2), IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight());
}

void imageFrameCrops::render()
{
	if (_crops.isHit)
	{
		IMAGEMANAGER->findImage(_crops.imageName)->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _crops.centerX - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth() / 2), _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() / 2), _crops.frameX, _crops.frameY, _crops.alpha);
	}
	else
	{
		IMAGEMANAGER->findImage(_crops.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _crops.centerX - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth() / 2), _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() / 2), _crops.frameX, _crops.frameY);
		//Rectangle(CAMERAMANAGER->getWorldDC(), _crops.rc);
	}
	//체력이 달면 출력한다.
	if (_crops.maxHp > _crops.hp)
	{
		_crops.hpBar = ((float)_crops.hp / (float)_crops.maxHp) * 41;
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 22, _crops.centerY + 30, 0, 0, 45, 12);
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 20, _crops.centerY + 32, 0, 72, _crops.hpBar, 8);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■ treeCrops ■■■■■■■■■■■■■■■■■■■■■■


void treeCrops::update()
{
	_crops.rc = RectMake(_crops.centerX - 15, _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() * 4) / 5, 30, IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight());
}

void treeCrops::render()
{
	if (_crops.isHit)
	{
		IMAGEMANAGER->findImage(_crops.imageName)->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _crops.centerX - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth() / 2), _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() * 4) / 5, _crops.frameX, _crops.frameY, _crops.alpha);
	}
	else
	{
		IMAGEMANAGER->findImage(_crops.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _crops.centerX - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth() / 2), _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() * 4) / 5, _crops.frameX, _crops.frameY);
		//Rectangle(CAMERAMANAGER->getWorldDC(), _crops.rc);
	}
	//체력이 달면 게이지를 출력한다.
	if (_crops.maxHp > _crops.hp)
	{
		_crops.hpBar = ((float)_crops.hp / (float)_crops.maxHp) * 41;
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 22, _crops.centerY + 30, 0, 0, 45, 12);
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 20, _crops.centerY + 32, 0, 72, _crops.hpBar, 8);
	}
}


// ■■■■■■■■■■■■■■■■■■■■■■■ BUSH and FLOWER ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void multiImageCrops::update()
{
	if (_crops.isClick) return;

	if (_crops.time + _crops.speed <= TIMEMANAGER->getWorldTime())
	{
		_crops.frameX++;
		_crops.speed += _crops.speed;
		if (_crops.frameX == 2)
		{
			_crops.frameX = RND->getFromIntTo(2, 4);
			_crops.isClick = true;
		}
	}

	_crops.rc = RectMake(_crops.centerX - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth() / 2), _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() / 2), IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight());
}

void multiImageCrops::render()
{
	if (_crops.isHit)
	{
		IMAGEMANAGER->findImage(_crops.imageName)->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _crops.centerX - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth() / 2), _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() / 2), _crops.frameX, _crops.frameY, _crops.alpha);
	}
	else
	{
		IMAGEMANAGER->findImage(_crops.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _crops.centerX - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameWidth() / 2), _crops.centerY - (IMAGEMANAGER->findImage(_crops.imageName)->getFrameHeight() / 2), _crops.frameX, _crops.frameY);
	}
	//체력이 달면 게이지 출력(없어도 됌)
	if (_crops.maxHp > _crops.hp)
	{
		_crops.hpBar = ((float)_crops.hp / (float)_crops.maxHp) * 41;
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 22, _crops.centerY + 30, 0, 0, 45, 12);
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 20, _crops.centerY + 32, 0, 72, _crops.hpBar, 8);
	}
}
