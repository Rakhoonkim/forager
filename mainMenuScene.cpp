#include "stdafx.h"
#include "mainMenuScene.h"

mainMenuScene::mainMenuScene()
{
}

mainMenuScene::~mainMenuScene()
{
}

HRESULT mainMenuScene::init()
{
	CURSORMANAGER->setCursor();	//Ŀ�� 

	_buttonX = 60;
	_buttonY = 40;
	_distance = 20;

	imageSetting();		// �̹��� ����
	buttonSetting();	// ��ư �̹��� ����

	_offsetX = 0;
	_offsetY = 0;
	return S_OK;
}

void mainMenuScene::release()
{
}

void mainMenuScene::update()
{
	if (_offsetX > 1200) _offsetX = 0;
	buttonEffect();		//��ư ����Ʈ
	buttonClick();;		//��ư Ŭ�� ����
}

void mainMenuScene::render()
{
	_offsetX++;
	IMAGEMANAGER->findImage("mainMenuBackground")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _offsetX, _offsetY);

	//��ư ����
	for (int i = 0; i < MAXBUTTON; i++)
	{
		// ��ư ����Ʈ�� �ƴϸ�
		if (!_button[i].isEffect)
		{
			IMAGEMANAGER->findImage(_button[i].imageName)->render(getMemDC(), _button[i].rc.left, _button[i].rc.top);
		}
		else		
		{
			IMAGEMANAGER->findImage(_button[i].imageName)->alphaRender(getMemDC(), _button[i].rc.left, _button[i].rc.top,_button[i].alpha);
		}
	}
	//�߾� �ΰ�
	IMAGEMANAGER->findImage("foragerLogo")->render(getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("foragerLogo")->getWidth() / 2), 30);

	//Rectangle(getMemDC(), _mapToolButton.rc);

	//���̺� ���� �̹��� ���� ���� 
	//IMAGEMANAGER->findImage("startBackground")->alphaRender(getMemDC(), 0, 0,100);
	//IMAGEMANAGER->findImage("saveSlot")->render(getMemDC(), (WINSIZEX / 2) - 450, WINSIZEY /5);
	//IMAGEMANAGER->findImage("saveSlotBackground")->render(getMemDC(), (WINSIZEX / 2) - 465, WINSIZEY / 5 - 15);

}

