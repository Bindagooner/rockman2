#include "Rockman.h"


CRockman::CRockman()
{
}


CRockman::~CRockman()
{
}

int CRockman::init()
{
	_sprite = CResourceManager::getSprite(ID_SPRITE_ROCKMAN_STAND);
	_position = Vector2(20, 50);
	_status = Status::Stand;
	_v = Vector2(0, 0);
	_a.x = 0;
	_a.y = 0;
	_deltaJump = 0;
	_isRight = true;
	_isFiring = false;
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
	updateInput(gametime, CInput::getInstance());
	
	
	// update vị trí
	_v += _a;
	_position += _v * gametime->getDeltaTime();

	updateSprite();
	updateBox();
	_sprite.update(gametime);
	
}

void CRockman::updateInput(CGameTime* gametime, CInput* input)
{
	switch (_status)
	{
	case Status::Stand:
		if (input->isKeyPress(DIK_RIGHT))
		{
			_isRight = true;
			_status = Status::Run;
			_v.x = ROCKMAN_VERLOCITY_X;
			_a.x = ROCKMAN_ACCELERATE_X;
		}
		else if (input->isKeyPress(DIK_LEFT))
		{
			_isRight = false;
			_status = Status::Run;
			_v.x = -ROCKMAN_VERLOCITY_X;
			_a.x = -ROCKMAN_ACCELERATE_X;
		}

		if (input->isKeyDown(DIK_X))
		{
			_status = Status::Jump;
			_a.y = 0.3f;
		}

		if (input->isKeyPress(DIK_UP))
		{
			_status = Status::Stair;
			_v.y = 20.0 / 1000;
		}
		else if (input->isKeyPress(DIK_DOWN))
		{
			_status = Status::Stair;
			_v.y = -20.0 / 1000;
		}
		
		if (input->isKeyDown(DIK_C) && !_isFiring)
		{
			_status = Stand_fire;
			fire();
			_isFiring = true;
		}
		break;
	case Status::Stand_fire:
		if (input->isKeyUp(DIK_C) && _isFiring)
		{
			_status = Stand;
			_isFiring = false;
		}
		break;
	case Status::Run:
		if (input->isKeyUp(DIK_RIGHT) || input->isKeyUp(DIK_LEFT))
		{
			_status = Stand;
			_v.x = _a.x = 0.0f;
		}
		if (input->isKeyDown(DIK_X))
		{
			_status = Status::Jump;
			_a.y = 0.4f;
		}
		if (input->isKeyDown(DIK_C) && !_isFiring)
		{
			_status = Run_fire;
			fire();
			_isFiring = true;
		}
		break;
	case Status::Run_fire:
		if (input->isKeyUp(DIK_C) && _isFiring)
		{
			_isFiring = false;
			_status = Run;
		}
		else if (input->isKeyDown(DIK_C))
		{
			_status = Run_fire;
			fire();
		}
		else if (input->isKeyPress(DIK_C) && _isFiring)
		{
			_status = Run;
			_isFiring = false;
		}
		break;
	case Status::Stair:
		_sprite.setAllowAnimate(0);
		if (input->isKeyUp(DIK_UP) || input->isKeyUp(DIK_DOWN))
		{
			_v.y = 0;
			_sprite.setAllowAnimate(0);
		}
		else if (input->isKeyPress(DIK_UP))
		{
			_v.y = 20.0 / 1000;
			_sprite.setAllowAnimate(120);
		}
		else if (input->isKeyPress(DIK_DOWN))
		{
			_v.y = -20.0 / 1000;
			_sprite.setAllowAnimate(120);
		}
		if (input->isKeyPress(DIK_RIGHT))
		{
			_isRight = true;
		}
		else if (input->isKeyPress(DIK_LEFT))
		{
			_isRight = false;
		}
		if (input->isKeyDown(DIK_C))
		{
			_status = Status::Stair_fire;
			fire();
		}
		break;
	case Status::Stair_fire:
		if (input->isKeyDown(DIK_C))
		{
			fire();
		}
		else if (input->isKeyUp(DIK_C))
		{
			_status = Stair;
		}
		break;
	case Status::Jump:
		if (input->isKeyPress(DIK_X))
		{
			_deltaJump += gametime->getDeltaTime();
			if (_deltaJump >= 50)
			{
				_a.y = GRAVITY;
				_deltaJump = 0;
			}
			
		}
		else if (input->isKeyUp(DIK_X))
		{
			_a.y = GRAVITY;
		}
		break;
	
	default:
		break;
	}

}

void CRockman::updateSprite()
{
	int preSpriteStatus = _spriteStatus;
	switch (_status)
	{
	case Status::Stand:
		_spriteStatus = ID_SPRITE_ROCKMAN_STAND;
		break;
	case Status::Stand_fire:
		_spriteStatus = ID_SPRITE_ROCKMAN_STAND_FIRE;
		break;
	case Status::Run:
		_spriteStatus = ID_SPRITE_ROCKMAN_RUN;
		break;
	case Status::Run_fire:
		_spriteStatus = ID_SPRITE_ROCKMAN_RUN_FIRE;
		break;
	case Status::Jump:
		_spriteStatus = ID_SPRITE_ROCKMAN_JUMP;
		break;
	case Status::Stair:
		_spriteStatus = ID_SPRITE_ROCKMAN_STAIR;
		break;
	case Status::Stair_end:
		_spriteStatus = ID_SPRITE_ROCKMAN_STAIR_END;
		break;
	case Status::Stair_fire:
		_spriteStatus = ID_SPRITE_ROCKMAN_STAIR_FIRE;
		break;
	default:
		break;
	}
	if (preSpriteStatus != _spriteStatus)
		_sprite = CResourceManager::getSprite(_spriteStatus);		
}

void CRockman::fire()
{
	if (_isRight)
		_bullets.push_back(new CRockmanBullet(Vector2(2 * ROCKMAN_VERLOCITY_X, 0), _position + Vector2(12, 0)));
	else
		_bullets.push_back(new CRockmanBullet(Vector2(-2 * ROCKMAN_VERLOCITY_X, 0), _position - Vector2(12, 0)));
	CResourceManager::playASound(ID_EFFECT_ROCKMAN_FIRE_BULLET_NORMAL);
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

vector<CBullet*> CRockman::getBullets(){
	return _bullets;
}

void CRockman::changeScreen(CDirection direction)
{
	switch (direction)
	{
	case ON_UP:
		_changeScreenDirection = direction;
	case ON_DOWN:
		_v.x *= 0.01f;
		_v.y *= 0.01f;
		_a.x *= 0.01f;
		_a.y *= 0.01f;
		_changeScreenDirection = direction;
		break;
	default:
		if (_status == Status::Fall)
		{
			_v.y = -ROCKMAN_VERLOCITY_Y;
			_a.y = -ROCKMAN_ACCELERATE_Y;
		}
		else if (_status == Status::Hurt_in_air)
		{
			_status == Status::Fall;
			/*_isInShield = true;
			_timeHurted = 0.0f;
			_deltaTimeInShield = 0.0f;*/
			_a.y = -ROCKMAN_ACCELERATE_Y;
		}
		else
		{
			_v.x = _v.y = _a.x = _a.y = 0.0f;
		}
		_changeScreenDirection = direction;
		break;
	}
}