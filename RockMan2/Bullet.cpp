#include "Bullet.h"


CBullet::CBullet(int id, int typeID, CSprite sprite, int dam, Vector2 v, Vector2 beginPosition) : CDynamicObject()
{
	_sprite = sprite;
	_v = v;
	_dam = dam;
	_id = id;
	_idType = typeID;
	_position = beginPosition;
	_state = BULLET_BASE_STATE::FLYING;
}


CBullet::~CBullet()
{
}

BULLET_BASE_STATE CBullet::getState()
{
	return _state;
}

void CBullet::updateBox()
{
	_box.vX = _v.x;
	_box.vX = _v.y;
	_box.width = _sprite.getFrameWidth() - 2;
	_box.height = _sprite.getFrameHeight() - 2;
	_box.x = _position.x - _box.width / 2;
	_box.y = _position.y + _box.height / 2;
}
void CBullet::setDie()
{
	_state = BULLET_BASE_STATE::DIE;
}

void CBullet::destroy()
{

}