#include "RockmanBullet.h"


CRockmanBullet::CRockmanBullet(Vector2 v, Vector2 beginPosition, int typeID, CSprite sprite, int dam) : CBullet(0, ID_BULLET_ROCKMAN_NORMAL, sprite, dam, v, beginPosition)
{
	_box.width = _sprite.getWidth();
	_box.height = _sprite.getHeight();
	_box.x = _position.x - _box.width / 2;
	_box.y = _position.y + _box.height / 2;
	_box.vX = _box.vY = 0.0f;
}


CRockmanBullet::~CRockmanBullet()
{
}

int CRockmanBullet::init()
{
	return 1;
}

void CRockmanBullet::update(CGameTime* gametime)
{
	_position += _v*gametime->getDeltaTime();
	updateBox();
}

void CRockmanBullet::render(CGameTime* gametime, CGraphic* graphic)
{
	graphic->draw(_sprite.getTexture(), _sprite.getDestinationRectangle(), _position, true, SpriteEffects::NONE);
}