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
	_player = new tagPlayer; // 플레이어 
	_invenSize = IMAGEMANAGER->findImage("invenSlot")->getWidth();	// 인벤 가로 길이 셋팅
	invenSetting();
	_direction = NULL;
	_invenItemSlot = false;
	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{
	invenClick();
	InvenPointer();
	invenMove();
}

void inventory::render()
{
}

void inventory::render(HDC hdc)
{
	//인벤토리 슬롯 
	for (int i = 0; i < INVENX * INVENY; i++)
	{
		IMAGEMANAGER->findImage("invenSlot")->render(hdc, _inven[i].x, _inven[i].y);
		//Rectangle(hdc, _inven[i].rc);
	/*	char str[100];
		sprintf_s(str, "%d", i);
		TextOut(hdc, _inven[i].rc.left, _inven[i].rc.top, str, strlen(str));*/
		if (_inven[i].isClick)
		{
			IMAGEMANAGER->findImage("invenSlotCursor")->aniRender(hdc, _inven[i].rc.left - 7, _inven[i].rc.top -9,KEYANIMANAGER->findAnimation("invenSlotCursor"));	
		}
	}


	if (_invenItemSlot && _inven[_direction].isItem)
	{
		IMAGEMANAGER->findImage("invenItemSlot")->render(hdc, _inven[7].x + 100, _inven[7].y);

		IMAGEMANAGER->findImage("viewItem")->frameRender(hdc, _inven[7].x + 200, _inven[7].y + 50, _inven[_direction].frameX, _inven[_direction].frameY);
	
		if (_inven[_direction].isUse)
		{
			IMAGEMANAGER->findImage("stamina")->render(hdc, _inven[7].x + 150, _inven[7].y + 200);
			IMAGEMANAGER->findImage("heartContainer")->render(hdc, _inven[7].x + 250, _inven[7].y + 200);

			//stemina창
			if (_inven[_direction].stemina < 10)
			{
				IMAGEMANAGER->findImage("staminaNumber")->frameRender(hdc, _inven[7].x + 190, _inven[7].y + 220, _inven[_direction].stemina % 10, 0);
			}
			else if (_inven[_direction].stemina < 100)
			{
				IMAGEMANAGER->findImage("staminaNumber")->frameRender(hdc, _inven[7].x + 210, _inven[7].y + 220, _inven[_direction].stemina % 10, 0);
				IMAGEMANAGER->findImage("staminaNumber")->frameRender(hdc, _inven[7].x + 190, _inven[7].y + 220, (_inven[_direction].stemina /10)%10, 0);
			}

			//heart창 
			if (_inven[_direction].heart < 10)
			{
				IMAGEMANAGER->findImage("heartNumber")->frameRender(hdc, _inven[7].x + 310, _inven[7].y + 220, _inven[_direction].heart % 10, 0);
			}
			else if (_inven[_direction].heart < 100)
			{
				IMAGEMANAGER->findImage("heartNumber")->frameRender(hdc, _inven[7].x + 330, _inven[7].y + 220, _inven[_direction].heart % 10, 0);
				IMAGEMANAGER->findImage("heartNumber")->frameRender(hdc, _inven[7].x + 310, _inven[7].y + 220, (_inven[_direction].heart / 10) % 10, 0);
			}

		}
		


		IMAGEMANAGER->findImage("useButton")->render(hdc, _useButton.x, _useButton.y);
		IMAGEMANAGER->findImage("disButton")->render(hdc, _disButton.x, _disButton.y);


		//하트 체력 
	}



	//인벤토리 아이템
	for (_miInven = _mInven.begin(); _miInven != _mInven.end(); ++_miInven)
	{	
		if (!_inven[_miInven->second.num].isItem) continue;
		IMAGEMANAGER->findImage("invenItem")->frameRender(hdc, _inven[_miInven->second.num].centerX - (IMAGEMANAGER->findImage("invenItem")->getFrameWidth() / 2), _inven[_miInven->second.num].centerY - (IMAGEMANAGER->findImage("invenItem")->getFrameHeight() / 2), _miInven->second.frameX, _miInven->second.frameY);
		// 숫자출력
		invenItemCountRecder(hdc);

		//SELECTION출력


		//디버깅용 인벤토리 숫자 
		/*char str[100];
		sprintf_s(str, "%d", _miInven->second.count);
		TextOut(hdc, _inven[_miInven->second.num].rc.left + 20, _inven[_miInven->second.num].rc.top, str, strlen(str));*/
	}
	//cout << _mInven.size() << endl;  // 인벤 사이즈 
}

