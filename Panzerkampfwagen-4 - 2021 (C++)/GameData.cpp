#include "GameData.h"

GameData::GameData()
{

}

GameData::~GameData()
{

}

GameData* GameData::Get_Instance()
{
	static GameData instance;
	return &instance;
}