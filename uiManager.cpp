#include "stdafx.h"
#include "uiManager.h"
#include "gameNode.h"

uiManager::uiManager()
{
}

uiManager::~uiManager()
{
}

HRESULT uiManager::init()
{
	imageSetting();			 // �̹��� ����
	_isOption = false;		 // UI�� �����ϱ� ���� ��

	//�ֻ��� �ɼǸ޴� �ʱ�ȭ 
	for (int i = 0; i < MAXOPTION; i++)
	{
		_optionList[i].isClick = false;
		_optionList[i].alpha = 100;
		_optionList[i].frameX = i;
		_optionList[i].rc = RectMake((WINSIZEX / 2) - 210 + i * 90, 25, IMAGEMANAGER->findImage("optionListIcon")->getFrameWidth(), IMAGEMANAGER->findImage("optionListIcon")->getFrameHeight());
	}
	_currentOption = 1;		// ���� ��ư ��

	//�ʱ� ��ư �� �ʱ�ȭ
	_optionList[_currentOption].alpha = 0;
	_optionList[_currentOption].isClick = true;


	_inven = new inventory;  // _currentOption = 1  �϶�
	_inven->init();

	_build = new build;	//�Ǽ� â
	_build->init();

	_equipment = new equipment; //��� â 
	_equipment->init();

	_player = new tagPlayer; // �÷��̾� 
	_healthBar = 0;			 // �÷��̾��� ü�� 

	_weather = new weather;
	_weather->init();

	_land = new land;
	_land->init();
	
	_slushX = 0;
	return S_OK;
}

void uiManager::release()
{
}

void uiManager::update()
{
	_weather->update();
	if (_isOption)
	{
		//��ųâ�� ��Ų ���¿����� 
		if(!_equipment->getSkill()) setButtonAlpha();	//��� �ɼǿ� �־�� �� 
		
		//�ɼ� ��� 
		if (_currentOption == 0)
		{
			_land->setLand(false);
			_equipment->update();
		}
		else if (_currentOption == 1)
		{	
			_land->setLand(false);
			_inven->update();
		}
		else if (_currentOption == 2)
		{
			_land->setLand(false);
			_build->update();
		}
		else if (_currentOption == 3)
		{
			_land->setPlayerCoin(_inven->getInven().count("coinDrop"));
			_land->update();
			_land->setLand(true);
		}
	}
}

void uiManager::render()
{
	_weather->render(_backBuffer->getMemDC());
	
	PlayerUIRender();
	if (_isOption)
	{
		IMAGEMANAGER->findImage("startBackground")->alphaRender(_backBuffer->getMemDC(), 0, 0, 100);
		
		//����ȭ�� ���
		if (_currentOption == 3)
		{
			_land->render(_backBuffer->getMemDC());
		}
		
		IMAGEMANAGER->findImage("optionList")->render(_backBuffer->getMemDC(), (WINSIZEX / 2) - (IMAGEMANAGER->findImage("optionList")->getWidth() / 2), 0);
		

		for (int i = 0; i < MAXOPTION; i++)
		{
			IMAGEMANAGER->findImage("optionListIcon")->alphaFrameRender(_backBuffer->getMemDC(), _optionList[i].rc.left, _optionList[i].rc.top, _optionList[i].frameX, 0,_optionList[i].alpha);
			//Rectangle(_backBuffer->getMemDC(), _optionList[i].rc);
		}


		// 0���â : 1�κ��丮 : 2�Ǽ�â 
		if (_currentOption == 0)
		{
			_equipment->render(_backBuffer->getMemDC());
		}
		else if (_currentOption == 1)
		{
			_inven->render(_backBuffer->getMemDC());
		}
		else if (_currentOption == 2)
		{
			_build->render(_backBuffer->getMemDC());
		}

	}
}

