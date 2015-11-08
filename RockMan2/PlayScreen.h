#pragma once

#include "ResourceManager.h"
#include "Screen.h"
#include "ScreenManager.h"
#include "Rockman.h"
#include "CameraPath.h"
#include "camera.h"
#include "GameInfo.h"
#include "QuadNode.h"
#include "SceneInfo.h"
#include "Block.h"

#include <map>
#include <vector>
#include <cmath>


class CPlayScreen : public CScreen
{
private:
	//-----------------------------------------------------------------------------
	// Phương thức vẽ bacground lên màn hình dựa theo khung camera di chuyển
	//-----------------------------------------------------------------------------
	void renderBackground(CGraphic* graphic, Rect viewport);

	void loadMap();

	void findScene(unsigned int startIndex);

	CQuadNode	_quadNodeCollision;			// Cây tứ phân lưu các đối tượng va chạm trên màn hình
	CSceneInfo              _sceneInfo;
	vector<vector<int>>		_tileMatrix;	// Ma trận lưu các tile background
	int						_countRow;		// Số lượng dòng của ma trận
	int						_countColumn;	// Số lượng cột của ma trận
	int						_totalTile;		// Tổng số tile được cắt
	CTexture _tteBackground; // đối tượng nắm giữ ảnh nền

	Vector2		_screenPosition;

	CRockman* _rockman;
	
public:
	void updateInput(CInput* input) override;
	void update(CGameTime* gametime) override;
	void render(CGameTime *gametime, CGraphic* graphic) override;
	CPlayScreen();
	~CPlayScreen();
};

