#pragma once
#include "gameNode.h"
#include "animation.h"

class player : public gameNode
{
private:

	struct tagPlayer
	{
		animation* ani;
		image* image;
		float x, y;
		int idx, idy;
	};

	tagPlayer _player;

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();
};


