#pragma once
#include "singletonBase.h"
#include <bitset>

#define KEYMAX 256

using namespace std;

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();

	//키를 한 번 누르면
	bool isOnceKeyDown(int key);
	//키를 눌렀다 떼면
	bool isOnceKeyUp(int key);
	//키를 누르고 있으면
	bool isStayKeyDown(int key);
	//키를 토글하면
	bool isToggleKey(int key);
	//키를 두개 한번 누르면 
	bool isOnceTwoDown(int key1, int key2);
	//키를 두개 누르고 있으면 
	bool isStayTwoDown(int key1, int key2);

	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	void setKeyDown(int key1, int key2, bool state) 
	{ 
		_keyDown.set(key1, state);
		_keyDown.set(key2, state);
	}
};

