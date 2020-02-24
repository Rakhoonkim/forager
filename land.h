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

	tagButton _land[MAXLAND];		// 총 LAND 개수 
	RECT _cameraRect;
	HDC _landDC;
	image* _landImage;

	float _cameraSpeed;
	float _landX, _landY;
	float _nextX, _nextY;

	int _playerCoin; // 플레이어의 coin
	int _direction;	 // 현재 나타내고 있는ㄱ 
	bool _isLand;   // 토지 사용중인지 아닌지 보여주는 BOOL값
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
	void landSetting(); // 초기 설정 

	bool getLand() { return _isLand; }
	void setLand(bool value) { _isLand = value; }
	void setPlayerCoin(int coin) { _playerCoin = coin; }
};

