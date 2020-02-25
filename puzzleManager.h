#pragma once
#include "stdafx.h"
#include "puzzle.h"

class puzzleManager
{
private:
	vector<puzzle*>			   _vPuzzle;
	vector<puzzle*>::iterator _viPuzzle;

public:
	puzzleManager();
	~puzzleManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();

	void puzzleRemove();
	void createPuzzle(PUZZLE puz, int idx, int idy);

	vector<puzzle*> getVPuzzle()			{ return _vPuzzle ;}
	vector<puzzle*>::iterator getViPuzzle() { return _viPuzzle; }
};

