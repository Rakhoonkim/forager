#include "stdafx.h"
#include "bullet.h"

bullet::bullet()
{
}

bullet::~bullet()
{
}

HRESULT bullet::init(const char* imageName, float x, float y, float angle, float speed)
{
	_imageName = imageName;
	_bullet.ani = KEYANIMANAGER->findAnimation(imageName);
	_bullet.ani->start();

	_bullet.x = _bullet.startX = x;
	_bullet.y = _bullet.startY = y;
	_bullet.angle = _bullet.startAngle = angle;
	_bullet.speed = speed;
	_bullet.isFire = true;

	_bullet.time = TIMEMANAGER->getWorldTime();
	//���� �Ǵ� 
	_count = 0;
	_angle = 0;
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
	if (_bullet.isFire) IMAGEMANAGER->findImage(_imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _bullet.x, _bullet.y, _bullet.ani);
}


void bullet::move()
{
	if (!_bullet.isFire) return;

	//0.1 �ʸ��� ȣ��
	if (_bullet.time + 0.1f <= TIMEMANAGER->getWorldTime())
	{
		// 0~4 ���� 5~9 ������ 9�϶� �ٽ� 0 ���� �ʱ�ȭ 
		if (_count < 5)
		{
			_bullet.angle += 0.4;
		}
		else if (_count >=5 && _count < 10)
		{
			_bullet.angle -= 0.4;
		}

		if (_count == 9) _count = 0;
		_count++; // ī��Ʈ ���� 
		_bullet.time = TIMEMANAGER->getWorldTime();
	}

	// ���۰������� ��� 
	_bullet.x += cosf(_bullet.startAngle) * _bullet.speed * TIMEMANAGER->getElapsedTime() * 20;
	_bullet.y += -sinf(_bullet.startAngle) * _bullet.speed * TIMEMANAGER->getElapsedTime() * 20;
	//��Ӻ�ȭ���ִ� �� 
	_bullet.x += cosf(_bullet.angle) * _bullet.speed * TIMEMANAGER->getElapsedTime() * 20;
	_bullet.y += -sinf(_bullet.angle) * _bullet.speed * TIMEMANAGER->getElapsedTime() * 20;
	
	_bullet.rc = RectMake(_bullet.x, _bullet.y, IMAGEMANAGER->findImage(_imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_imageName)->getFrameHeight());

	//�Ѿ��� ������� ���� 
	if (getDistance(_bullet.startX, _bullet.startY, _bullet.x, _bullet.y) >= 500)
	{
		EFFECTMANAGER->play("fireBall", _bullet.x, _bullet.y);
		_bullet.isFire = false;
	}
}
