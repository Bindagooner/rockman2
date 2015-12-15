#pragma once

#include "GameObject.h"
#include "Input.h"
#include "RockmanBullet.h"
#include "Bullet.h"

#define GRAVITY -3.0 / 10
#define ROCKMAN_VERLOCITY_X		80.0f/1000.0f
#define ROCKMAN_VERLOCITY_Y		355.0f/1000.0f
#define ROCKMAN_ACCELERATE_X	0.5f/1000.0f
#define ROCKMAN_ACCELERATE_Y	1.09f/1000.0f

enum Status
{
	Stand,
	Stand_fire,
	Run,
	Run_fire,
	Jump,
	Jump_fire,
	Stair,
	Stair_end,
	Stair_fire,
	Fall,
	Hurt_in_air,
};

class CRockman : public CDynamicObject
{
private:
	
	bool _isRight; // hướng quay mặt trái phải rockman
	bool _isFiring;
	

	int _deltaJump;
	
	CDirection			_changeScreenDirection;

	vector<CBullet*> _bullets;
	void fire();

public:
	Status _status; // trạng thái rockman

	int init() override;
	void updateSprite();
	void updateBox();
	void updateInput(CGameTime* gametime, CInput* input);
	void update(CGameTime* gametime) override;
	void render(CGameTime* gametime, CGraphic* graphic) override;
	
	void changeScreen(CDirection direction);

	vector<CBullet*> getBullets();

	CRockman();
	~CRockman();
};

