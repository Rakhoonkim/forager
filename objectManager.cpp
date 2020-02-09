#include "stdafx.h"
#include "objectManager.h"

objectManager::objectManager()
{
}

objectManager::~objectManager()
{
}

HRESULT objectManager::init()
{
	_cropsManager = new cropsManager;
	_cropsManager->init();

	return S_OK;
}

void objectManager::release()
{
	_cropsManager->release();
}

void objectManager::update()
{
	_cropsManager->update();
}

void objectManager::render()
{
	_cropsManager->render();
}
