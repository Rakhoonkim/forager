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
	virtual void setCursorXY(float x, float y);
	virtual void setCursorChange();
	virtual bool getObjectPoint() { return _ObjectPoint; }
	virtual POINT getCursorIdXY() { return PointMake(_cursor.idx, _cursor.idy);}
	virtual tagCursor getCursor() { return _cursor;}
};

//�⺻ Ŀ�� 
class cursorBasic : public cursor
{
	~cursorBasic();
	virtual void update();
	virtual void render();
	virtual void imageChange();
};

// 1x1 ���� 
class cursorPoint : public cursor
{
public:
	~cursorPoint();

	virtual void update();
	virtual void render();
	virtual void imageChange();
	virtual void setCursorXY(float x, float y);
};