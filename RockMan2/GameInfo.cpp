#include "GameInfo.h"

CGameInfo* CGameInfo::_instance = NULL;

CGameInfo::CGameInfo()
{
	_idLevelGame = ID_LEVEL_CUT;
	_score = 0;
	_bonusValue = 1000;
}


CGameInfo::~CGameInfo()
{
}

CGameInfo* CGameInfo::getInstance()
{
	if (_instance == NULL)
		_instance = new CGameInfo();

	return _instance;
}

void CGameInfo::setScore(int score)
{
	_score = score;
}

int CGameInfo::getScore()
{
	return _score;
}

void CGameInfo::setBonusValue(int bonusvalue)
{
	_bonusValue = bonusvalue;
}

int CGameInfo::getBonusValue()
{
	return _bonusValue;
}

void CGameInfo::setBonus(unsigned int totalBonus)
{
	_totalBonus = totalBonus;
}

int CGameInfo::getTotalBonus()
{
	return _totalBonus;
}

void CGameInfo::setLevel(int level)
{
	_idLevelGame = level;
}

int CGameInfo::getLevel()
{
	return _idLevelGame;
}