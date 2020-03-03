#include "stdafx.h"
#include "Zorder.h"
#include "player.h"
#include "puzzle.h"
#include "enemy.h"
#include "crops.h"
#include "building.h"

Zorder::Zorder()
{
}

Zorder::~Zorder()
{
}

HRESULT Zorder::init()
{
	return S_OK;
}

void Zorder::release()
{
	_vZOrder.clear();
}

void Zorder::update()
{
	//for (int i = 0; i < _vZOrder.size(); i++)
	//{
	//	RECT temp;
	//	if (_vZOrder[i]->zOrder->puzzle != nullptr)
	//	{
	//		if (IntersectRect(&temp, &CAMERAMANAGER->getWorldRect(), &_vZOrder[i]->zOrder->puzzle->getPuzzle()->rc))
	//		{
	//			_vZOrder[i]->zOrder->puzzle->update();
	//		}
	//	}
	//}
	_vZOrder = ZOrderUpdate(_vZOrder);
	removeObject();
}

void Zorder::render()
{
	for (int i = 0; i < _vZOrder.size(); i++)
	{
		RECT temp;
		if (_vZOrder[i]->zOrder->puzzle != nullptr)
		{
			if (IntersectRect(&temp, &CAMERAMANAGER->getWorldRect(), &_vZOrder[i]->zOrder->puzzle->getPuzzle()->rc))
			{
				_vZOrder[i]->zOrder->puzzle->render();
			}
		}
		else if (_vZOrder[i]->zOrder->player != nullptr)
		{
			_vZOrder[i]->zOrder->player->render();
		}
		else if (_vZOrder[i]->zOrder->crops != nullptr)
		{
			if (IntersectRect(&temp, &CAMERAMANAGER->getWorldRect(), &_vZOrder[i]->zOrder->crops->getCrops()->rc))
			{
				_vZOrder[i]->zOrder->crops->render();
			}
		}
		else if (_vZOrder[i]->zOrder->enemy!= nullptr)
		{
			if (IntersectRect(&temp, &CAMERAMANAGER->getWorldRect(), &_vZOrder[i]->zOrder->enemy->getEnemy()->rc))
			{
				_vZOrder[i]->zOrder->enemy->render();
			}
		}
		else if (_vZOrder[i]->zOrder->build != nullptr)
		{
			if (IntersectRect(&temp, &CAMERAMANAGER->getWorldRect(), &_vZOrder[i]->zOrder->build->getBuilding()->rc))
			{
				_vZOrder[i]->zOrder->build->render();
			}
		}
	}
}

void Zorder::addZorder(STAGEOBJECT obj, ZorderStageClass* object)
{
	if (obj == STAGEOBJECT::PLAYER)
	{
		ZorderObject* tempObject;
		tempObject = new ZorderObject;
		tempObject->zOrder = object;
		tempObject->y = &object->player->get_PlayerAddress()->y;

		_vZOrder.push_back(tempObject);
	}
}

void Zorder::addZorder(STAGEOBJECT obj, player* player, crops* crop, building* build, enemy* enemy, puzzle* puzzle)
{
	ZorderStageClass* stageClass;
	stageClass = new ZorderStageClass;
	stageClass->player = nullptr;
	stageClass->enemy = nullptr;
	stageClass->build = nullptr;
	stageClass->puzzle = nullptr;
	stageClass->crops = nullptr;

	ZorderObject* tempObject;
	tempObject = new ZorderObject;
	ZeroMemory(tempObject, sizeof(tempObject));


	if (obj == STAGEOBJECT::PLAYER)
	{
		stageClass->player = player;

		//´ëÀÔ 
		tempObject->zOrder = stageClass;
		tempObject->y = &player->get_PlayerAddress()->y;

		_vZOrder.push_back(tempObject);
	}
	else if (obj == STAGEOBJECT::PUZZLE)
	{
		stageClass->puzzle = puzzle;

		tempObject->zOrder = stageClass;
		tempObject->y = &puzzle->getPuzzle()->centerY;

		_vZOrder.push_back(tempObject);
	}
	else if (obj == STAGEOBJECT::CROPS)
	{
		stageClass->crops = crop;

		tempObject->zOrder = stageClass;
		tempObject->y = &crop->getCrops()->y;

		_vZOrder.push_back(tempObject);
	}
	else if (obj == STAGEOBJECT::ENEMY)
	{
		stageClass->enemy = enemy;

		tempObject->zOrder = stageClass;
		tempObject->y = &enemy->getEnemy()->y;

		_vZOrder.push_back(tempObject);
	}
	else if (obj == STAGEOBJECT::BUILDING)
	{
		stageClass->build = build;

		tempObject->zOrder = stageClass;
		tempObject->y = &build->getBuilding()->centerY;

		_vZOrder.push_back(tempObject);
	}
}

vector<ZorderObject*> Zorder::ZOrderUpdate(vector<ZorderObject*> num)
{
	ZorderObject* instance = new ZorderObject;

	float i, j;
	float key;

	for (i = 1; i < num.size(); i++)
	{
		instance = num[i];
		key = (*num[i]->y);

		for (j = i - 1; j >= 0 && (*num[j]->y) > key; j--)
		{
			num[j + 1] = num[j];
		}

		num[j + 1] = instance;
	}

	return num;
}

void Zorder::removeObject()
{
	for (int i = 0; i < _vZOrder.size(); i++)
	{
		if (_vZOrder[i]->zOrder->crops != nullptr)
		{
			if (_vZOrder[i]->zOrder->crops->getCrops()->hp <= 0)
			{
				_vZOrder.erase(_vZOrder.begin() + i);
				break;
			}
		}
		else if (_vZOrder[i]->zOrder->enemy != nullptr)
		{
			if (_vZOrder[i]->zOrder->enemy->getEnemy()->hp <= 0)
			{
				_vZOrder.erase(_vZOrder.begin() + i);
				break;
			}
		}
	}
}

