#pragma once
#include "stdafx.h"


#define LANDX 3
#define LANDY 3

#define MAXLAND 9
#define LANDTILESIZE 40
class land
{
private:
	tagTile					_landTiles[TILEX * TILEY];

	tagButton			_land[MAXLAND];  //LAND 
	RECT				   _cameraRect;	 //LAND RECT
	HDC						   _landDC;	 //LAND DC
	image*					_landImage;  //LADN IMAGE

	float _cameraSpeed;			//카메라 스피드
	float _landX, _landY;		//(X,Y)
	float _nextX, _nextY;		//(nextX, nextY)

	int		_playerCoin; // 플레이어 COIN
	int		 _direction; // 현재 나타내고 있는지  
	bool	    _isLand; // 토지 사용중인지 아닌지 보여주는 BOOL값
public:
	land();
	~land();

	HRESULT init();
	void release();
	void update();

	void MapLoad(const char* fileName);	 // Map로드

	void render(HDC hdc);

	void mapMove();				// Map이동
	void mapBuy(int x, int y);	// Map구매

	void landSetting();			// 초기 설정 

	bool getLand()					{ return _isLand; }    //랜드 페이지 접근자
	void setLand(bool value)		{ _isLand = value;}	   //랜드 페이지 설정자
	void setPlayerCoin(int coin)	{ _playerCoin = coin; }//플레이어 코인 
};

