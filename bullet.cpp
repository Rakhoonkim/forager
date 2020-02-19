#include "stdafx.h"
#include "bullet.h"

bullet::bullet()
{
}

bullet::~bullet()
{
}

HRESULT bullet::init(const char* imageName)
{
	_imageName = imageName;
	OBJECTPOOL->Init(10000);
	//방향 판단 
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	move();
}

void bullet::render()
{
	vector<tagBullet*>::iterator iter = _vBullet.begin();
	vector<tagBullet*>::iterator endIter = _vBullet.end();
	for (iter; iter != endIter; iter++)
	{
		if (!(*iter)->isFire) continue;
		IMAGEMANAGER->findImage(_imageName)->aniRender(CAMERAMANAGER->getWorldDC(), (*iter)->x, (*iter)->y, (*iter)->ani);
	}
}


void bullet::move()
{
	vector<tagBullet*>::iterator iter = _vBullet.begin();
	vector<tagBullet*>::iterator endIter = _vBullet.end();

	for (iter; iter != endIter; iter++)
	{
		if (!(*iter)->isFire) continue;

		if ((*iter)->time + 0.1f <= TIMEMANAGER->getWorldTime())
		{
			if ((*iter)->count < 5)
			{
				(*iter)->angle += 0.4;
			}
			else if ((*iter)->count >= 5 && (*iter)->count < 10)
			{
				(*iter)->angle -= 0.4;
			}

			if ((*iter)->count == 9) (*iter)->count = 0;
			(*iter)->count++;
			(*iter)->time = TIMEMANAGER->getWorldTime();
		}


		(*iter)->x += cosf((*iter)->startAngle) * (*iter)->speed * TIMEMANAGER->getElapsedTime() * 20;
		(*iter)->y += -sinf((*iter)->startAngle) * (*iter)->speed * TIMEMANAGER->getElapsedTime() * 20;
		//계속변화해주는 값 
		(*iter)->x += cosf((*iter)->angle) * (*iter)->speed * TIMEMANAGER->getElapsedTime() * 20;
		(*iter)->y += -sinf((*iter)->angle) * (*iter)->speed * TIMEMANAGER->getElapsedTime() * 20;

		(*iter)->rc = RectMake((*iter)->x, (*iter)->y, IMAGEMANAGER->findImage(_imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_imageName)->getFrameHeight());

		//총알이 사라지는 구간 
		if (getDistance((*iter)->startX, (*iter)->startY, (*iter)->x, (*iter)->y) >= 500)
		{
			EFFECTMANAGER->play("fireBall", (*iter)->x, (*iter)->y);
			(*iter)->isFire = false;
		}
	}
}

void bullet::remove()
{
	vector<tagBullet*>::iterator iter = _vBullet.begin();
	vector<tagBullet*>::iterator endIter = _vBullet.end();
	for (iter; iter != endIter;)
	{
		if (!(*iter)->isFire)
		{
			OBJECTPOOL->returnObject((*iter));
			iter = _vBullet.erase(iter);
		}
		else iter++;
	}

}

void bullet::fire(float x, float y, float angle, float speed)
{
	tagBullet* tempBullet = OBJECTPOOL->getObject();
	//tempBullet = new tagBullet;
	tempBullet->ani = KEYANIMANAGER->findAnimation(_imageName);
	tempBullet->ani->start();
	tempBullet->x = tempBullet->startX = x;
	tempBullet->y = tempBullet->startY = y;
	tempBullet->angle = tempBullet->startAngle = angle;
	tempBullet->speed = speed;
	tempBullet->count = 0;
	tempBullet->isFire = true;
	tempBullet->time = TIMEMANAGER->getWorldTime();
	_vBullet.push_back(tempBullet);
}
