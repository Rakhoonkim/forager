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

	OBJECTPOOL->Init(10000); // 오브젝트 POOL 초기 사이즈 정의
	 
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

		//INDEX 업데이트
		(*iter)->idx = (*iter)->x / 60;		 // idx 
		(*iter)->idy = (*iter)->y / 60;		 // idy

		//총알이 사라지는 구간 
		if ((MAPMANAGER->setBulletBossTileCollision((*iter)->idx, (*iter)->idy) && (getDistance((*iter)->startX, (*iter)->startY, (*iter)->x, (*iter)->y) >= 50)) || (getDistance((*iter)->startX, (*iter)->startY, (*iter)->x, (*iter)->y) >= (*iter)->distance))
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
	//tempBullet = new tagBullet; ?? 하면 오류났던..
	tempBullet->ani = KEYANIMANAGER->findAnimation(_imageName);
	tempBullet->ani->start(); 
	tempBullet->x = tempBullet->startX = x;
	tempBullet->y = tempBullet->startY = y;
	tempBullet->idx = tempBullet->x / 60;
	tempBullet->idy = tempBullet->y / 60;
	tempBullet->angle = tempBullet->startAngle = angle;
	tempBullet->speed = speed;
	tempBullet->count = 0;
	tempBullet->isFire = true;
	tempBullet->distance = 500;
	tempBullet->time = TIMEMANAGER->getWorldTime();
	_vBullet.push_back(tempBullet);
}

void bullet::fire(float x, float y, float angle, float speed, float distance)
{
	tagBullet* tempBullet = OBJECTPOOL->getObject();
	//tempBullet = new tagBullet; ?? 하면 오류났던..
	tempBullet->ani = KEYANIMANAGER->findAnimation(_imageName);
	tempBullet->ani->start();
	tempBullet->x = tempBullet->startX = x;
	tempBullet->y = tempBullet->startY = y;
	tempBullet->angle = tempBullet->startAngle = angle;
	tempBullet->speed = speed;
	tempBullet->count = 0;
	tempBullet->isFire = true;
	tempBullet->distance = distance;
	tempBullet->time = TIMEMANAGER->getWorldTime();
	_vBullet.push_back(tempBullet);
}
