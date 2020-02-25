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




	//_treasureChest.imageName = "treasureChest";
	//_treasureChest.width = IMAGEMANAGER->findImage("treasureChest")->getWidth();
	//_treasureChest.height = IMAGEMANAGER->findImage("treasureChest")->getHeight();
	//_treasureChest.width = IMAGEMANAGER->findImage("treasureChest")->getWidth();
	//_treasureChest.idx = 22;
	//_treasureChest.idy = 6;

	createPuzzle(PUZZLE::RAINBOW, 36, 16);
	createPuzzle(PUZZLE::DRUIDTREE, 4, 10);
	createPuzzle(PUZZLE::TREASURECHEST, 22, 5);

	return S_OK;
}

void puzzleManager::release()
{
}

void puzzleManager::update()
{
	for (_viPuzzle = _vPuzzle.begin(); _viPuzzle != _vPuzzle.end(); ++_viPuzzle)
	{
		(*_viPuzzle)->update();
	}
	puzzleRemove();
}

void puzzleManager::render()
{
	for (_viPuzzle = _vPuzzle.begin(); _viPuzzle != _vPuzzle.end(); ++_viPuzzle)
	{
		(*_viPuzzle)->render();
	}


	/*IMAGEMANAGER->findImage("rainBow")->render(CAMERAMANAGER->getWorldDC(), _rainBow.x, _rainBow.y);
	IMAGEMANAGER->findImage("druidTree")->render(CAMERAMANAGER->getWorldDC(), _druidTree.rc.left, _druidTree.rc.top);
	*///IMAGEMANAGER->findImage("druidTree")->render(CAMERAMANAGER->getWorldDC(),)
	//Rectangle(CAMERAMANAGER->getWorldDC(), _druidTree.rc);
}

void puzzleManager::imageSetting()
{
	IMAGEMANAGER->addImage("rainBow", "./image/puzzle/rainbow.bmp", 216, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("druidTree", "./image/puzzle/druidTree.bmp", 471, 446, true, RGB(255, 0, 255),true);

	IMAGEMANAGER->addFrameImage("treasureChest", "./image/puzzle/treasureChest.bmp", 768, 126, 8, 1, true, RGB(255, 0, 255));
	KEYANIMANAGER->addDefaultFrameAnimation("treasureChest", "treasureChest", 10, false, false);
	IMAGEMANAGER->addImage("treasureChestKey", "./image/puzzle/treasureChestKey.bmp",54, 54,true, RGB(255, 0, 255));

}

void puzzleManager::puzzleRemove()
{
	for (int i = 0;i < _vPuzzle.size(); i++)
	{
		if (_vPuzzle[i]->getRemove())
		{
			_vPuzzle.erase(_vPuzzle.begin() + i);
			break;
		}
	}
}

void puzzleManager::createPuzzle(PUZZLE puz, int idx, int idy)
{
	puzzle* tempPuzzle;
	

	if (puz == PUZZLE::RAINBOW)
	{
		tempPuzzle = new puzzle;
		tempPuzzle->init("rainBow", idx, idy);
		tempPuzzle->setPuzzle(puz);
		tempPuzzle->setPuzzleMoveX(+10);
	}
	else if (puz == PUZZLE::DRUIDTREE)
	{
		tempPuzzle = new puzzle;
		tempPuzzle->init("druidTree", idx, idy);
		tempPuzzle->setPuzzle(puz);
		tempPuzzle->setPuzzleMoveX(+10);
	}
	else if (puz == PUZZLE::TREASURECHEST)
	{
		tempPuzzle = new framePuzzle;
		tempPuzzle->init("treasureChest", idx, idy);
		tempPuzzle->setPuzzle(puz);
	}

	_vPuzzle.push_back(tempPuzzle);
}

