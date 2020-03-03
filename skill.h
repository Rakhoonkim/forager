#pragma once
#include "stdafx.h"

#define SKILLX 4 // x 4
#define SKILLY 4 // y 4

class skill
{
private:
	tagSkill _skill[SKILLX * SKILLY];

	float _startX, _startY;	          // ��ư ���� X, Y
	float		 _tileSize;

	int* _skillPoint;	// �ɸ��� ��ų����Ʈ
	int		_offsetX;	// �������� X��
	int		_offsetY;	// �������� Y��

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

