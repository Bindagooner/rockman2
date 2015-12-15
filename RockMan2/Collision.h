#pragma once

#include <limits>
#include "Global.h"

struct Box
{
	float x, y;             /* Vị trí của box */
	float width, height;    /* Chiều dài và chiều cao của box */
	float vX, vY;           /* Vận tốc của box */
	/*M+==================================================================
	Method:	    Box::Box

	Summary:	Phương thức khởi tạo của lớp box
	==================================================================-M*/
	Box(){
		Box(0, 0, 0, 0, 0, 0);
	}

	Box(float x, float y, float w, float h, float vx, float vy)
	{
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
		this->vX = vx;
		this->vY = vy;
	}

	bool intersecWith(Box box, bool acceptDiffirent = false);

	Box(Rect rectangle);
};

enum CDirection
{
	// Hướng lên
	ON_UP = 101,
	// Hướng xuống
	ON_DOWN = 102,
	// Hướng bên phải
	ON_RIGHT = 103,
	// Hướng bên trái
	ON_LEFT = 104,
	NONE_DIRECT = 105,
	// Hai vật nằm lồng trong nhau
	INSIDE = 106
};

class CCollision
{

public:

	CCollision();
	~CCollision();
	//-----------------------------------------------------------------------------
	// Phương thức tạo swept box - là khối bao tổng thể theo vận tốc di chuyển đối tượng
	//
	// + frameTime: Khoảng thời gian chuyển khung hình
	//-----------------------------------------------------------------------------
	static Box GetSweptBox(Box box, float frameTime);

	//-----------------------------------------------------------------------------
	// Hàm hỗ trợ kiểm tra đơn giản xem box1 có va chạm với box hay không
	// bao khác hay không.
	//
	// + anotherBox: Khung bao được dùng để kiểm tra

	// return: Trả về true nếu va chạm, false nếu không va chạm
	//-----------------------------------------------------------------------------
	static bool AABBCheck(Box box1, Box box2);

	//-----------------------------------------------------------------------------
	// Kiểm tra xem box1 có va chạm với box2 theo hướng nào trong 1 khoảng thời gian chuyển khung hình nhất định
	//
	// + box1: Khung bao đối tượng di chuyển 1
	// + box2: Khung bao đối tượng đứng yên 2
	// + normalX: Hướng va chạm theo chiều x
	// + normalY: Hướng va chạm theo chiều y
	// + frameTime: Khoảng thời gian chuyển khung hình
	//
	// return: Thời gian bắt đầu va chạm theo trục x hoặc y
	//-----------------------------------------------------------------------------
	static float SweepAABB(Box box1, Box box2, CDirection &normalX, CDirection &normalY, float frameTime);
};

