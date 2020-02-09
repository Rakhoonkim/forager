#pragma once
#include "singletonBase.h"
#include "cursor.h"

class cursorManager : public singletonBase<cursorManager>
{

private:
	cursor*			  _cursor;  // 커서 
	cursorBasic* _cursorBasic;  // 기본이미지 
	cursorPoint* _cursorPoint;	// 포인트 이미지 
public:

	cursorManager();
	~cursorManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void imageSetting();

	void setPoint();
	void setCursor();

	cursor* getCursor(){ return _cursor; }
};

