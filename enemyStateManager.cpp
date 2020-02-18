#include "stdafx.h"
#include "enemyStateManager.h"

enemyStateManager::enemyStateManager()
{
}

enemyStateManager::~enemyStateManager()
{
}

//enemyState* enemyStateManager::_currentState = NULL;

HRESULT enemyStateManager::init()
{
	_currentState = NULL;

	return S_OK;
}

void enemyStateManager::release()
{
	mapStateIter miState = _mState.begin();
	for (; miState != _mState.end();)
	{
		if (miState->second != NULL)
		{
			if (miState->second == _currentState) _miState->second->release();
			SAFE_DELETE(miState->second);
			miState = _mState.erase(miState);
		}
		else ++miState;
	}

	_mState.clear();
}

void enemyStateManager::update()
{
	if (_currentState) _currentState->update();
}

void enemyStateManager::render()
{
	if (_currentState) _currentState->render();
}

enemyState* enemyStateManager::addState(string stateName, enemyState* state)
{
	if (!state) return nullptr;

	_mState.insert(make_pair(stateName, state));

	return state;
}

HRESULT enemyStateManager::chanageState(string stateName)
{
	mapStateIter find = _mState.find(stateName);

	if (find == _mState.end()) return E_FAIL;
	if (find->second == _currentState) return S_OK;

	if (SUCCEEDED(find->second->init()))
	{
		if (_currentState) _currentState->release();
	
		_currentState = find->second;

		return S_OK;
	}

	return E_FAIL;
}
