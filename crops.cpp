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
//	ROCK, COAL, IRON, GOLD, VOLCANIC_COAL, VOLCANIC_IRON, VOLCANIC_GOLD,  		// ÀÜµðÇü½Ä 
//	COTTON, BEET, WHEAT, BUSH, FLOWER_1, FLOWER_2, FLOWER_3,
//	HOT_PEPPER, PUMPKIN, LAVENDER, CINDERBLOOM, NIGHTSHADE,
//	NONE,
//};

// ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á OBJECT ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á
HRESULT crops::init(OBJECT object, const char* imageName, int idx, int idy)
{
	_crops.object = object;
	_crops.tree = TREE::NONE;
	_crops.building = BUILDING::NONE;
	_crops.imageName = imageName;
	_crops.idx = idx;
	_crops.idy = idy;
	_crops.x = idx * 60 + 30 - IMAGEMANAGER->findImage(_crops.imageName)->getWidth() / 2;
	_crops.y = idy * 60 + 30 - IMAGEMANAGER->findImage(_crops.imageName)->getHeight() / 2;
	_crops.centerX = idx * 60 + 30;
	_crops.centerY = idy * 60 + 30;
	_crops.hp = 1;
	_crops.maxHp = 1;
	_crops.isClick = false;
	_crops.isEffect = false;
	_crops.isHit = false;
	_crops.hitTime = 0;
	_crops.hitCount = 0;
	_crops.frameX = _crops.frameY = 0;
	_crops.exp = 0;
	_crops.alpha = 0;

	_crops.hpBar = 0;
	_crops.rc = RectMake(_crops.x, _crops.y, IMAGEMANAGER->findImage(_crops.imageName)->getWidth(), IMAGEMANAGER->findImage(_crops.imageName)->getHeight());
	return S_OK;
}
// ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á TREE ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á
HRESULT crops::init(TREE tree, const char* imageName, int idx, int idy)
{
	_crops.tree = tree;
	_crops.object = OBJECT::NONE;
	_crops.building = BUILDING::NONE;
	_crops.imageName = imageName;
	_crops.idx = idx;
	_crops.idy = idy;
	_crops.x = idx * 60 + 30 - IMAGEMANAGER->findImage(_crops.imageName)->getWidth() / 2;
	_crops.y = idy * 60 + 30 - IMAGEMANAGER->findImage(_crops.imageName)->getHeight() / 2;
	_crops.centerX = idx * 60 + 30;
	_crops.centerY = idy * 60 + 30;
	_crops.hp = 0;
	_crops.maxHp = 0;
	_crops.isClick = false;
	_crops.isEffect = false;
	_crops.isHit = false;
	_crops.hitTime = 0;
	_crops.hitCount = 0;

	_crops.hpBar = 0;
	_crops.frameX = _crops.frameY = 0;
	_crops.exp = 0;
	_crops.alpha = 0;

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

void crops::setHp(int maxHp, int hp)
{
	_crops.maxHp = maxHp;
	_crops.hp = hp;
	//cout << _crops.maxHp << _crops.hp << endl;
}

//¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á imageCrops ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á

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

	if (_crops.maxHp > _crops.hp)
	{
		_crops.hpBar = ((float)_crops.hp / (float)_crops.maxHp) * 41;
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 22, _crops.centerY + 30, 0, 0, 45, 12);
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 20, _crops.centerY + 32, 0, 72, _crops.hpBar, 8);
	}
	
	//Rectangle(CAMERAMANAGER->getWorldDC(), _crops.rc);
}

//¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á frameCrops ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á

void frameCrops::update()
{
	if (_crops.frameX == IMAGEMANAGER->findImage(_crops.imageName)->getMaxFrameX()) return;
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
	if (_crops.maxHp > _crops.hp)
	{
		_crops.hpBar = ((float)_crops.hp / (float)_crops.maxHp) * 41;
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 22, _crops.centerY + 30, 0, 0, 45, 12);
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 20, _crops.centerY + 32, 0, 72, _crops.hpBar, 8);
	}
	//Rectangle(CAMERAMANAGER->getWorldDC(), _crops.rc);
}

//¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á imageFrameCrops ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á

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
	if (_crops.maxHp > _crops.hp)
	{
		_crops.hpBar = ((float)_crops.hp / (float)_crops.maxHp) * 41;
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 22, _crops.centerY + 30, 0, 0, 45, 12);
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 20, _crops.centerY + 32, 0, 72, _crops.hpBar, 8);
	}
}

//¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á treeCrops ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á


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
	if (_crops.maxHp > _crops.hp)
	{
		_crops.hpBar = ((float)_crops.hp / (float)_crops.maxHp) * 41;
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 22, _crops.centerY + 30, 0, 0, 45, 12);
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 20, _crops.centerY + 32, 0, 72, _crops.hpBar, 8);
	}
}


// ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á BUSH and FLOWER ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á
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
	if (_crops.maxHp > _crops.hp)
	{
		_crops.hpBar = ((float)_crops.hp / (float)_crops.maxHp) * 41;
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 22, _crops.centerY + 30, 0, 0, 45, 12);
		IMAGEMANAGER->findImage("healthBar")->render(CAMERAMANAGER->getWorldDC(), _crops.centerX - 20, _crops.centerY + 32, 0, 72, _crops.hpBar, 8);
	}
}
