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
	imageSetting();
	_isOption = false;		 // UI를 제어하기 위한 값

	for (int i = 0; i < MAXOPTION; i++)
	{
		_optionList[i].isClick = false;
		_optionList[i].alpha = 100;
		_optionList[i].frameX = i;
		_optionList[i].rc = RectMake((WINSIZEX / 2) - 210 + i * 90, 25, IMAGEMANAGER->findImage("optionListIcon")->getFrameWidth(), IMAGEMANAGER->findImage("optionListIcon")->getFrameHeight());
	}
	_currentOption = 1;
	_optionList[_currentOption].alpha = 0;
	_optionList[_currentOption].isClick = true;


	_inven = new inventory;  // _currentOption = 1  일때
	_inven->init();

	_build = new build;
	_build->init();

	return S_OK;
}

void uiManager::release()
{
}

void uiManager::update()
{
	if (_isOption)
	{
		setButtonAlpha();	//모든 옵션에 있어야 함 
		
		if (_currentOption == 1)
		{	
			_inven->update();
		}
		else if (_currentOption == 2)
		{
			_build->update();
		}
	}
}

void uiManager::render()
{
	if (_isOption)
	{
		IMAGEMANAGER->findImage("startBackground")->alphaRender(_backBuffer->getMemDC(), 0, 0, 100);
		IMAGEMANAGER->findImage("optionList")->render(_backBuffer->getMemDC(), (WINSIZEX / 2) - (IMAGEMANAGER->findImage("optionList")->getWidth() / 2), 0);
	
		for (int i = 0; i < MAXOPTION; i++)
		{
			IMAGEMANAGER->findImage("optionListIcon")->alphaFrameRender(_backBuffer->getMemDC(), _optionList[i].rc.left, _optionList[i].rc.top, _optionList[i].frameX, 0,_optionList[i].alpha);
			//Rectangle(_backBuffer->getMemDC(), _optionList[i].rc);
		}
		// 1일때 인벤토리
		if (_currentOption == 1)
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
	//숫자
	IMAGEMANAGER->addFrameImage("invenNumber", "./image/ui/inven/invenNumber.bmp", 140, 16, 10, 1, true, RGB(255, 0, 255));

	//인벤토리 
	IMAGEMANAGER->addImage("invenSlot", "./image/ui/inven/invenSlot.bmp", 72, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("invenItem", "./image/ui/inven/invenItem.bmp", 540, 108, 10, 2, true, RGB(255, 0, 255));

	//장비
	IMAGEMANAGER->addFrameImage("bigBox", "./image/ui/equipment/bigBox.bmp", 96, 192, 1, 4, true, RGB(255, 0, 255));
	
	//건물 건설 
	IMAGEMANAGER->addFrameImage("bigLongBox", "./image/ui/build/bigLongBox.bmp", 226, 290, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("longBox", "./image/ui/build/longBox.bmp", 156, 180, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("industry", "./image/ui/build/industry.bmp", 156, 180, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("farming", "./image/ui/build/farming.bmp", 156, 180, 1, 4, true, RGB(255, 0, 255));
	//그냥 이미지
	IMAGEMANAGER->addFrameImage("building", "./image/ui/build/building.bmp", 288, 144, 3, 1, true, RGB(255, 0, 255),true);
	IMAGEMANAGER->addFrameImage("farmingImage", "./image/ui/build/farmingImage.bmp", 96, 42, 2, 1, true, RGB(255, 0, 255), true);
}

void uiManager::optionsSetting()
{

}

void uiManager::setButtonAlpha()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXOPTION; i++)
		{
			if (PtInRect(&_optionList[i].rc, _ptMouse))
			{
				_currentOption = i;
				_build->setClickInit();// 건설 bool값을 초기화 해줌 
				break;
			}
		}
		KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}

	// 재정의
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
