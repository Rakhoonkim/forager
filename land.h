#pragma once
#include "stdafx.h"


#define LANDX 3
#define LANDY 3

#define MAXLAND 9
#define LANDTILESIZE 40
class land
{
private:
	tagTile _landTiles[TILEX * TILEY];

	tagButton _land[MAXLAND];		// �� LAND ���� 
	RECT _cameraRect;
	HDC _landDC;
	image* _landImage;

	float _cameraSpeed;
	float _landX, _landY;
	float _nextX, _nextY;

	int _playerCoin; // �÷��̾��� coin
	int _direction;	 // ���� ��Ÿ���� �ִ¤� 
	bool _isLand;   // ���� ��������� �ƴ��� �����ִ� BOOL��
public:
	land();
	~land();

	HRESULT init();
	void release();
	void update();
	void MapLoad(const char* fileName);
	void render(HDC hdc);


	void mapMove();
	void mapBuy(int x, int y);
	void landSetting(); // �ʱ� ���� 

	bool getLand() { return _isLand; }
	void setLand(bool value) { _isLand = value; }
	void setPlayerCoin(int coin) { _playerCoin = coin; }
};

