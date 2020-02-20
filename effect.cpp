#include "stdafx.h"
#include "effect.h"
#include "animation.h"


effect::effect()
	: _effectImage(NULL),
	_effectAnimation(NULL),
	_isRunning(false),
	_x(0), _y(0)
{
}


effect::~effect()
{
}

HRESULT effect::init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	//����Ʈ �̹����� ������ ���и� �����
	if (!effectImage) return E_FAIL;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;
	_last = false;
	_move = false;
	_AttacEffect = false;
	_moveCount = 0;
	_angle = 1.57;
	if (!_effectAnimation) _effectAnimation = new animation;

	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();

	return S_OK;
}

HRESULT effect::init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime, bool last)
{
	//����Ʈ �̹����� ������ ���и� �����
	if (!effectImage) return E_FAIL;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;
	_last = last;
	_move = false;
	if (!_effectAnimation) _effectAnimation = new animation;

	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();
	_effectAnimation->frameContinue();
	return S_OK;
}

HRESULT effect::init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime, bool last, float x, float y)
{
	//����Ʈ �̹����� ������ ���и� �����
	if (!effectImage) return E_FAIL;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;
	_last = last;
	_move = false;
	if (!_effectAnimation) _effectAnimation = new animation;

	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->frameContinue();
	_effectAnimation->start();

	//if (!_effectImage || !_effectAnimation) return;

	//�ϴ� �߾Ӱ�����... ��ž���� ��ž���� ��...
	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;

	_effectAnimation->start();

	return S_OK;
}

void effect::release()
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void effect::update()
{
	//����Ʈ �ִϸ��̼� ���� ������ false�� ������������
	if (!_isRunning) return;

	_effectAnimation->frameUpdate(_elapsedTime);

	//���� �ִϸ��̼� �����ȣ�� false�� ����Ʈ�� ����
	if (!_effectAnimation->isPlay())
	{
		killEffect();	
	}
	move();
}

void effect::render()
{

	if (!_isRunning) return;

	//_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);
	_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);
}

void effect::render(HDC hdc)
{
	if (!_isRunning) return;
	//_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);

	_effectImage->aniRender(hdc, _x, _y, _effectAnimation);
}

void effect::move()
{
	if (!_move) return;

	cout << "move ���̴� " << endl;  // ����Ʈ ���� �����ؾ��� 
	_moveCount++;
	if (_moveCount > RND->getFromIntTo(3,10))
	{
		_angle -= RND->getFromFloatTo(0.10f,0.30f);
		_moveCount = 0;
	}
	_x += cosf(_angle) * 2;
	_y += -sinf(_angle) * 2;
}


void effect::startEffect(int x, int y)
{
	if (!_effectImage || !_effectAnimation) return;

	//�ϴ� �߾Ӱ�����... ��ž���� ��ž���� ��...
	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;

	_effectAnimation->start();
}

void effect::startEffect(float x, float y)
{
	if (!_effectImage || !_effectAnimation) return;

	//�ϴ� �߾Ӱ�����... ��ž���� ��ž���� ��...
	_x = x; //- (_effectAnimation->getFrameWidth() / 2);
	_y = y; //- (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;

	_effectAnimation->start();
}

void effect::startEffect(float x, float y, bool move)
{
	if (!_effectImage || !_effectAnimation) return;

	//�ϴ� �߾Ӱ�����... ��ž���� ��ž���� ��...
	_x = x; //- (_effectAnimation->getFrameWidth() / 2);
	_y = y; //- (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_move = move;
	_angle = 1.57;
	_effectAnimation->start();
}

void effect::killEffect()
{
	_isRunning = false;
}
