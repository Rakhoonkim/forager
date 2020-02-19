#include "stdafx.h"
#include "bulletManager.h"

bulletManager::bulletManager()
{
}

bulletManager::~bulletManager()
{
}

HRESULT bulletManager::init()
{
	OBJECTPOOL->Init(10000);

	_bullet = new bullet;
	_bullet->init("fireBall");

	return S_OK;
}

void bulletManager::update()
{
	_bullet->update();
}

void bulletManager::release()
{
}

void bulletManager::render()
{
	_bullet->render();
}

