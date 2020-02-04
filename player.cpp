#include "stdafx.h"
#include "player.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{
	IMAGEMANAGER->addFrameImage("playerIdle", "./image/player/playerIdle.bmp", 198, 48, 6, 1, true, RGB(255, 0, 255));

	KEYANIMANAGER->addDefaultFrameAnimation("playerIdle", "playerIdle", 10, false, true);

	_player.image = IMAGEMANAGER->findImage("playerIdle");
	_player.ani = KEYANIMANAGER->findAnimation("playerIdle");
	_player.ani->start();
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;


	return S_OK;
}

void player::release()
{
}

void player::update()
{
}

void player::render()
{
	_player.image->aniRender(getMemDC(), _player.x, _player.y, _player.ani);
}
