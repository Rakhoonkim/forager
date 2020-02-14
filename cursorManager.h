#pragma once
#include "singletonBase.h"
#include "cursor.h"

class cursorManager : public singletonBase<cursorManager>
{

private:
	cursor*			  _cursor;  // 커서 
	cursorBasic* _cursorBasic;  // 기본이미지 
	cursorPoint* _cursorPoint;	// 포인트 이미지 
	cursorBuild* _cursorBuild;
	cursorFarming* _cursorFarming;
public:

	cursorManager();
	~cursorManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void imageSetting();

	void setCropsPoint();
	void setBuildPoint();
	void setBridgePoint();
	void setCursor();

	cursor* getCursor(){ return _cursor; }
};

