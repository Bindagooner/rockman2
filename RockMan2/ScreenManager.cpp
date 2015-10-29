#include "ScreenManager.h"

CScreenManager* CScreenManager::_instance = NULL;

CScreenManager::CScreenManager()
{
}


CScreenManager::~CScreenManager()
{
}

void CScreenManager::update(CGameTime* gametime)
{

}

void CScreenManager::updateInput(CInput* input)
{

}

void CScreenManager::render(CGameTime* gametime, CGraphic* graphic)
{

}

CScreenManager* CScreenManager::getInstance()
{
	if (_instance == NULL)
		_instance = new CScreenManager();
	return _instance;

}