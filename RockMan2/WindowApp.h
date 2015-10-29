#pragma once
#ifndef _CWINDOW_H_
#define _CWINDOW_H_

#include <Windows.h>
#include "Global.h"

/*------------------------------------------
Sumary:	Lớp singleton tạo cửa sổ game
-------------------------------------------*/
class CWindowApp
{
public:
	~CWindowApp();

	static CWindowApp* getInstance();
	/*------------------------------------------
	Sumary:	Khởi tạo đối tượng cửa sổ ứng dụng
	Parameters:
	+ hInstance	: Thể hiện ứng dụng.
	+ isFullScreen: 0 là không full, 1 là full
	Return:
	-------------------------------------------*/
	int init(HINSTANCE hInstance);

	/*------------------------------------------
	Sumary:	Nhận thông điệp trả về từ hệ thống
	Parameters:
	+ hWnd	: Thể hiện cửa sổ ứng dụng.
	+ msg	: Thông điệp hệ thống.
	+ wParam: ???
	+ lParam: ???
	Return:	Kết quả trả về cho hệ thống.
	-------------------------------------------*/
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void setIsFullScreen(int isFullScreen);
	int getIsFullScreen();
	HINSTANCE getInstanceW();
	HWND getHWND();

protected:
	CWindowApp();

	HINSTANCE _hInstance;		// Thể hiện
	HWND _hwnd;					// Thể hiện đối tượng cửa sổ
	static CWindowApp* _pInstance;	//Biến toàn cục
};

#endif //!_CWINDOW_H_