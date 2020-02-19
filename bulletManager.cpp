#include "stdafx.h"
#include "bulletManager.h"

bulletManager::bulletManager()
{
}

bulletManager::~bulletManager()
{
}

HRESULT bulletManager::init()
{
	return S_OK;
}

void bulletManager::update()
{
	vector<bullet*>::iterator iter = _vBullet.begin();
	vector<bullet*>::iterator endIter = _vBullet.end();
	for (iter; iter != endIter; iter++)
	{
		(*iter)->update();
	}
	remove();
}

void bulletManager::release()
{
}

void bulletManager::render()
{
	vector<bullet*>::iterator iter = _vBullet.begin();
	vector<bullet*>::iterator endIter = _vBullet.end();
	for (iter; iter != endIter; iter++)
	{
		(*iter)->render();
	}
}

void bulletManager::remove()
{
	vector<bullet*>::iterator iter = _vBullet.begin();
	vector<bullet*>::iterator endIter = _vBullet.end();
	for (iter; iter != endIter; iter++)
	{
		if (!(*iter)->getBullet()->isFire)
		{
			_vBullet.erase(iter);
			break;
		}
	}
}

void bulletManager::fire(const char* imageName, float x, float y, float angle, float speed)
{
	bullet* temp;
	temp = new bullet;
	temp->init(imageName, x, y, angle, speed);
	_vBullet.push_back(temp);
}
