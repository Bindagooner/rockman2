//-----------------------------------------------------------------------------
// Copyright 2015 TAPI Solution Company
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//-----------------------------------------------------------------------------
#include "GameApp.h"

CGameApp::CGameApp(HINSTANCE hInstance, bool isFullScreen)
{
	// Khởi tạo đối tượng cửa sổ window
	if (CWindowApp::getInstance()->init(hInstance) == 0)
	{
		MessageBox(NULL, L"Lỗi không khởi tạo được cửa sổ", L"Lỗi khởi tạo", MB_OK);
		return;
	}

	HWND hwnd = CWindowApp::getInstance()->getHWND();

	// Khởi tạo các đối tượng DirectX
	if (CGraphic::getInstance()->init(hwnd) == 0)
	{
		MessageBox(NULL, L"Lỗi không khởi tạo được các đối tượng DirecX", L"Lỗi khởi tạo", MB_OK);
		return;
	}

	// Khởi tạo đối tượng đếm thời gian 
	this->_gameTime = new CGameTime(FRAME_PER_SECOND);

	//Khởi tạo Resource
	if (CResourceManager::init(hwnd) == 0)
	{
		MessageBox(NULL, L"Lỗi không khởi tạo được các đối tượng Sound", L"Lỗi khởi tạo", MB_OK);
		return;
	}

	//// Load thông tin game
	//CGameInfo::GetInstance()->Load();

	// Khởi tạo đối tượng quản lý màn hình
//	CScreenManager::getInstance()->setStartScreen(new CGameStart());

	_playScreen = new CPlayScreen();

	// Khởi tạo Keyboard
	if (CInput::getInstance()->initInput(hInstance, hwnd) == 0)
	{
		MessageBox(NULL, L"Lỗi không khởi tạo được các đối tượng Input", L"Lỗi khởi tạo", MB_OK);
		return;
	}

}


CGameApp::~CGameApp()
{
	
}

void CGameApp::Run()
{
	MSG msg;
	bool done = false;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				done = true;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		_gameTime->update();
		CInput::getInstance()->update(CWindowApp::getInstance()->getHWND());
		if (_gameTime->isAvailableNextFrame())
		{
			// chưa viết đến, từ từ tính sau
			/*CScreenManager::getInstance()->updateInput(CInput::getInstance());
			CScreenManager::getInstance()->update(_gameTime);
			CScreenManager::getInstance()->render(_gameTime, CGraphic::getInstance());*/

			_playScreen->updateInput(CInput::getInstance());
			_playScreen->update(_gameTime);
			_playScreen->render(_gameTime, CGraphic::getInstance());

			CInput::getInstance()->saveKeyStateHistory();
		}
	}
}