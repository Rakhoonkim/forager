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

	_buildManager = new buildManager;
	_buildManager->init();

	UIMANAGER->buildAdressLink(_buildManager);
	return S_OK;
}

void objectManager::release()
{
	_cropsManager->release();
	_buildManager->release();
}

void objectManager::update()
{
	_cropsManager->update();
	_buildManager->update();
}

void objectManager::render()
{
	_cropsManager->render();
	_buildManager->render();
}
