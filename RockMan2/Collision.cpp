#include "Collision.h"


Box::Box(Rect rectangle)
{
	x = rectangle.left;
	y = rectangle.top;
	width = abs(rectangle.right - rectangle.left);
	height = abs(rectangle.top - rectangle.bottom);
	vX = 0.0f;
	vY = 0.0f;
}

CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}

bool Box::intersecWith(Box box, bool acceptDiffirent)
{
	if (!acceptDiffirent)
	{
		return !(x > box.x + box.width || y < box.y - box.height || x + width<box.x || y - height>box.y);
	}
	else
	{
		return !(floor(x) > floor(box.x + box.width) || floor(y) < floor(box.y - box.height) || floor(x + width) < floor(box.x) || floor(y - height) > floor(box.y));
	}
}

Box CCollision::GetSweptBox(Box box, float frameTime)
{
	Box re;
	re.x = box.vX > 0 ? box.x : box.x - abs(box.vX)*frameTime;
	re.y = box.vY > 0 ? box.y + abs(box.vY)*frameTime : box.y;
	re.vX = box.vX;
	re.vY = box.vY;
	re.width = box.width + abs(box.vX)*frameTime;
	re.height = box.height + abs(box.vY)*frameTime;
	return re;
}

bool CCollision::AABBCheck(Box box1, Box box2)
{
	return box1.intersecWith(box2, true);
}

float CCollision::SweepAABB(Box box1, Box box2, CDirection &normalX, CDirection &normalY, float frameTime)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// Xác định các khoảng cách bắt đầu và kết thúc va chạm theo hai chiều x, y
	if (box1.vX > 0.0f)
	{
		xInvEntry = box2.x - (box1.x + box1.width);
		xInvExit = (box2.x + box2.width) - box1.x;
	}
	else
	{
		xInvEntry = (box2.x + box2.width) - box1.x;
		xInvExit = box2.x - (box1.x + box1.width);
	}
	if (box1.vY > 0.0f)
	{
		yInvEntry = (box2.y - box2.height) - box1.y;
		yInvExit = box2.y - (box1.y - box1.height);
	}
	else
	{
		yInvEntry = box2.y - (box1.y - box1.height);
		yInvExit = (box2.y - box2.height) - box1.y;
	}
	// Tính thời gian bắt đầu và kết thúc va chạm theo hai chiều x, y
	float xEntry, xExit;
	float yEntry, yExit;

	if (box1.vX == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / box1.vX;
		xExit = xInvExit / box1.vX;
	}

	if (box1.vY == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / box1.vY;
		yExit = yInvExit / box1.vY;
	}
	// Tìm ra khoảng thời gian bắt đầu và kết thúc va chạm tổng hợp
	float entryTime, exitTime;

	entryTime = __max(xEntry, yEntry);
	exitTime = __min(xExit, yExit);
#pragma region Xét va chạm với các trường hợp còn lại
	// Nếu không có va chạm trong frameTime này thì trả về false
	if (entryTime > exitTime || xEntry<0.0f&&yEntry<0.0f || xEntry>frameTime || yEntry>frameTime)
	{
		// Mặc định không va chạm theo hai hướng
		normalX = CDirection::NONE_DIRECT;
		normalY = CDirection::NONE_DIRECT;

		if (box1.intersecWith(box2))
		{
			// Nếu 2 box va chạm lẫn nhau thì có thể hai box này đã dính nhau
			if (fabsf(box1.y - box1.height - box2.y) <= 2.0f
				&& !(box1.x + box1.width <= box2.x || box1.x >= box2.x + box2.width))
				normalY = CDirection::ON_DOWN;

			else if (fabsf(box1.y - (box2.y - box2.height)) <= 2.0f
				&& !(box1.x + box1.width <= box2.x || box1.x >= box2.x + box2.width))
				normalY = CDirection::ON_UP;

			else if (fabsf(box1.x + box1.width - box2.x) <= 2.0f
				&& !(box1.y - box1.height >= box2.y || box1.y <= box2.y - box2.height))
				normalX = CDirection::ON_RIGHT;

			else if (fabsf(box1.x - (box2.x + box2.width)) <= 2.0f
				&& !(box1.y - box1.height >= box2.y || box1.y <= box2.y - box2.height))
				normalX = CDirection::ON_LEFT;

			else if (!(box1.y - box1.height >= box2.y
				|| box1.y <= box2.y - box2.height
				|| box1.x + box1.width <= box2.x
				|| box1.x >= box2.x + box2.width))
				normalX = normalY = CDirection::INSIDE;
		}
		return 0;
	}
#pragma  endregion
#pragma region Nếu có va chạm xảy ra
	else
	{
		if (xEntry > yEntry)
		{
			if (box1.vX > 0.0f) // Nếu va chạm từ trái sang phải
			{
				if (!(box1.y - box1.height >= box2.y || box1.y <= box2.y - box2.height))
				{
					normalX = CDirection::ON_RIGHT;
					normalY = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.y - box1.height - box2.y) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_DOWN;
						entryTime = 0.0f;
					}
					else if (fabsf(box1.y - (box2.y - box2.height) <= 2.0f))
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_UP;
						entryTime = 0.0f;
					}
				}
			}
			else // Nếu va chạm từ phải sang trái
			{
				if (!(box1.y - box1.height >= box2.y || box1.y <= box2.y - box2.height))
				{
					normalX = CDirection::ON_LEFT;
					normalY = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.y - box1.height - box2.y) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_DOWN;
						entryTime = 0.0f;
					}
					else if (fabsf(box1.y - (box2.y - box2.height)) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_UP;
						entryTime = 0.0f;
					}
				}
			}
		}
		else
		{
			if (box1.vY > 0.0f) // Nếu va chạm từ dưới lên
			{
				if (!(box1.x + box1.width <= box2.x || box1.x >= box2.x + box2.width))
				{
					normalY = CDirection::ON_UP;
					normalX = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.x + box1.width - box2.x) <= 2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_RIGHT;
						entryTime = 0.0f;
					}
					else if (fabsf(box1.x - (box2.x + box2.width))<2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_LEFT;
						entryTime = 0.0f;
					}
				}
			}
			else // Nếu va chạm từ trên xuống
			{
				if (!(box1.x + box1.width <= box2.x || box1.x >= box2.x + box2.width))
				{
					normalY = CDirection::ON_DOWN;
					normalX = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.x + box1.width - box2.x) <= 2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_RIGHT;
						entryTime = 0.0f;
					}
					else if (fabsf(box1.x - (box2.x + box2.width))<2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_LEFT;
						entryTime = 0.0f;
					}
				}
			}
		}
		return entryTime;
	}
#pragma endregion
}