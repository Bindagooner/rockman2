#pragma once
//-----------------------------------------------------------------------------
// File: GameObject.h
//
// Desc: Định nghĩa lớp CObject, đây là lớp căn bản cho tất cả các đối tượng
//		 trong game
//
//-----------------------------------------------------------------------------
#ifndef _COBJECT_H_
#define _COBJECT_H_

#include <string.h>
#include <iostream>
#include "Collision.h"
#include "DSUtil.h"
#include "Global.h"
#include "GameTime.h"
#include "Graphic.h"
#include "Camera.h"
#include "Texture.h"
#include "Sprite.h"
#include "ResourceManager.h"

using namespace std;

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

	//-----------------------------------------------------------------------------
	// 	Khởi tạo tất cả các thành phần của 1 đối tượng với các giá trí đã có
	//	
	//	Trả về 0 nếu lối hoặc 1 nếu thành công
	//-----------------------------------------------------------------------------
	virtual int init() = 0;

	//-----------------------------------------------------------------------------
	// 	Vẽ tất cả các thành phần của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//	+ graphics	: cọ vẽ đối tượng
	//-----------------------------------------------------------------------------
	virtual void render(CGameTime* gameTime, CGraphic* graphic) = 0;

	//-----------------------------------------------------------------------------
	// 	Cập nhật tất cả các logic của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//-----------------------------------------------------------------------------
	virtual void update(CGameTime* gameTime) = 0;

	//-----------------------------------------------------------------------------
	// Lấy box, nhằm xét va chạm đối tượng
	//-----------------------------------------------------------------------------
	virtual void updateBox();

	//-----------------------------------------------------------------------------
	// Lấy khung hình chữ nhật bao đối tượng
	//-----------------------------------------------------------------------------
	Rect getBoundingRectangle();

	//Lấy vị trí của đối tượng tính tại tâm
	Vector2 getPositionCenter();

	Box getBox();

	Vector2 _position;	// Vị trí vẽ đối tượng

	Vector2	_origin;	// Vị trí tâm vẽ đối tượng

	Vector2	_size;		// Kích thước đối tượng

	int _id; // id của tối tượng
	int _idType; // id type của đối tượng

protected:
	Box _box;
	CTexture	_border;
};

/*
 lớp đối tượng tĩnh
*/
class CStaticObject : public CGameObject
{
public:
	CTexture _texture; // giữ hình của đối tượng
	CStaticObject();
	~CStaticObject();
};

/*
lớp định nghĩa đối tượng động
*/
class CDynamicObject : public CGameObject
{
public:
	CDynamicObject();
	virtual ~CDynamicObject();

	Vector2 _v; // vận tốc đối tượng
	Vector2 _a; // gia tốc đối tượng
	int _hp;	// health point
	int _dam;	// damage

	CSprite _sprite; // sprite giữ hình đối tượng

	int _statusSprite; // trạng thái đối tượng
};

#endif //_COBJECT_H_