//-----------------------------------------------------------------------------
// File: CGrphics.h
//
#pragma once
#ifndef _GLOBAL_
#define _GLOBAL_

#include <d3dx9.h>
#include <stdio.h>
#include <vector>
#include <dinput.h>
#include <math.h>
#include <limits>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

typedef LPDIRECT3DDEVICE9		Device;
typedef LPDIRECT3DSURFACE9		Surface;
typedef LPDIRECT3DTEXTURE9		Texture;
typedef LPD3DXSPRITE			Sprite;
typedef LPD3DXFONT				SpriteFont;
typedef LPDIRECT3D9				DirectX9;
typedef D3DXIMAGE_INFO			ImageInfo;
typedef D3DXVECTOR2				Vector2;
typedef D3DXVECTOR3				Vector3;
typedef D3DXVECTOR4				Vector4;
typedef LPDIRECTINPUT8			Input;
typedef LPDIRECTINPUTDEVICE8	InputDevice;
typedef DIDEVICEOBJECTDATA		DeviceObjectData;
typedef D3DXMATRIX				Matrix;
typedef D3DCOLOR				Color;
typedef RECT					Rect;

#define IS_FULL_SCREEN			0
#define GAME_TITLE				L"MARIO"
#define SCREEN_WIDTH			800
#define SCREEN_HEIGHT			600
#define KEYBOARD_BUFFER_SIZE	1024
#define FRAME_PER_SECOND		60
#define FONT_SIZE				12
#define FONT_FAMILY				L"Game Font"

// ID TYPE SPRITE
// ID MARIO
#define	ID_SPRITE_MARIO_SMALL 100

#endif