void inventory::addInven(const char* imageName, int frameX, int frameY,int stemina, int heart , bool use)
{
	int count = 0;
	// for문 돌려서 있으면 1증가 
	for (_miInven = _mInven.begin(); _miInven != _mInven.end(); ++_miInven)
	{
		if (_miInven->first == imageName)
		{
			_miInven->second.count++; // 개수 추가 
			return;
		}
		count++;
	}
	//없으면 추가하기 
	tagInven inven;
	inven.imageName = imageName;
	inven.count = 1;   // 개수 
	inven.frameX = frameX;
	inven.frameY = frameY;
	inven.num = this->invenNumber(); // 인밴의 위치 
	_inven[inven.num].imageName = imageName;
	_inven[inven.num].stemina = inven.stemina = stemina;
	_inven[inven.num].heart = inven.heart = heart;
	_inven[inven.num].isItem = true;
	_inven[inven.num].frameX = frameX;
	_inven[inven.num].frameY = frameY;
	_inven[inven.num].isUse = use;
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
		_inven[_mInven[imageName].num].isItem = false;
		_inven[_mInven[imageName].num].isUse = false;
		_inven[_mInven[imageName].num].frameX = NULL;
		_inven[_mInven[imageName].num].frameY = NULL;
		_inven[_mInven[imageName].num].imageName = NULL;
		_inven[_mInven[imageName].num].heart = NULL;
		_inven[_mInven[imageName].num].stemina = NULL;
		_inven[_mInven[imageName].num].num = NULL;
		_inven[_mInven[imageName].num].count = NULL;
		_mInven.erase(imageName);
		return;
	}
}

void inventory::InvenPointer()
{
	for (int i = 0; i < INVENY * INVENX; i++)
	{
		if (_direction != i) _inven[i].isClick = false;
		if (PtInRect(&_inven[i].rc,  _ptMouse))
		{
			CURSORMANAGER->setInvenCursor();
			CURSORMANAGER->getCursor()->setCursorXY(_inven[i].rc.left + _invenSize / 2, _inven[i].rc.top + _invenSize / 2);
			cout << "인벤슬롯이랑 충돌중이다" << endl;

			return;
		}
	}

	CURSORMANAGER->setCursor();
	CURSORMANAGER->getCursor()->setCursorChange();
}

void inventory::itemUse()
{

}

void inventory::invenMove()
{
	if (_inven[_direction].isClick && _inven[_direction].isItem)
	{
		for (int i = 0; i < INVENX * INVENY; i++)
		{
			if (_inven[0].x > 50)
			{
				_inven[i].x -= 5;
			}
			else if (_inven[0].x < 50)
			{
				_invenItemSlot = true;
				break;
			}
			_inven[i].rc = RectMake(_inven[i].x, _inven[i].y, _invenSize, _invenSize);
			_inven[i].centerX = _inven[i].x + (_invenSize / 2);
			_inven[i].centerY = _inven[i].y + (_invenSize / 2);

		}
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
			_inven[i * INVENX + j].isClick = false;
			_inven[i * INVENX + j].isItem = false;
			_inven[i * INVENX + j].x = _inven[i * INVENX + j].rc.left;
			_inven[i * INVENX + j].y = _inven[i * INVENX + j].rc.top;
			_inven[i * INVENX + j].centerX = _inven[i * INVENX + j].x + (_invenSize / 2);
			_inven[i * INVENX + j].centerY = _inven[i * INVENX + j].y + (_invenSize / 2);
			_inven[i * INVENX + j].stemina = 0;
			_inven[i * INVENX + j].heart = 0;
		}
	}
	_useButton.x = WINSIZEX / 2+ 280;
	_useButton.y = WINSIZEY / 2 +100;
	_useButton.rc = RectMake(_useButton.x, _useButton.y, IMAGEMANAGER->findImage("useButton")->getWidth(), IMAGEMANAGER->findImage("useButton")->getHeight());
	_disButton.x = _useButton.rc.right + 10;
	_disButton.y = _useButton.y;
	_disButton.rc = RectMake(_disButton.x, _disButton.y, IMAGEMANAGER->findImage("useButton")->getWidth(), IMAGEMANAGER->findImage("useButton")->getHeight());
}

