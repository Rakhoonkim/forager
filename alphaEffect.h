#pragma once
#include "stdafx.h"

// ����ġ ����Ʈ�� ���� ���� ���� alphaEffect
struct tagAlphaEffect
{
	const char* imageName;
	int frameX, frameY;		 // ������ ��ȣ
	float x;
	float y;
	bool isRender;			 // ���� �Ӱ谪 
	int alpha;
};

class alphaEffect
{
private: 
	vector<tagAlphaEffect*>				  _vAlphaEffect;
	vector<tagAlphaEffect*>::iterator    _viAlphaEffect;

public:
	alphaEffect();
	~alphaEffect();

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void play(const char* imageName ,int value, float x, float y);
};

