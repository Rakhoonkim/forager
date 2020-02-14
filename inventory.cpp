#include "stdafx.h"
#include "inventory.h"

inventory::inventory()
{
}

inventory::~inventory()
{
}

HRESULT inventory::init()
{
	_invenSize = IMAGEMANAGER->findImage("invenSlot")->getWidth();	// �κ� ���� ���� ����
	invenSetting();

	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{
}

void inventory::render()
{
}

void inventory::render(HDC hdc)
{
	//�κ��丮 ���� 
	for (int i = 0; i < INVENX * INVENY; i++)
	{
		IMAGEMANAGER->findImage("invenSlot")->render(hdc, _inven[i].rc.left, _inven[i].rc.top);
		char str[100];
		sprintf_s(str, "%d", i);
		TextOut(hdc, _inven[i].rc.left, _inven[i].rc.top, str, strlen(str));
	}
	//�κ��丮 ������
	for (_miInven = _mInven.begin(); _miInven != _mInven.end(); ++_miInven)
	{	
		IMAGEMANAGER->findImage("invenItem")->frameRender(hdc, _inven[_miInven->second.num].centerX - (IMAGEMANAGER->findImage("invenItem")->getFrameWidth() / 2), _inven[_miInven->second.num].centerY - (IMAGEMANAGER->findImage("invenItem")->getFrameHeight() / 2), _miInven->second.frameX, _miInven->second.frameY);
		// �������
		invenItemCountRecder(hdc);
		//������ �κ��丮 ���� 
		/*char str[100];
		sprintf_s(str, "%d", _miInven->second.count);
		TextOut(hdc, _inven[_miInven->second.num].rc.left + 20, _inven[_miInven->second.num].rc.top, str, strlen(str));*/
	}
	//cout << _mInven.size() << endl;  // �κ� ������ 
}

void inventory::addInven(const char* imageName, int frameX, int frameY)
{
	int count = 0;
	// for�� ������ ������ 1���� 
	for (_miInven = _mInven.begin(); _miInven != _mInven.end(); ++_miInven)
	{
		if (_miInven->first == imageName)
		{
			_miInven->second.count++;
			return;
		}
		count++;
	}
	//������ �߰��ϱ� 
	tagInven inven;
	inven.count = 1;   // ���� 
	inven.frameX = frameX;
	inven.frameY = frameY;
	inven.num = count; 
	_mInven.insert(pair<const char*, tagInven>(imageName, inven));
	//_mInven.emplace(pair<const char*,tagInven>(imageName, inven));
}

void inventory::invenSetting()
{
	//�κ��丮 ����
	for (int i = 0; i < INVENY; i++)
	{
		for (int j = 0; j < INVENX; j++)
		{
			_inven[i * INVENX + j].rc = RectMake(WINSIZEX / 2 - 400 + j * 100 + ((100 -_invenSize)/2), WINSIZEY / 2 - 200 + i * 100, _invenSize, _invenSize);
			_inven[i * INVENX + j].centerX = _inven[i * INVENX + j].rc.left + (_invenSize / 2);
			_inven[i * INVENX + j].centerY = _inven[i * INVENX + j].rc.top + (_invenSize / 2);
		}
	}
}

void inventory::invenItemCountRecder(HDC hdc)
{
	//�κ� ���� ���
	for (int i = 0; i < 10; i++)
	{
		//1�� �ڸ�
		if ((_miInven->second.count % 10) == i)
		{
			IMAGEMANAGER->findImage("invenNumber")->frameRender(hdc, _inven[_miInven->second.num].centerX + 20, _inven[_miInven->second.num].centerY - (IMAGEMANAGER->findImage("invenNumber")->getFrameHeight() / 2), i, 0);
		}
		//10�� �ڸ�
		if ((_miInven->second.count / 10) % 10 == i && _miInven->second.count >= 10)
		{
			IMAGEMANAGER->findImage("invenNumber")->frameRender(hdc, _inven[_miInven->second.num].centerX + 8, _inven[_miInven->second.num].centerY - (IMAGEMANAGER->findImage("invenNumber")->getFrameHeight() / 2), i, 0);
		}
		//100�� �ڸ�
		if (_miInven->second.count / 100 == i && _miInven->second.count >= 100)
		{
			IMAGEMANAGER->findImage("invenNumber")->frameRender(hdc, _inven[_miInven->second.num].centerX - 4, _inven[_miInven->second.num].centerY - (IMAGEMANAGER->findImage("invenNumber")->getFrameHeight() / 2), i, 0);
		}
	}
}
