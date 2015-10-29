#include "PlayScreen.h"


CPlayScreen::CPlayScreen()
{
	_mario = new CMario();
	_mario->init();
}


CPlayScreen::~CPlayScreen()
{
}

void CPlayScreen::updateInput(CInput* input)
{

}

void CPlayScreen::update(CGameTime* gametime)
{

}

void CPlayScreen::render(CGameTime* gametime, CGraphic* graphic)
{
	_mario->render(gametime, graphic);
}

void CPlayScreen::loadMap()
{

}

void CPlayScreen::renderBackground(CGraphic* graphic, Rect viewport)
{

}