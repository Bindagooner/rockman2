#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Input.h"
#include "GameTime.h"
#include "Graphic.h"
#include "PlayScreen.h"

class CScreenManager
{
private:
	static CScreenManager* _instance;
public:
	static CScreenManager* getInstance();
	void updateInput(CInput* input);
	void update(CGameTime* gametime);
	void render(CGameTime* gametime, CGraphic* graphic);
	CScreenManager();
	~CScreenManager();
};

