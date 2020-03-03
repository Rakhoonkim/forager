#pragma once
#include "stdafx.h"
#include "puzzle.h"
#include "gameNode.h"

class puzzleManager : public gameNode
{
private:
	vector<puzzle*>			   _vPuzzle;
	vector<puzzle*>::iterator _viPuzzle;

	puzzle*					 _druidTree;			// 드루이드의 집
	puzzle*					   _rainbow;		    // 무지개
	framePuzzle*		 _treasureChest;			// 보물상자
	templeEntrance* _fireTempleEntrance;			// 던전입구

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
	
	puzzle* getTreasureChest()		{ return _treasureChest; }
	puzzle* getDruidTree()			{ return _druidTree; }
	puzzle* getFireTempleEntrance() { return _fireTempleEntrance;}

};

