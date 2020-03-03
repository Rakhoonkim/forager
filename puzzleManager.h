#pragma once
#include "stdafx.h"
#include "puzzle.h"
#include "gameNode.h"

class puzzleManager : public gameNode
{
private:
	vector<puzzle*>			   _vPuzzle;
	vector<puzzle*>::iterator _viPuzzle;

	puzzle*					 _druidTree;			// ����̵��� ��
	puzzle*					   _rainbow;		    // ������
	framePuzzle*		 _treasureChest;			// ��������
	templeEntrance* _fireTempleEntrance;			// �����Ա�

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

