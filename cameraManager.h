#pragma once
#include "singletonBase.h"

// 200116 ī�޶� �Ŵ��� �ۼ��� 
struct tagCamera
{
	HDC hdc;
	image* image;
	float cameraX, cameraY;
	float cameraSizeX, cameraSizeY;
	float cameraWorldSizeX, cameraWorldSizeY;
};
class cameraManager : public singletonBase<cameraManager>
{

private:
	tagCamera _worldCamera;
	tagCamera _mapToolCamera;


public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// ī�޶� ������ 
	tagCamera getWorldCamera()		{ return _worldCamera; }
	tagCamera getMapToolCamera()	{ return _mapToolCamera; }

	//���� ī�޶� 
	void setCameraSizeXY(float x, float y);
	void setCameraXY(int x, int y);
	void setCameraXY(float x, float y);

	void setCameraMapToolXY(int x, int y);
	

	// ���� ī�޶� 
	void setMapToolCameraXY(float x, float y);

	HDC getWorldDC()	 { return _worldCamera.hdc; }
	HDC getMapToolDC()	 { return _mapToolCamera.hdc; }

	image* getMapToolImage() { return _mapToolCamera.image; }
	image* getWorldImage() { return _worldCamera.image; }

};

