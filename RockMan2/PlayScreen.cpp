#include "PlayScreen.h"


CPlayScreen::CPlayScreen()
{
	_rockman = new CRockman();
	_rockman->init();
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
	_rockman->render(gametime, graphic);
}

void CPlayScreen::loadMap()
{

}

void CPlayScreen::renderBackground(CGraphic* graphic, Rect viewport)
{

}