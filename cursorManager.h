#pragma once
#include "singletonBase.h"
#include "cursor.h"

class cursorManager : public singletonBase<cursorManager>
{

private:
	cursor*			  _cursor;  // Ŀ�� 
	cursorBasic* _cursorBasic;  // �⺻�̹��� 
	cursorPoint* _cursorPoint;	// ����Ʈ �̹��� 
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

