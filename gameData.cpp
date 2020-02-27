#include "stdafx.h"
#include "gameData.h"
#include "objectManager.h"

gameData::gameData()
{
}

gameData::~gameData()
{
}

HRESULT gameData::init()
{
	return S_OK;
}

void gameData::release()
{
}

void gameData::update()
{
}

void gameData::render()
{
}

void gameData::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("playerInfo.txt", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _playerManager, sizeof(_playerManager), &write, NULL);
	WriteFile(file, _objectManager, sizeof(_objectManager), &write, NULL);


	CloseHandle(file);
}

void gameData::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("playerInfo.txt", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//맵을 불로온 직후 타일의 속성을 매겨준다
	ReadFile(file, _playerManager, sizeof(_playerManager), &read, NULL);
	ReadFile(file, _objectManager, sizeof(_objectManager), &read, NULL);
	CloseHandle(file);
}
