#pragma once
#include "stdafx.h"

class gameNode;

struct tagCursor
{
	animation* ani;
	image* image;
	float x, y;
};

class cursor
{
protected:
	tagCursor _cursor;
	bool _change;
	bool _ObjectPoint;
public:

	cursor();
	~cursor();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void imageChange();
	virtual void setCursorXY(float x, float y);
	virtual void setCursorChange();
	virtual bool getObjectPoint() { return _ObjectPoint; }
};

//기본 커서 
class cursorBasic : public cursor
{
	~cursorBasic();
	virtual void update();
	virtual void render();
	virtual void imageChange();
};

// 1x1 현재 
class cursorPoint : public cursor
{
public:
	~cursorPoint();

	virtual void update();
	virtual void render();
	virtual void imageChange();
	virtual void setCursorXY(float x, float y);
};