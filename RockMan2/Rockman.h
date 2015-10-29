#pragma once

#include "GameObject.h"
#include "Input.h"
class CRockman : public CDynamicObject
{
private:

public:
	int init() override;
	void updateInput(CInput* input);
	void update(CGameTime* gametime) override;
	void render(CGameTime* gametime, CGraphic* graphic) override;
	CRockman();
	~CRockman();
};

