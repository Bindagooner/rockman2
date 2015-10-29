#pragma once
#include <dinput.h>
#include "Global.h"
#include "Trace.h"

class CInput
{
public:
	~CInput();

	//===================================================
	static CInput* getInstance();

	// Khởi tạo Input
	int initInput(HINSTANCE hInstance, HWND hwnd);

	// Update KeyState từ KeyEvents
	void update(HWND hWnd);
	// Lấy trạng thái bàn phím có được kích hoạt hay không? Nếu không thì kích hoạt
	void saveKeyStateHistory();

	int isKeyDown(int keyCode);

	int isKeyUp(int keyCode);

	int isKeyPress(int keyCode);

	int isKeyRelease(int keyCode);

	// Hủy đối tượng bàn phím và dữ liệu bộ đệm
	void releaseKeyboard();

	void active();

	void deactive();

private:
	CInput();

	//=========Phương thức===============================

	// Khởi tạo Direct Input
	int initInputDirect(HINSTANCE hInstance);

	// Khởi tạo bàn phím
	int initKeyboard(HWND hWnd);


	// Lấy trạng thái phím với "key"
	BYTE getKeyState(int keyCode);

	//=========Thuộc tính================================

	static CInput* _pInstance;

	// Đối tượng DirectInput 
	LPDIRECTINPUT8 _directInput;

	// Bàn phím 
	LPDIRECTINPUTDEVICE8 _keyBoard;

	// Bộ đệm trạng thái của bàn phím DirectInput 
	BYTE  _keyStates[256];

	// Bộ đệm trạng thái của bàn phím DirectInput 
	BYTE  _preKeyStates[256];

	bool  _isActive;
};

