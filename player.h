#pragma once
#include "gameNode.h"

enum PLATERSTATE
{

};

class player : public gameNode
{
private:

	int _direction;     // �÷��̾��� ����

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();
};