void inventory::invenClick()
{
	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{ 
		//인벤토리 선택
		for (int i = 0; i < INVENY * INVENX; i++)
		{
			if (PtInRect(&_inven[i].rc, _ptMouse))
			{
				_direction = i;
				break;
			}
		}
		//클릭 
		_inven[_direction].isClick = true;

		//사용 및 
		if (_invenItemSlot && _inven[_direction].isUse)
		{
			if (PtInRect(&_useButton.rc, _ptMouse))
			{
				//체력증가
				_player->health += _inven[_direction].stemina;
				_player->hp += _inven[_direction].heart;

				//인벤토리 1개 마이너스
				this->removeInven(_inven[_direction].imageName, 1);

				if (_player->health >= 100) _player->health = 100;					// 스테미나 최대값 예외처리
				if (_player->hp >= _player->maxHp)	_player->hp = _player->maxHp;	// 체력 최대값 예외처리
				return;
			}
		}
		//삭제 버튼을 누르면 
		if (_invenItemSlot)
		{
			if (PtInRect(&_disButton.rc, _ptMouse))
			{
				this->removeInven(_inven[_direction].imageName, 100);
				return;
			}
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

int inventory::invenNumber()
{
	// 인벤 숫자 반환하기 계산
	
	for (int i = 0; i < INVENX * INVENY; i++)
	{
		if (_inven[i].isItem) continue;
		if (!_inven[i].isItem) return i;
	}
	
	
}

int inventory::itemCount(const char* imageName)
{
	if (_mInven.size() <= 0) return 0;
	if (_mInven.count(imageName) == 0) return 0;  // 없으면 
	
	return _mInven.count(imageName);
}

bool inventory::buildRecipes(BUILDING building)
{
	if (_mInven.size() <= 0) return false;

	if (building == BUILDING::FURNACE)
	{
		if (_mInven.count("stoneDrop") == 0) return false;  // 없으면 
		if (_mInven["stoneDrop"].count >= 10)
		{
			return true;
		}
		return false;
	}
	else if (building == BUILDING::FORGE)
	{ 
		if (_mInven.count("ironingotDrop") == 0 || _mInven.count("brickDrop") == 0) return false;  // 없으면 
		if (_mInven["ironingotDrop"].count >= 4 && _mInven["brickDrop"].count >= 4)
		{
			return true;
		}
		return false;
	}
	else if (building == BUILDING::SEWING_STATION)
	{
		if (_mInven.count("woodDrop") == 0 || _mInven.count("brickDrop") == 0 || _mInven.count("fiberDrop") == 0) return false;  // 없으면 
		if (_mInven["woodDrop"].count >= 4 && _mInven["brickDrop"].count >= 4 && _mInven["fiberDrop"].count >= 4)
		{
			return true;
		}
		return false;
	}
	else if (building == BUILDING::BRIDGE)
	{
		if (_mInven.count("woodDrop") == 0 ) return false;  // 없으면 
		if (_mInven["woodDrop"].count >= 4 )
		{
			return true;
		}
		return false;
	}
	else if (building == BUILDING::FISHTRAP)
	{
		if (_mInven.count("woodDrop") == 0 || _mInven.count("berryDrop") == 0 ) return false;  // 없으면 
		if (_mInven["woodDrop"].count >= 4  && _mInven["berryDrop"].count >= 4)
		{
			return true;
		}
		return false;
	}

	return false;
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
	else if (recipe == FURNACERECIPE::GLASS) 
	{
		if ( _mInven.count("coalDrop") == 0 || _mInven.count("sandDrop") == 0) return false;  // 없으면 
			if ( _mInven["coalDrop"].count >= 2 && _mInven["sandDrop"].count >= 1)
			{
				return true;
			}
		return false;
	}
	else if (recipe == FURNACERECIPE::BREAD) // 밀가루 추가할 예정 
	{
		if (_mInven.count("coalDrop") == 0 ) return false;  // 없으면 
		if (_mInven["coalDrop"].count >= 2 )
		{
			return true;
		}
		return false;
	}
	else if (recipe == FURNACERECIPE::FISH) 
	{
		if (_mInven.count("coalDrop") == 0 || _mInven.count("fishDrop") == 0) return false;  // 없으면 
		if (_mInven["coalDrop"].count >= 2 && _mInven["fishDrop"].count >=1)
		{
			return true;
		}
		return false;
	}
	else if (recipe == FURNACERECIPE::MEAT) // meat 추가할 예정 
	{
		if (_mInven.count("coalDrop") == 0 || _mInven.count("meatDrop") == 0) return false;  // 없으면 
		if (_mInven["coalDrop"].count >= 2 && _mInven.count("meatDrop") >= 1)
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
	else if (recipe == FORGERECIPE::KEY)
	{
		//key 값을 찾아내는 방법 
		// count 함수  -> 0이면 
		// find 함수 있는지 확인  find == m.end() 없는것
		if (_mInven.count("goldingotDrop") == 0 || _mInven.count("ironingotDrop") == 0) return false;  // 없으면 
		if (_mInven["goldingotDrop"].count >= 2 && _mInven["ironingotDrop"].count >= 4)
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
		if (_mInven.count("ironingotDrop") == 0 || _mInven.count("jellyDrop") == 0) return false;  // 젤리 추가 예정  
		if (_mInven["ironingotDrop"].count >= 20 && _mInven.count("jellyDrop") >= 20)
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


