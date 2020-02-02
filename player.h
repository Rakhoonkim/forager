#pragma once
#include "gameNode.h"

enum PLATERSTATE
{

};

class player : public gameNode
{
private:

	int _direction;     // 플레이어의 방향

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();
};

