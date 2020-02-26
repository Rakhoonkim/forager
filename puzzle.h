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


	virtual void setPuzzleXY(int x, int y)		 { _puzzle.x = x;_puzzle.y = y; }
	virtual void setPuzzleIdex(int idx, int idy) { _puzzle.idx = idx; _puzzle.idy = idy; }
	virtual void setPuzzle(PUZZLE puzzle) { _puzzle.puzzle = puzzle; }
	virtual void setTemple(TEMPLEOBJECT temple) { _puzzle.temple = temple; }

	virtual tagPuzzle* getPuzzle() { return &_puzzle;}
	virtual void setPuzzleMoveX(int x) { _puzzle.x += x; }   //x ��ŭ �̵�
	virtual void setPuzzleMoveY(int y) { _puzzle.y += y; }   //x ��ŭ �̵�
	virtual bool getRemove()		   { return  _puzzle.remove; }

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
	
};