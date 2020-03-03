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

	float _cameraSpeed;			//ī�޶� ���ǵ�
	float _landX, _landY;		//(X,Y)
	float _nextX, _nextY;		//(nextX, nextY)

	int		_playerCoin; // �÷��̾� COIN
	int		 _direction; // ���� ��Ÿ���� �ִ���  
	bool	    _isLand; // ���� ��������� �ƴ��� �����ִ� BOOL��
public:
	land();
	~land();

	HRESULT init();
	void release();
	void update();

	void MapLoad(const char* fileName);	 // Map�ε�

	void render(HDC hdc);

	void mapMove();				// Map�̵�
	void mapBuy(int x, int y);	// Map����

	void landSetting();			// �ʱ� ���� 

	bool getLand()					{ return _isLand; }    //���� ������ ������
	void setLand(bool value)		{ _isLand = value;}	   //���� ������ ������
	void setPlayerCoin(int coin)	{ _playerCoin = coin; }//�÷��̾� ���� 
};

