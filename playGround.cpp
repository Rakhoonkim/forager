#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init(true);
	SCENEMANAGER->addScene("STAGE", new stageScene);
	SCENEMANAGER->addScene("MAPTOOL", new mapToolScene);

	SCENEMANAGER->changeScene("STAGE");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	SCENEMANAGER->release();
}


void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY,BLACKNESS);
	//===========================================================
	
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::D2Drender()
{
	//_gp_D2DFactory
	// _gp_RenderTarget
	_gp_RenderTarget->BeginDraw();
	_gp_RenderTarget->Clear(ColorF(0.0f, 0.08f, 1.0));
	D2D1_ELLIPSE my_region;
	my_region.point.x = 100;
	my_region.point.y = 100;
	my_region.radiusX = 50.0f;
	my_region.radiusY = 50.0f;

	ID2D1SolidColorBrush* p_yellow_brush = NULL;
	_gp_RenderTarget->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 0.0f), &p_yellow_brush);
	_gp_RenderTarget->FillEllipse(my_region, p_yellow_brush);
	p_yellow_brush->Release();
	p_yellow_brush = NULL;

	_gp_RenderTarget->EndDraw();
}
