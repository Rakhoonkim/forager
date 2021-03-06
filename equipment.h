#pragma once
#include "stdafx.h"
#include "skill.h"

class equipment
{
private:
	tagButton  _skillButton;		// 스킬버튼
	tagButton	_featButton;		// 위업버튼 

	tagButton   _weaponButton[11]; // 도구 및 무기
	tagButton     _equipButton[6]; // 장신구
	tagButton      _sealButton[9]; // 씰
	tagButton _treasureButton[15]; // 

	skill* _skill;		// 스킬창

	bool _isSkill;
public:
	equipment();
	~equipment();

	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC hdc);

	void buttonSetting();

	bool getSkill()					 { return _isSkill; }
	void setSkill()					 { _isSkill = false; }
	void setSkillPount(int* point)   { _skill->setSkillPoint(point); }

};

