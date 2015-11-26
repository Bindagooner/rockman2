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
	_position = Vector2(20, 40);
	_status = Status::Stand;
	_isRight = true;
	return 1;
}

void CRockman::updateBox()
{
	_box.width = 16.0f;
	_box.height = 24.0f;
	_box.x = _position.x - _box.width / 2.0f;
	_box.y = _position.y + _box.height / 2.0f;
	_box.vX = _v.x;
	_box.vY = _v.y;
}

void CRockman::update(CGameTime* gametime)
{
	_v += _a;
	_position +=  _v * gametime->getDeltaTime();

	updateSprite();
	updateBox();
	_sprite.update(gametime);
}

void CRockman::updateSprite()
{
	int preSpriteStatus = _spriteStatus;
	switch (_status)
	{
	case CRockman::Stand:
		_spriteStatus = ID_ROCKMAN_STAND;
		break;
	case CRockman::Run:
		_spriteStatus = ID_ROCKMAN_RUN;
		break;
	case CRockman::Jump:
		_spriteStatus = ID_ROCKMAN_JUMP;
		break;
	default:
		break;
	}
	if (preSpriteStatus != _spriteStatus)
		_sprite = CResourceManager::getSprite(_spriteStatus);	
}

void CRockman::updateInput(CInput* input)
{
	if (input->isKeyPress(DIK_RIGHT))
	{
		_isRight = true;
		_status = CRockman::Run;
		_a.x = 1.0 / 100;
	}
	else if (input->isKeyPress(DIK_LEFT))
	{
		_isRight = false;
		_status = CRockman::Run;
		_a.x = -1.0 / 100;
	}
	else
	{
		_status = CRockman::Stand;
		_a.x = 0.0f;
		_v.x = 0;
	}
}

void CRockman::render(CGameTime* gametime, CGraphic* graphic)
{
	if (_isRight == true)
		graphic->draw(_sprite.getTexture(), _sprite.getDestinationRectangle(), _position, true);
	else
	{
		graphic->draw(_sprite.getTexture(), _sprite.getDestinationRectangle(), _position, true, SpriteEffects::FLIP_HORIZONTALLY);
	}
}