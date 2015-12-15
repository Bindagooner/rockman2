#pragma once

#include "GameObject.h"

enum BULLET_BASE_STATE
{
	EXPLODING,//Đang nổ
	FLYING,//Đang bay
	DIE//Chết
};

class CBullet : public CDynamicObject
{
public:
	CBullet(int id, int typeID, CSprite sprite, int dam, Vector2 v, Vector2 beginPosition);

	~CBullet();

	void updateBox() override;
	virtual void destroy();

	//Hàm lấy trạng thái của đạn dùng để check xem đạn đang ở đã chết hay đang nổ. Đang nổ thì không cần check va chạm, chết rồi thì không phải vẽ.
	BULLET_BASE_STATE getState();
	// Set trạng thái đạn
	void setDie();

protected:
	//Trạng thái của đạn
	BULLET_BASE_STATE _state;
};

