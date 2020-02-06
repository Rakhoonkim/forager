#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
	}

	return S_OK;
}

void keyManager::release()
{
}

bool keyManager::isOnceKeyDown(int key)
{
	//��� Ű�� ��������
	if (GetAsyncKeyState(key) & 0x8000)
	{
		//���࿡ �� Ű�� ���������� �ʴٸ�
		if (!this->getKeyDown()[key])
		{
			//�������ٰ� ��ȣ�� ������
			this->setKeyDown(key, true);

			return true;
		}
	}
	else this->setKeyDown(key, false);

	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) this->setKeyUp(key, true);
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);

			return true;
		}
	}
	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}

bool keyManager::isOnceTwoDown(int key1, int key2)
{
	if ((GetAsyncKeyState(key1) & 0x8000)&& (GetAsyncKeyState(key2) & 0x8000))
	{
		//���࿡ �� Ű�� ���������� �ʴٸ�
		if ((!this->getKeyDown()[key1]) && (!this->getKeyDown()[key2]))
		{
			//�������ٰ� ��ȣ�� ������
			this->setKeyDown(key1,key2,true);

			return true;
		}
	}
	return false;
}

bool keyManager::isStayTwoDown(int key1, int key2)
{
	if ((GetAsyncKeyState(key1) & 0x8000) && (GetAsyncKeyState(key2) & 0x8000)) return true;

	return false;
}