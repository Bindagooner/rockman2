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
	_position = Vector2(20, 50);
	_status = Status::Stand;
	_v = Vector2(0, 0);
	_a.x = 0;
	_a.y = 0;
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
	
	// update vị trí
	_v += _a;
	_position +=  _v * gametime->getDeltaTime();

	if (_status == Jump)
	{
		if (_position.y <= 50)
		{
			_a.y = 0;
			_v.y = 0;
			_v.x = 0;
			_position.y = 50;
			_status = Stand;
		}
		else {
			_a.y += GRAVITY;
		}
	}

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
	case CRockman::Stand_fire:
		_spriteStatus = ID_ROCKMAN_STAND_FIRE;
		break;
	default:
		break;
	}
	if (preSpriteStatus != _spriteStatus)
		_sprite = CResourceManager::getSprite(_spriteStatus);		
}

void CRockman::updateInput(CInput* input)
{
	switch (_status)
	{
	case CRockman::Stand:
		if (input->isKeyDown(DIK_RIGHT))
		{
			_isRight = true;
			_status = CRockman::Run;
			_a.x = 3.0 / 1000;
		}
		else if (input->isKeyDown(DIK_LEFT))
		{
			_isRight = false;
			_status = CRockman::Run;
			_a.x = -3.0 / 1000;
		}

		break;
	case CRockman::Run:
		if ((input->isKeyDown(DIK_RIGHT) && input->isKeyDown(DIK_LEFT))
			|| input->isKeyUp(DIK_RIGHT) || input->isKeyUp(DIK_LEFT))
		{
			_status = Stand;
			_a.x = 0;
			_v.x = 0;
		}
		break;
	case CRockman::Jump:
	case CRockman::Stand_fire:
		if (input->isKeyUp(DIK_C))
			_status = Stand;
		break;
	default:
		break;
	}

	if (input->isKeyPress(DIK_C))
	{
		_status = Stand_fire;
	}
	
	if (input->isKeyPress(DIK_X))
	{
		if (_status == CRockman::Stand || _status == CRockman::Run)
		{
			_status = CRockman::Jump;
			_a.y = 0.4f;
		}
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