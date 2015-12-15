#pragma once

#include "Bullet.h"
class CRockmanBullet : public CBullet
{
private:
public:
	/*------------------------------------------
	Summary:	Khởi tạo đối tượng đạn thuần của Rockman
	+ v: Vận tốc của đạn, quy định hướng bay của đạn
	+ beginPosition: Vị trí bắt đầu bay của đạn
	Return:
	-------------------------------------------*/
	CRockmanBullet(Vector2 v, Vector2 beginPosition, int typeID = ID_BULLET_ROCKMAN_NORMAL, CSprite sprite = CResourceManager::getSprite(ID_SPRITE_BULLET_ROCKMAN_NORMAL), int dame = DAME_BULLET_ROCKMAN);
	~CRockmanBullet();

	int init() override;

	void render(CGameTime* gameTime, CGraphic* graphic) override;

	void update(CGameTime* gameTime) override;
};

