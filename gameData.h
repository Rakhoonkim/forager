#pragma once
#include "stdafx.h"
#include "singletonBase.h"

class gameData : public singletonBase<gameData>
{
private:
	tagPlayer _player;

public:
	gameData();
	~gameData();

	HRESULT init();
	void release();
	void update();
	void render();

	tagPlayer getPlayer()			 { return _player; }
	void setPlayer(tagPlayer player) { _player = player; }
};

