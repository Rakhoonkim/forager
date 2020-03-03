#pragma once
#include "stdafx.h"

#define MAXLIST 4
#define MAXINDUSTRY 3
#define MAXFARMING 2
class buildManager;

class build
{
private:
	tagButton		 _buildList[MAXLIST];
	tagButton _industryList[MAXINDUSTRY];
	tagButton   _farmingList[MAXFARMING];

	int _listHeight; // ����Ʈ�� ���� 
	int _listWidth;  // ����Ʈ�� ���� 

	int _direction;  // ����Ʈ ����Ű�� �ִ� ��ư 
	int _buildingDirection;  // �ǹ��� ����Ű�� �ִ� ��ư 
	int _farmingDirection;   // �Ĺ� �ǹ��� ����Ű�� �ִ� ��ư

	buildManager* _buildManager;  // �����ϱ� ���� 

	bool _isBuilding;	// �Ǽ� ������ �Ǵ�
public:
	build();
	~build();

	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC hdc);

	void buttonClick();
	void listOpen();

	void industryCheck();
	void farmingCheck();
	void buildingCheck();

	void setClickInit();  //��� ��� Ŭ���� �ʱ�ȭ 
	void setisBuilding() { _isBuilding = false; }	 //���� ��ư�� ����
	void setDirection()  { _direction = 5; }		 //������ NULL�� 
	void setBuildManager(buildManager* buildManager) { _buildManager = buildManager; }

	void isClickBuild();

	bool getisBuilding() { return _isBuilding; }
};

