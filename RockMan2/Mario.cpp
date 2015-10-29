#include "Mario.h"


CMario::CMario()
{
}


CMario::~CMario()
{
}

int CMario::init()
{
	_sprite = CResourceManager::getSprite(ID_SPRITE_MARIO_SMALL);
	_position = Vector2(00, 00);
	return 1;
}

void CMario::update(CGameTime* gametime)
{

}

void CMario::updateInput(CInput* input)
{

}

void CMario::render(CGameTime* gametime, CGraphic* graphic)
{
	graphic->draw(_sprite.getTexture(), _sprite.getDestinationRectangle(), _position, true);
}