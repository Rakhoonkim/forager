#pragma once
#include "stdafx.h"

class puzzle
{
protected: 
	tagPuzzle _puzzle;
public:
	puzzle();
	~puzzle();

	virtual HRESULT init(const char* imageName, int idx,int idy);
	virtual void release();
	virtual void update();
	virtual void render();

	//������ 
	virtual void setPuzzle(PUZZLE puzzle)		  { _puzzle.puzzle = puzzle; }              
	virtual void setTemple(TEMPLEOBJECT temple)   { _puzzle.temple = temple; }				 
	virtual void setPuzzleXY(int x, int y)		  { _puzzle.x = x; _puzzle.y = y; }         //(X,Y)
	virtual void setPuzzleIdex(int idx, int idy)  { _puzzle.idx = idx; _puzzle.idy = idy; } //(idx,idy)
	virtual void setRender()				      { _puzzle.isRender = true; }
	virtual void setAlpha(int alpha)			  { _puzzle.alpha = alpha; }
	virtual void setPuzzleMoveX(int x)			  { _puzzle.x += x; }   //x ��ŭ �̵�
	virtual void setPuzzleMoveY(int y)			  { _puzzle.y += y; }   //x ��ŭ �̵�

	//������ 
	virtual RECT getRect()				 { return _puzzle.rc; }		 //RECT
	virtual bool getRemove()			 { return _puzzle.remove; }  //����
	virtual tagPuzzle* getPuzzle()		 { return &_puzzle;}
	virtual bool getIsOpen()			 { return false; }			
};

class framePuzzle : public puzzle
{
private:
	bool _isOpen;
public:
	framePuzzle();
	~framePuzzle();

	HRESULT init(const char* imageName, int idx, int idy);
	void update();
	void render();
	bool getIsOpen() { return _isOpen; }
};

class templeEntrance : public puzzle
{
public:
	templeEntrance();
	~templeEntrance();

	void update();
	void render();
};