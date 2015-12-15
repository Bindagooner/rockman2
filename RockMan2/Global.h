//-----------------------------------------------------------------------------
// File: CGlobal.h
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
#define GAME_TITLE				L"Rockman"
#define SCREEN_WIDTH			256
#define SCREEN_HEIGHT			224
#define KEYBOARD_BUFFER_SIZE	1024
#define FRAME_PER_SECOND		60
#define FONT_SIZE				12
#define FONT_FAMILY				L"Game Font"
#define TILE_SIZE               32

/*
 LEVEL MÀN CHƠI
*/

#define ID_LEVEL_CUT 1
#define ID_LEVEL_GUTS 2
#define ID_LEVEL_BOOM 3

#define MAP_IMAGE_BOOM_MAN		L"Resources//Maps//boom_man_stage.bmp"
#define MAP_IMAGE_CUT_MAN		L"Resources//Maps//cut_man_stage.bmp"
#define MAP_IMAGE_GUTS_MAN		L"Resources//Maps//guts_man_stage.bmp"
#define MAP_DATA_BOOM_MAN		L"Resources//Maps//boom_man_stage.txt"
#define MAP_DATA_CUT_MAN		L"Resources//Maps//cut_man_stage.txt"
#define MAP_DATA_GUTS_MAN		L"Resources//Maps//guts_man_stage.txt"


/*
	ID SCREEN
*/

#define ID_SCREEN_PLAY 3009

// ID TYPE SPRITE
// ID ROCK MAN
#define	ID_SPRITE_ROCKMAN_STAND			100
#define ID_SPRITE_ROCKMAN_STAND_FIRE	102
#define	ID_SPRITE_ROCKMAN_RUN			103
#define ID_SPRITE_ROCKMAN_RUN_FIRE		104
#define	ID_SPRITE_ROCKMAN_JUMP			105
#define ID_SPRITE_ROCKMAN_STAIR			106
#define ID_SPRITE_ROCKMAN_STAIR_END		107
#define ID_SPRITE_ROCKMAN_STAIR_FIRE	108

//Damage bullet rockman
#define DAME_BULLET_ROCKMAN 2

// ID SPRITE DAN
#define ID_SPRITE_BULLET_ROCKMAN_NORMAL 1208

//ID Rockman bullet
#define ID_BULLET_ROCKMAN_NORMAL 4011


// ID SOUND
#define ID_EFFECT_ROCKMAN_FIRE_BULLET_NORMAL		2076

// OTHER
#define ID_FALLING_POINT 341
#define ID_ROCK          29

#endif
