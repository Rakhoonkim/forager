#pragma once
#include "stdafx.h"
#include "puzzle.h"

class puzzleManager
{
private:
	vector<puzzle*>			   _vPuzzle;
	vector<puzzle*>::iterator _viPuzzle;
	puzzle*					 _druidTree;			// 드루이드의 집
	puzzle*					   _rainbow;
	framePuzzle*		 _treasureChest;
	templeEntrance* _fireTempleEntrance;


public:
	puzzleManager();
	~puzzleManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();

	void puzzleRemove();
	void setPuzzleIndex(PUZZLE puz, int idx, int idy);
	void setPuzzleRender(PUZZLE puz);
	void setTempleIndex(TEMPLEOBJECT temple, int idx, int idy);
	void setTempleRender(TEMPLEOBJECT temple);
	
	puzzle* getTreasureChest() { return _treasureChest; }
	puzzle* getFireTempleEntrance() { return _fireTempleEntrance;}

};

