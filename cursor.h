#pragma once
#include "stdafx.h"

class gameNode;

struct tagCursor
{
	animation* ani;
	image* image;
	float x, y;
	int idx, idy;
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
	virtual void imageChange1x1B();
	virtual void imageChange3x3();
	virtual void setCursorXY(float x, float y);
	virtual void setCursorChange();
	virtual bool getObjectPoint() { return _ObjectPoint; }
	virtual POINT getCursorIdXY() { return PointMake(_cursor.idx, _cursor.idy);}
	virtual tagCursor getCursor() { return _cursor;}
};

//기본 커서 
class cursorBasic : public cursor
{
	~cursorBasic();
	virtual void render();
	virtual void imageChange();
};

// 1x1 현재 
class cursorPoint : public cursor
{
public:
	~cursorPoint();
	virtual void render();
	virtual void imageChange();
	virtual void setCursorXY(float x, float y);
};

//2x2
class cursorBuild : public cursor
{
public:
	~cursorBuild();

	virtual void render();
	virtual void imageChange();
	virtual void imageChange1x1B();
	virtual void setCursorXY(float x, float y);
};

class cursorFarming : public cursor
{
public:
	~cursorFarming();
	virtual void render();
	virtual void imageChange();
	virtual void setCursorXY(float x, float y);
};