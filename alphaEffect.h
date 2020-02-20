#pragma once
#include "stdafx.h"

// 경험치 이펙트를 띄우기 위해 만든 alphaEffect
struct tagAlphaEffect
{
	const char* imageName;
	int frameX, frameY;		 // 프레임 번호
	float x;
	float y;
	bool isRender;			 // 삭제 임계값 
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

