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
	_invenSize = IMAGEMANAGER->findImage("invenSlot")->getWidth();	// 인벤 가로 길이 셋팅
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
	//인벤토리 슬롯 
	for (int i = 0; i < INVENX * INVENY; i++)
	{
		IMAGEMANAGER->findImage("invenSlot")->render(hdc, _inven[i].rc.left, _inven[i].rc.top);
		char str[100];
		sprintf_s(str, "%d", i);
		TextOut(hdc, _inven[i].rc.left, _inven[i].rc.top, str, strlen(str));
	}
	//인벤토리 아이템
	for (_miInven = _mInven.begin(); _miInven != _mInven.end(); ++_miInven)
	{	
		IMAGEMANAGER->findImage("invenItem")->frameRender(hdc, _inven[_miInven->second.num].centerX - (IMAGEMANAGER->findImage("invenItem")->getFrameWidth() / 2), _inven[_miInven->second.num].centerY - (IMAGEMANAGER->findImage("invenItem")->getFrameHeight() / 2), _miInven->second.frameX, _miInven->second.frameY);
		// 숫자출력
		invenItemCountRecder(hdc);
		//디버깅용 인벤토리 숫자 
		/*char str[100];
		sprintf_s(str, "%d", _miInven->second.count);
		TextOut(hdc, _inven[_miInven->second.num].rc.left + 20, _inven[_miInven->second.num].rc.top, str, strlen(str));*/
	}
	//cout << _mInven.size() << endl;  // 인벤 사이즈 
}

void inventory::addInven(const char* imageName, int frameX, int frameY)
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
	inven.count = 1;   // 개수 
	inven.frameX = frameX;
	inven.frameY = frameY;
	inven.num = count; 
	_mInven.insert(pair<const char*, tagInven>(imageName, inven));
	//_mInven.emplace(pair<const char*,tagInven>(imageName, inven));
}

//아직 실험 안함 
//인벤 삭제 
void inventory::removeInven(const char* imageName, int count)
{
	_mInven[imageName].count = _mInven[imageName].count - count;
	if (_mInven[imageName].count <= 0)
	{
		_mInven.erase(imageName);
		return;
	}
}

void inventory::invenSetting()
{
	//인벤토리 셋팅
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
	//인벤 개수 출력
	for (int i = 0; i < 10; i++)
	{
		//1의 자리
		if ((_miInven->second.count % 10) == i)
		{
			IMAGEMANAGER->findImage("invenNumber")->frameRender(hdc, _inven[_miInven->second.num].centerX + 20, _inven[_miInven->second.num].centerY - (IMAGEMANAGER->findImage("invenNumber")->getFrameHeight() / 2), i, 0);
		}
		//10의 자리
		if ((_miInven->second.count / 10) % 10 == i && _miInven->second.count >= 10)
		{
			IMAGEMANAGER->findImage("invenNumber")->frameRender(hdc, _inven[_miInven->second.num].centerX + 8, _inven[_miInven->second.num].centerY - (IMAGEMANAGER->findImage("invenNumber")->getFrameHeight() / 2), i, 0);
		}
		//100의 자리
		if (_miInven->second.count / 100 == i && _miInven->second.count >= 100)
		{
			IMAGEMANAGER->findImage("invenNumber")->frameRender(hdc, _inven[_miInven->second.num].centerX - 4, _inven[_miInven->second.num].centerY - (IMAGEMANAGER->findImage("invenNumber")->getFrameHeight() / 2), i, 0);
		}
	}
}

bool inventory::foranceRecipes(FURNACERECIPE recipe, int count)
{
	if (_mInven.size() <= 0) return false;

	if (recipe == FURNACERECIPE::COAL)
	{
		//key 값을 찾아내는 방법 
		// count 함수  -> 0이면 
		// find 함수 있는지 확인  find == m.end() 없는것
		if (_mInven.count("woodDrop") == 0) return false;  // 없으면 
		if (_mInven["woodDrop"].count >= 2)
		{
			return true;
		}
		return false;
	}
	else if (recipe == FURNACERECIPE::BRICK)
	{
		if (_mInven.count("stoneDrop") == 0 || _mInven.count("coalDrop") == 0) return false;  // 없으면 
		if (_mInven["stoneDrop"].count >= 2 && _mInven["coalDrop"].count >= 1)
		{ 
			return true;
		}
		return false;
	}
	else if (recipe == FURNACERECIPE::IRON)
	{
		if (_mInven.count("ironOreDrop") == 0 || _mInven.count("coalDrop") == 0) return false;  // 없으면 
		if (_mInven["ironOreDrop"].count >= 2 && _mInven["coalDrop"].count >= 1)
		{
			return true;
		}
		return false;
	}
	else if (recipe == FURNACERECIPE::GOLD)
	{
		if (_mInven.count("goldOreDrop") == 0 || _mInven.count("coalDrop") == 0) return false;  // 없으면 
		if (_mInven["goldOreDrop"].count >= 2 && _mInven["coalDrop"].count >= 1)
		{
			return true;
		}
		return false;
	}
	else if (recipe == FURNACERECIPE::STEEL)
	{
		if (_mInven.count("goldOreDrop") == 0 || _mInven.count("coalDrop") == 0|| _mInven.count("ironOreDrop") == 0) return false;  // 없으면 
		if (_mInven["goldOreDrop"].count >= 2 && _mInven["coalDrop"].count >= 1&& _mInven["ironOreDrop"].count >=2)
		{
			return true;
		}
		return false;
	}
	else if (recipe == FURNACERECIPE::GLASS) // 모래 추가할 예정 
	{
		if ( _mInven.count("coalDrop") == 0 ) return false;  // 없으면 
			if ( _mInven["coalDrop"].count >= 2 )
			{
				return true;
			}
		return false;
	}
	else if (recipe == FURNACERECIPE::BREAD) // 밀가루 추가할 예정 
	{
		if (_mInven.count("coalDrop") == 0) return false;  // 없으면 
		if (_mInven["coalDrop"].count >= 2)
		{
			return true;
		}
		return false;
	}
	else if (recipe == FURNACERECIPE::FISH) // fish 추가할 예정 
	{
		if (_mInven.count("coalDrop") == 0) return false;  // 없으면 
		if (_mInven["coalDrop"].count >= 2)
		{
			return true;
		}
		return false;
	}
	else if (recipe == FURNACERECIPE::MEAT) // meat 추가할 예정 
	{
		if (_mInven.count("coalDrop") == 0) return false;  // 없으면 
		if (_mInven["coalDrop"].count >= 2)
		{
			return true;
		}
		return false;
	}
	else 
	{
		return false;
	}
	return false;
}

