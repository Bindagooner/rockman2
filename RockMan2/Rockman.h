#pragma once

#include "GameObject.h"
#include "Input.h"

#define GRAVITY -3.0 / 10

class CRockman : public CDynamicObject
{
private:
	enum Status
	{
		Stand,
		Stand_fire,
		Run,
		Jump,
	};
	bool _isRight; // hướng quay mặt trái phải rockman
	Status _status; // trạng thái rockman

public:
	int init() override;
	void updateSprite();
	void updateBox();
	void updateInput(CInput* input);
	void update(CGameTime* gametime) override;
	void render(CGameTime* gametime, CGraphic* graphic) override;
	CRockman();
	~CRockman();
};

