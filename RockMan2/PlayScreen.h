#pragma once

#include "Screen.h"
#include "ScreenManager.h"
#include <map>
#include <vector>
#include <cmath>
#include "Rockman.h"

class CPlayScreen : public CScreen
{
private:
	//-----------------------------------------------------------------------------
	// Phương thức vẽ bacground lên màn hình dựa theo khung camera di chuyển
	//-----------------------------------------------------------------------------
	void renderBackground(CGraphic* graphic, Rect viewport);

	void loadMap();

	CRockman* _rockman;
	
public:
	void updateInput(CInput* input) override;
	void update(CGameTime* gametime) override;
	void render(CGameTime *gametime, CGraphic* graphic) override;
	CPlayScreen();
	~CPlayScreen();
};

