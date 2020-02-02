#pragma once
#include "singletonBase.h"

// 200116 카메라 매니저 작성중 

class cameraManager : public singletonBase<cameraManager>
{

private:
	float _cameraSizeX, _cameraSizeY;
	float _cameraX, _cameraY;

	HDC			_worldDC;
	image*	 _worldImage;


public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// 월드 사이즈 
	void setWorldSize(string strKey);
	float  getCameraSizeX() { return _cameraSizeX; }
	float  getCameraSizeY() { return _cameraSizeY; }


};

