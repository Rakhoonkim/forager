#include "stdafx.h"
#include "enemyState.h"

enemyState::enemyState(tagObject* enemy)
{
	_enemy = enemy;
}

enemyState::~enemyState()
{
}

HRESULT enemyState::init()
{
	return S_OK;
}

void enemyState::update()
{
}

void enemyState::release()
{
}

void enemyState::render()
{
}
