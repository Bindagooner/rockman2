#include "Rockman.h"


CRockman::CRockman()
{
}


CRockman::~CRockman()
{
}

int CRockman::init()
{
	_sprite = CResourceManager::getSprite(ID_ROCKMAN_STAND);
	_position = Vector2(100, 100);
	return 1;
}

void CRockman::update(CGameTime* gametime)
{

}

void CRockman::updateInput(CInput* input)
{

}

void CRockman::render(CGameTime* gametime, CGraphic* graphic)
{
	graphic->draw(_sprite.getTexture(), _sprite.getDestinationRectangle(), _position, true);
}