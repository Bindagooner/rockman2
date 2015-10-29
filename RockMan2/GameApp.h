#pragma once
#ifndef _CGAMEAPP_H_
#define _CGAMEAPP_H_

#include "WindowApp.h"
#include "Graphic.h"
#include "Input.h"
#include "global.h"
#include "GameTime.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

class CGameApp
{
public:
	//-----------------------------------------------------------------------------
	// Create a game application instance
	//
	// + hIntance: Instance of game
	// + fullScreenMode: Default value if FULL_SCREEEN_MODE
	//
	//-----------------------------------------------------------------------------
	CGameApp(HINSTANCE hInstance, bool isFullScreen = IS_FULL_SCREEN);

	//-----------------------------------------------------------------------------
	// Initiate  all necessary objects
	//
	//-----------------------------------------------------------------------------
	//bool Init();

	~CGameApp();

	//-----------------------------------------------------------------------------
	// Runs game. This function run the main game lood
	//
	//-----------------------------------------------------------------------------
	void Run();

private:
	HINSTANCE		_hInstance;
	bool			_isFullScreen;
	CGameTime*		_gameTime;

	CPlayScreen *_playScreen;
	/*CWindowApp*		_gameWindow;
	CInput*			_input;
	CGraphic*		_graphics;
	CScreenManager*	_screenManager;*/
};

#endif
