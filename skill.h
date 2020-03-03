#pragma once
#include "stdafx.h"

#define SKILLX 4 // x 4
#define SKILLY 4 // y 4

class skill
{
private:
	tagSkill _skill[SKILLX * SKILLY];

	float _startX, _startY;	          // 버튼 시작 X, Y
	float		 _tileSize;

	int* _skillPoint;	// 케릭터 스킬포인트
	int		_offsetX;	// 루프렌더 X값
	int		_offsetY;	// 루프렌더 Y값

public:
	skill();
	~skill();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void skillSetting();
	void buttonClick();
	void setSkillPoint(int* num)	{ _skillPoint = num; }

};

