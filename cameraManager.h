#pragma once
#include "singletonBase.h"

// 200116 카메라 매니저 작성중 
struct tagCamera
{
	HDC hdc;
	image* image;
	float cameraX, cameraY;
	float cameraCenterX, cameraCenterY;
	float cameraSizeX, cameraSizeY;
	float cameraWorldSizeX, cameraWorldSizeY;
	float cameraAngle;
	float cameraSpeed;
};
class cameraManager : public singletonBase<cameraManager>
{

private:
	tagCamera _worldCamera;
	tagCamera _mapToolCamera;

	RECT _worldRect;
	bool _cameraMove;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	// 카메라 접근자 
	tagCamera getWorldCamera()		{ return _worldCamera; }
	tagCamera getMapToolCamera()	{ return _mapToolCamera; }

	//월드 카메라 
	void setCameraSizeXY(float x, float y);
	void setCameraXY(int x, int y);
	void setCameraXY(float x, float y);
	void setCameraInit(float x, float y);
	void setCameraMapToolXY(int x, int y);
	
	void ColiisionWorldCamera();
	// 맵툴 카메라 
	void setMapToolCameraXY(float x, float y);

	HDC getWorldDC()	 { return _worldCamera.hdc; }
	HDC getMapToolDC()	 { return _mapToolCamera.hdc; }

	image* getMapToolImage() { return _mapToolCamera.image; }
	image* getWorldImage() { return _worldCamera.image; }

	RECT getWorldRect() { return _worldRect; }

	void MapToolCameraRectUpdate();

};

