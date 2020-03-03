#pragma once
#include "stdafx.h"
#include "inventory.h"
#include "build.h"
#include "equipment.h"
#include "land.h"


class gameNode;

#define MAXOPTION 5

class uiManager : public singletonBase<uiManager>
{
private:
	tagButton		_optionList[MAXOPTION];	 //�ɼ� ����Ʈ
	equipment*					_equipment;  //���&��ųâ
	inventory*						_inven;  //�κ��丮
	build*							_build;  //�Ǽ�â
	land*					     	 _land;  //���� ����â

	int						_currentOption;
	bool						 _isOption;

	// ������������������������� PLAYER UI �������������������������

	tagPlayer*  _player;
	float	 _healthBar;   // ���� ü�¹�
	float		_expBar;   // ���� ����ġ��
	float		_slushX; 

	RECT		  _exit;   // ������ RECT
public:
	uiManager();
	~uiManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();

	// �÷��̾� �ɼ� â
	void PlayerUIRender();

	// �̿��� �ɼ� 
	void optionsSetting();
	void setButtonAlpha();
	bool getOption()		{ return _isOption; }
	void setOption()		// �ɼ� ���� �Լ�
	{
		if (!_isOption)
		{
			_isOption = true;
		}
		else
		{
			_equipment->setSkill();
			_land->setLand(false);
			_isOption = false;
			_currentOption = 1;
		}
	}		 // �ɼǼ���


	void setInven(inventory* inven)					 { _inven = inven; }
	void playerAdressLink(tagPlayer* player)	     { _player = player;}
	void buildAdressLink(buildManager* buildManager) { _build->setBuildManager(buildManager);}
	
	//Ŭ���� ������
	land*	   getLand()		 { return _land; }
	build*	   getBuild()		 { return _build; }
	inventory* getInven()		 { return _inven; }
	equipment* getEquipment()	 { return _equipment; }

	void setOptionDirection(int num) { _currentOption = num; }
};