bool inventory::forgeRecipes(FORGERECIPE recipe, int count)
{
	if (_mInven.size() <= 0) return false;

	if (recipe == FORGERECIPE::COIN)
	{
		//key 값을 찾아내는 방법 
		// count 함수  -> 0이면 
		// find 함수 있는지 확인  find == m.end() 없는것
		if (_mInven.count("goldingotDrop") == 0) return false;  // 없으면 
		if (_mInven["goldingotDrop"].count >= 1)
		{
			return true;
		}
		return false;
	}
	else if (recipe == FORGERECIPE::SHOVEL)
	{
		if (_mInven.count("ironingotDrop") == 0 || _mInven.count("woodDrop") == 0) return false;  // 없으면 
		if (_mInven["woodDrop"].count >= 20 && _mInven["ironingotDrop"].count >= 20)
		{
			return true;
		}
		return false;
	}
	else if (recipe == FORGERECIPE::SWORD)
	{
		if (_mInven.count("ironingotDrop") == 0) return false;  // 젤리 추가 예정  
		if (_mInven["ironingotDrop"].count >= 20)
		{
			return true;
		}
		return false;
	}
	else if (recipe == FORGERECIPE::PICKAXE)
	{
		if (_mInven.count("ironingotDrop") == 0 || _mInven.count("coalDrop") == 0) return false;  // 젤리 추가 예정 
		if (_mInven["ironingotDrop"].count >= 15 && _mInven["coalDrop"].count >= 2)
		{
			return true;
		}
		return false;
	}
	else if (recipe == FORGERECIPE::BOTTLE)
	{
		if (_mInven.count("threadDrop") == 0|| _mInven.count("grassDrop") == 0) return false;  // 없으면 
		if (_mInven["threadDrop"].count >= 1 && _mInven["grassDrop"].count >= 2)
		{
			return true;
		}
		return false;
	}



	return false;
}

bool inventory::sewingRecipes(SEWINGRECIPE recipe, int count)
{
	if (_mInven.size() <= 0) return false;

	if (recipe == SEWINGRECIPE::THREAD)
	{
		//key 값을 찾아내는 방법 
		// count 함수  -> 0이면 
		// find 함수 있는지 확인  find == m.end() 없는것
		if (_mInven.count("fiberDrop") == 0) return false;  // 없으면 
		if (_mInven["fiberDrop"].count >= 2)
		{
			return true;
		}
		return false;
	}
	else if (recipe == SEWINGRECIPE::SMALL_BACKPACK)
	{
		//key 값을 찾아내는 방법 
		// count 함수  -> 0이면 
		// find 함수 있는지 확인  find == m.end() 없는것
		if (_mInven.count("threadDrop") == 0 || _mInven.count("ironOreDrop") == 0) return false;  // 없으면 
		if (_mInven["threadDrop"].count >= 10 && _mInven["ironOreDrop"].count >= 10)
		{
			return true;
		}
		return false;
	}
	else if (recipe == SEWINGRECIPE::MEDIUM_BACKPACK)
	{
		//key 값을 찾아내는 방법 
		// count 함수  -> 0이면 
		// find 함수 있는지 확인  find == m.end() 없는것
		if (_mInven.count("threadDrop") == 0 || _mInven.count("ironingotDrop") == 0) return false;  // 없으면 
		if (_mInven["threadDrop"].count >= 20 && _mInven["ironingotDrop"].count >= 15)
		{
			return true;
		}
		return false;
	}
	else if (recipe == SEWINGRECIPE::SMALL_WALLET)
	{
		//key 값을 찾아내는 방법 
		// count 함수  -> 0이면 
		// find 함수 있는지 확인  find == m.end() 없는것
		if (_mInven.count("threadDrop") == 0 || _mInven.count("goldOreDrop") == 0) return false;  // 없으면 
		if (_mInven["threadDrop"].count >= 10 && _mInven["goldOreDrop"].count >= 10)
		{
			return true;
		}
		return false;
	}
	else if (recipe == SEWINGRECIPE::SLIME_WALLET)
	{
		//key 값을 찾아내는 방법 
		// count 함수  -> 0이면 
		// find 함수 있는지 확인  find == m.end() 없는것
		if (_mInven.count("threadDrop") == 0 || _mInven.count("goldingotDrop") == 0) return false;  // 없으면 
		if (_mInven["threadDrop"].count >= 20 && _mInven["goldingotDrop"].count >= 10)
		{
			return true;
		}
		return false;
	}
	return false;
}


