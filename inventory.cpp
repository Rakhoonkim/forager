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
	_invenSize = IMAGEMANAGER->findImage("invenSlot")->getWidth();
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
	for (int i = 0; i < INVENX * INVENY; i++)
	{
		IMAGEMANAGER->findImage("invenSlot")->render(hdc, _inven[i].rc.left, _inven[i].rc.top);
	}
}

void inventory::addInven(string imageName, int frameX, int frameY)
{
	int count = 0;
	// for문 돌려서 있으면 1증가 
	for (_miInven = _mInven.begin(); _miInven != _mInven.end(); ++_miInven)
	{
		if (_miInven->first == imageName)
		{
			_miInven->second.count++;
			return;
		}
		count++;
	}
	//없으면 추가하기 
	tagInven inven;
	inven.count = 1;
	inven.frameX = frameX;
	inven.frameY = frameY;
	inven.num = count + 1;
	inven.idx = count % 8; // 8 은 인벤토리의 개수 
	inven.idx = count / 8;
	_mInven.emplace(pair<string,tagInven>(imageName, inven));
}

void inventory::invenSetting()
{
	for (int i = 0; i < INVENY; i++)
	{
		for (int j = 0; j < INVENX; j++)
		{
			_inven[i * INVENX + j].rc = RectMake(WINSIZEX / 2 - 400 + j * 100 + ((100 -_invenSize)/2), WINSIZEY / 2 - 200 + i * 100, _invenSize, _invenSize);
		}
	}
}
