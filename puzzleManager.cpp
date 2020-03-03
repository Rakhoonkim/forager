#include "stdafx.h"
#include "puzzleManager.h"

puzzleManager::puzzleManager()
{
}

puzzleManager::~puzzleManager()
{
}

HRESULT puzzleManager::init()
{
	imageSetting();

	_rainbow = new puzzle;
	_rainbow->init("rainBow", 0, 0);
	_rainbow->setPuzzle(PUZZLE::RAINBOW);
	_rainbow->setPuzzleMoveX(-5);

	_druidTree = new puzzle;
	_druidTree->init("druidTree", 0, 0);
	_druidTree->setPuzzle(PUZZLE::DRUIDTREE);

	_treasureChest = new framePuzzle;
	_treasureChest->init("treasureChest", 0, 0);
	_treasureChest->setPuzzle(PUZZLE::TREASURECHEST);

	_fireTempleEntrance = new templeEntrance;
	_fireTempleEntrance->init("fireTempleEntrance", 0, 0);
	_fireTempleEntrance->setTemple(TEMPLEOBJECT::TEMPLE_ENTRANCE);

	//제트오더에 넣는다.
	ZORDER->addZorder(STAGEOBJECT::PUZZLE, NULL, NULL, NULL, NULL, _rainbow);
	ZORDER->addZorder(STAGEOBJECT::PUZZLE, NULL, NULL, NULL, NULL, _druidTree);
	ZORDER->addZorder(STAGEOBJECT::PUZZLE, NULL, NULL, NULL, NULL, _treasureChest);
	ZORDER->addZorder(STAGEOBJECT::PUZZLE, NULL, NULL, NULL, NULL, _fireTempleEntrance);


	_vPuzzle.push_back(_rainbow);
	_vPuzzle.push_back(_druidTree);
	_vPuzzle.push_back(_treasureChest);
	_vPuzzle.push_back(_fireTempleEntrance);
	return S_OK;
}

void puzzleManager::release()
{
}

void puzzleManager::update()
{
	vector<puzzle*>::iterator iter;
	iter = _vPuzzle.begin();
	for (; iter != _vPuzzle.end(); iter++)
	{
		if (!(*iter)->getPuzzle()->isRender) continue;
		(*iter)->update();
	}
}

void puzzleManager::render()
{
	//vector<puzzle*>::iterator iter;
	//iter = _vPuzzle.begin();
	//for (; iter != _vPuzzle.end(); iter++)
	//{
	//	if (!(*iter)->getPuzzle()->isRender) continue;
	//	(*iter)->render();
	//}
}

void puzzleManager::imageSetting()
{
	IMAGEMANAGER->addImage("rainBow", "./image/puzzle/rainbow.bmp", 216, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("druidTree", "./image/puzzle/druidTree.bmp", 471, 446, true, RGB(255, 0, 255),true);

	IMAGEMANAGER->addFrameImage("treasureChest", "./image/puzzle/treasureChest.bmp", 768, 126, 8, 1, true, RGB(255, 0, 255));
	KEYANIMANAGER->addDefaultFrameAnimation("treasureChest", "treasureChest", 10, false, false);
	IMAGEMANAGER->addImage("treasureChestKey", "./image/puzzle/treasureChestKey.bmp",54, 54,true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("fireTempleEntrance", "./image/puzzle/fireTempleEntrance.bmp", 288, 336, true, RGB(255, 0, 255),true);
}

void puzzleManager::setPuzzleIndex(PUZZLE puz, int idx, int idy)
{
	if (puz == PUZZLE::RAINBOW)
	{
		_rainbow->setPuzzleIdex(idx,idy);
	}
	else if (puz == PUZZLE::DRUIDTREE)
	{
		_druidTree->setPuzzleIdex(idx, idy);
	}
	else if (puz == PUZZLE::TREASURECHEST)
	{
		_treasureChest->setPuzzleIdex(idx, idy);
	}
}

void puzzleManager::setPuzzleRender(PUZZLE puz)
{
	if (puz == PUZZLE::RAINBOW)
	{
		_rainbow->setRender();
	}
	else if (puz == PUZZLE::DRUIDTREE)
	{
		_druidTree->setRender();
	}
	else if (puz == PUZZLE::TREASURECHEST)
	{
		_treasureChest->setRender();
	}
}

void puzzleManager::setTempleIndex(TEMPLEOBJECT temple, int idx, int idy)
{
	if (temple == TEMPLEOBJECT::TEMPLE_ENTRANCE)
	{
		_fireTempleEntrance->setPuzzleIdex(idx, idy);
	}
}

void puzzleManager::setTempleRender(TEMPLEOBJECT temple)
{
	_fireTempleEntrance->setRender();
}