void mainMenuScene::imageSetting()
{
	//���
	IMAGEMANAGER->addImage("mainMenuBackground", "./image/ui/mainMenu/newMainMenuBackground.bmp", 1200, 720, false, RGB(255, 0, 255));
	//��ư �̹���
	IMAGEMANAGER->addImage("playButton", "./image/ui/mainMenu/play.bmp", 416, 132, true, RGB(255, 0, 255),true);
	IMAGEMANAGER->addImage("extraButton", "./image/ui/mainMenu/extras.bmp", 396, 104, true, RGB(255, 0, 255),true);
	IMAGEMANAGER->addImage("roadButton", "./image/ui/mainMenu/roadMap.bmp", 392, 104, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("comunityButton", "./image/ui/mainMenu/comunity.bmp", 400, 92, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("creditsButton", "./image/ui/mainMenu/credits.bmp", 332, 88, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("optionsButton", "./image/ui/mainMenu/options.bmp", 288, 100, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("exitButton", "./image/ui/mainMenu/exit.bmp", 208, 100, true, RGB(255, 0, 255), true);
	//�߾� �ΰ�
	IMAGEMANAGER->addImage("foragerLogo", "./image/ui/mainMenu/foragerLogo.bmp", 250, 133, true, RGB(255, 0, 255), true);
	

	//SAVE DATA �о� ������
	//���� ����
	//���� ����� �ٸ������� ���� 
	IMAGEMANAGER->addImage("startBackground", "./image/ui/startBackground.bmp", 1200, 720, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("saveSlot", "./image/ui/saveSlot.bmp", 900, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("saveSlotBackground", "./image/ui/saveSlotBackground.bmp", 930, 400, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("maptoolButton", "./image/ui/mainMenu/maptoolButton.bmp", 302, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("maptoolButton2", "./image/ui/mainMenu/maptoolButton2.bmp", 302, 80, true, RGB(255, 0, 255),true);
}
// ��ġ��� ! 
void mainMenuScene::buttonSetting()
{
	_button[0].rc = RectMake(_buttonX, _buttonY, IMAGEMANAGER->findImage("playButton")->getWidth(), IMAGEMANAGER->findImage("playButton")->getHeight());
	_button[1].rc = RectMake(_buttonX + 10, 155 + _distance, IMAGEMANAGER->findImage("extraButton")->getWidth(), IMAGEMANAGER->findImage("extraButton")->getHeight());
	_button[2].rc = RectMake(_buttonX + 15, 265 + _distance, IMAGEMANAGER->findImage("roadButton")->getWidth(), IMAGEMANAGER->findImage("roadButton")->getHeight());
	_button[3].rc = RectMake(_buttonX, 380 + _distance, IMAGEMANAGER->findImage("comunityButton")->getWidth(), IMAGEMANAGER->findImage("comunityButton")->getHeight());;
	_button[4].rc = RectMake(_buttonX + 40, 480 + _distance, IMAGEMANAGER->findImage("creditsButton")->getWidth(), IMAGEMANAGER->findImage("creditsButton")->getHeight());;
	_button[5].rc = RectMake(_buttonX - 40, 585 + _distance, IMAGEMANAGER->findImage("optionsButton")->getWidth() - 30, IMAGEMANAGER->findImage("optionsButton")->getHeight());;
	_button[6].rc = RectMake(_buttonX + 230, 585 + _distance, IMAGEMANAGER->findImage("exitButton")->getWidth(), IMAGEMANAGER->findImage("exitButton")->getHeight());;
	_button[7].rc = RectMake(WINSIZEX / 2 + 220, WINSIZEY - 220, 267, 78);
	_button[0].imageName = "playButton";
	_button[1].imageName = "extraButton";
	_button[2].imageName = "roadButton";
	_button[3].imageName = "comunityButton";
	_button[4].imageName = "creditsButton";
	_button[5].imageName = "optionsButton";
	_button[6].imageName = "exitButton";
	_button[7].imageName = "maptoolButton2";
	//��ư 7�� �ʱ�ȭ 
	for (int i = 0; i < MAXBUTTON; i++)
	{
		_button[i].isClick = false;
		_button[i].isEffect = false;
		_button[i].alpha = 0;
	}

	//_mapToolButton.rc = RectMake(WINSIZEX/2 +220, WINSIZEY - 220,  267, 78);
}

void mainMenuScene::buttonClick()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXBUTTON; i++)
		{
			if(PtInRect(&_button[i].rc,_ptMouse)) _button[i].isClick = true;
			break;
		}
	}

	//���� ��ư�� ������ ���������� 
	if (_button[0].isClick)
	{
		SCENEMANAGER->changeScene("STAGE");
	}

	//���� ��ư�� ������ ������ �̵�
	if (_button[7].isClick)
	{
		SCENEMANAGER->changeScene("MAPTOOL");
	}
}

void mainMenuScene::buttonEffect()
{
	//��ư ����Ʈ ����
	for (int i = 0; i < MAXBUTTON; i++)
	{
		if (_button[i].isEffect) continue;

		if (PtInRect(&_button[i].rc, _ptMouse))
		{
			_button[i].isEffect = true;
			break;
		}

	}

	//��ư ����Ʈ�̸� 
	for (int i = 0; i < MAXBUTTON; i++)
	{
		if (!_button[i].isEffect) continue;
		//���İ� ����
		_button[i].alpha += 5;
		//���İ��� ������ �̻��̸�
		if (_button[i].alpha >= 150)
		{
			if (!PtInRect(&_button[i].rc, _ptMouse))
			{
				_button[i].alpha = 0;
				_button[i].isEffect = false;
				continue;
			}
		}
	}
}
