#pragma once
//-----------------------------------------------------------------------------
// File: CGameTime.h
//
// Desc: Định nghĩa lớp CGameTime, đối tượng này quản lý thời gian của game
//-----------------------------------------------------------------------------
#ifndef _CGAME_TIME_H_
#define _CGAME_TIME_H_

#include <Windows.h>

//Số khung hình được vẽ trong một giây
#define FRAME_PER_SECOND		30

class CGameTime{
public:
	CGameTime(int framePerSecond);
	~CGameTime();

	//-----------------------------------------------------------------------------
	// Phương thức cập nhật thời gian chạy chương trình
	//-----------------------------------------------------------------------------
	void update();

	//-----------------------------------------------------------------------------
	// Lấy khoảng thời gian chênh lệch giữa hai khung hình hiện thời
	// Đơn vị: (tick)
	//-----------------------------------------------------------------------------
	int getDeltaTime();

	//-----------------------------------------------------------------------------
	// Cho phép kiểm tra có thể chuyền frame được hay chưa
	//-----------------------------------------------------------------------------
	bool isAvailableNextFrame();

	//-----------------------------------------------------------------------------
	// Cho phép kiểm tra có thể chuyền frame được hay chưa
	//-----------------------------------------------------------------------------
	void reset();

private:
	DWORD _deltaTime;
	DWORD _deltaTimePrevious;
	DWORD _startTime;
	DWORD _tickPerFrame;
	bool _availableNextFrame;
};

#endif //!_CGAME_TIME_H_