void uiManager::imageSetting()
{
	IMAGEMANAGER->addImage("startBackground", "./image/ui/startBackground.bmp", 1200, 720, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("optionList", "./image/ui/optionList.bmp", 480, 120, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("optionListIcon", "./image/ui/optionListIcon.bmp", 340, 68,5,1, true, RGB(255, 0, 255), true);
	//����
	IMAGEMANAGER->addFrameImage("invenNumber", "./image/ui/inven/invenNumber.bmp", 140, 16, 10, 1, true, RGB(255, 0, 255));
	//�κ��丮 
	IMAGEMANAGER->addImage("invenSlot", "./image/ui/inven/invenSlot.bmp", 72, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("invenItem", "./image/ui/inven/invenItem.bmp", 540, 270, 10, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("viewItem", "./image/ui/inven/viewItem.bmp", 1080, 540, 10, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("invenItemSlot", "./image/ui/inven/invenItemSlot.bmp", 300, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("useButton", "./image/ui/inven/useButton.bmp", 120, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("disButton", "./image/ui/inven/disButton.bmp", 120, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stamina", "./image/ui/inven/stamina.bmp", 45, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("heartContainer", "./image/ui/inven/heartContainer.bmp", 45, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heartNumber", "./image/ui/inven/heartNumber.bmp", 140, 16,10,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("staminaNumber", "./image/ui/inven/staminaNumber.bmp", 140, 16, 10, 1, true, RGB(255, 0, 255));


	//�κ��丮 Ŀ���� Ŀ���Ŵ�����

	//���
	IMAGEMANAGER->addFrameImage("bigBox", "./image/ui/equipment/bigBox.bmp", 120, 240, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("disableBlock", "./image/ui/equipment/disableBlock.bmp", 288, 72, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ableBlock", "./image/ui/equipment/ableBlock.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skillIcon", "./image/ui/equipment/skillIcon.bmp", 139, 61, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("featIcon", "./image/ui/equipment/featIcon.bmp", 139, 61, true, RGB(255, 0, 255));
	//�ǹ� �Ǽ� 
	IMAGEMANAGER->addFrameImage("bigLongBox", "./image/ui/build/bigLongBox.bmp", 226, 290, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("longBox", "./image/ui/build/longBox.bmp", 156, 180, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("industry", "./image/ui/build/industry.bmp", 156, 180, 1, 4, true, RGB(255, 0, 255),true);
	IMAGEMANAGER->addFrameImage("farming", "./image/ui/build/farming.bmp", 156, 180, 1, 4, true, RGB(255, 0, 255), true);
	//�׳� �̹���
	IMAGEMANAGER->addFrameImage("building", "./image/ui/build/building.bmp", 288, 144, 3, 1, true, RGB(255, 0, 255),true);
	IMAGEMANAGER->addFrameImage("farmingImage", "./image/ui/build/farmingImage.bmp", 96, 42, 2, 1, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("industryMaterial", "./image/ui/build/industryMaterial.bmp",600, 125, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("farmingMaterial", "./image/ui/build/farmingMaterial.bmp", 400, 100, 2, 1, true, RGB(255, 0, 255));

	//ũ����Ʈ ȭ�� 
	IMAGEMANAGER->addImage("craftBackground", "./image/ui/build/craftBackground.bmp", 250, 253, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("craft", "./image/ui/build/craft.bmp", 180, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrowButton", "./image/ui/build/arrowButton.bmp", 64, 45,2,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("craftItem", "./image/ui/build/craftItem.bmp", 405, 135, 9, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("piece", "./image/ui/build/piece.bmp", 84, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pieceList", "./image/ui/build/pieceList.bmp", 954, 297, 9, 3, true, RGB(255, 0, 255));

	//fishtrap
	IMAGEMANAGER->addImage("caught", "./image/ui/build/caught.bmp", 112, 16, true, RGB(255, 0, 255));

	//====================playerUI ======================

	IMAGEMANAGER->addFrameImage("heart", "./image/ui/player/heart.bmp", 68, 30, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("healthBar", "./image/ui/player/healthBar.bmp", 100, 96, 1, 4, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("expBar", "./image/ui/player/expBar.bmp", 800, 60, 1, 2, false, RGB(255, 0, 255));

	//expnum
	IMAGEMANAGER->addFrameImage("expNum", "./image/ui/player/expNum.bmp", 208, 18, 13, 1, true, RGB(255, 0, 255),true);
	//level
	IMAGEMANAGER->addFrameImage("whiteNum", "./image/ui/player/whiteNum.bmp", 140, 16, 10, 1, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addImage("level", "./image/ui/player/level.bmp", 70, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slush", "./image/ui/player/slush.bmp", 24, 24, true, RGB(255, 0, 255));

	// ���� ����Ʈ
	IMAGEMANAGER->addFrameImage("attackEffect", "./image/ui/player/attackEffect.bmp", 510, 85, 6, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("attackEffect", "attackEffect", 510,85, 85, 85, 10, 0.5f, 10,true);


	//===================== skill ================
	IMAGEMANAGER->addImage("skillBackground", "./image/ui/equipment/skillBackground.bmp", 1200, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skillTile", "./image/ui/equipment/skillTile.bmp", 320, 320,4,4, true, RGB(255, 0, 255),true);
	IMAGEMANAGER->addImage("skillPoint", "./image/ui/equipment/skillPoint.bmp", 175, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("needPoint", "./image/ui/equipment/needPoint.bmp", 165, 16, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("landBuy", "./image/ui/landBuy.bmp", 800, 320, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("landNum", "./image/ui/landNum.bmp",350, 40, 10, 1, true, RGB(255, 0, 255));

	
}


void uiManager::PlayerUIRender()
{	

	// ���μ� ����ϱ� 
	IMAGEMANAGER->findImage("invenItem")->frameRender(_backBuffer->getMemDC(), 20, WINSIZEY - 100, 0, 3);
	int coin = _inven->getInven().count("coinDrop");
	//������ ������ ��� 	
	if (coin < 10)	
	{
		IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), 40, WINSIZEY - 50, coin, 0);
	}
	else if (coin < 100)
	{
		IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), 50, WINSIZEY - 50, coin % 10, 0);
		IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), 30, WINSIZEY - 50, (coin/10)%10, 0);
	}
	else if (coin < 1000)
	{
		IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), 60, WINSIZEY - 50, coin % 10, 0);
		IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), 40, WINSIZEY - 50, (coin / 10) % 10, 0);
		IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), 20, WINSIZEY - 50, coin / 100, 0);
	}

	// PLAYER ü��
	for (int i = 0; i < _player->maxHp; i++)
	{
		IMAGEMANAGER->findImage("heart")->frameRender(_backBuffer->getMemDC(), 15 + (i * 35), 15,1,0);
	}
	for (int i = 0; i < _player->hp; i++)
	{
		IMAGEMANAGER->findImage("heart")->frameRender(_backBuffer->getMemDC(), 15 + (i * 35), 15, 0, 0);
	}

	_healthBar = (_player->health * 0.80);
	IMAGEMANAGER->findImage("healthBar")->render(_backBuffer->getMemDC(), 15, 50, 0, 24, 86,24);	 // ȭ��Ʈ
	IMAGEMANAGER->findImage("healthBar")->render(_backBuffer->getMemDC(), 16, 51, 0, 0, 84,22);		 // ��
	IMAGEMANAGER->findImage("healthBar")->render(_backBuffer->getMemDC(), 18, 53, 0, 54, _healthBar, 18);	 // ü��
	
	//�ɼ�â�� �ƴϸ��																					 
	if (!_isOption)
	{																										 //����ġ ��
	//_expBar = 696;
		_expBar = ((float)_player->exp / (float)_player->expMax) * 696;
		IMAGEMANAGER->findImage("expBar")->render(_backBuffer->getMemDC(), WINSIZEX / 2 - 350, 10, 0, 0, 700, 30);
		IMAGEMANAGER->findImage("expBar")->render(_backBuffer->getMemDC(), WINSIZEX / 2 - 348, 12, 0, 32, _expBar, 26);
		IMAGEMANAGER->findImage("level")->render(_backBuffer->getMemDC(), WINSIZEX / 2 - 100, 17);

		//���� ��� 
		if (_player->level < 10)
		{
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), WINSIZEX / 2 - 10, 17, _player->level, 0);
		}
		else
		{
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), WINSIZEX / 2 - 10, 17, _player->level % 10, 0);
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), WINSIZEX / 2 - 10, 17, _player->level / 10, 0);
		}

		//Player ����ġ 
		if (_player->exp < 10)
		{
			_slushX = WINSIZEX / 2 + 70;
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), WINSIZEX / 2 + 50, 17, _player->exp, 0);
			IMAGEMANAGER->findImage("slush")->render(_backBuffer->getMemDC(), _slushX, 14);
		}
		else if (_player->exp < 100)
		{
			_slushX = WINSIZEX / 2 + 70;
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), WINSIZEX / 2 + 55, 17, _player->exp % 10, 0);
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), WINSIZEX / 2 + 40, 17, _player->exp / 10, 0);
			IMAGEMANAGER->findImage("slush")->render(_backBuffer->getMemDC(), _slushX, 14);
		}
		else if (_player->exp < 1000)
		{
			_slushX = WINSIZEX / 2 + 85;
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), WINSIZEX / 2 + 70, 17, _player->exp % 10, 0);
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), WINSIZEX / 2 + 55, 17, (_player->exp / 10) % 10, 0);
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), WINSIZEX / 2 + 40, 17, _player->exp / 100, 0);
			IMAGEMANAGER->findImage("slush")->render(_backBuffer->getMemDC(), _slushX, 14);
		}
		// ����ġ MAX��
		if (_player->expMax < 10)
		{
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), _slushX + 30, 17, _player->expMax, 0);
		}
		else if (_player->expMax < 100)
		{
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), _slushX + 45, 17, _player->expMax % 10, 0);  // 1�� �ڸ� 
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), _slushX + 30, 17, _player->expMax / 10, 0);  // 10�� �ڸ�
		}
		else if (_player->expMax < 1000)
		{
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), _slushX + 60, 17, _player->expMax % 10, 0);  // 1
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), _slushX + 45, 17, (_player->expMax / 10) % 10, 0);  // 10
			IMAGEMANAGER->findImage("whiteNum")->frameRender(_backBuffer->getMemDC(), _slushX + 30, 17, _player->expMax / 100, 0);  // 100
		}
	}

}

void uiManager::optionsSetting()
{

}

void uiManager::setButtonAlpha()
{
	// �ɼ� �޴�â�� Ŭ��
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXOPTION; i++)
		{
			if (PtInRect(&_optionList[i].rc, _ptMouse))
			{
				_currentOption = i;
				_build->setClickInit();	// �Ǽ� bool���� �ʱ�ȭ ���� 
				break;
			}
		}
		KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}

	// ������
	for (int i = 0; i < MAXOPTION; i++)
	{
		if (i == _currentOption)
		{
			_optionList[i].isClick = true;
			_optionList[i].alpha = 0;
		}
		else
		{
			_optionList[i].isClick = false;
			_optionList[i].alpha = 100;
		}
	}
}
