#include "Block.h"


CBlock::CBlock() : CStaticObject()
{

}

CBlock::~CBlock()
{

}

int CBlock::init()
{
	updateBox();
	return 0;
}

void CBlock::render(CGameTime* gametime, CGraphic* graphic)
{
	//CGameObject::render(gametime, graphic);
}

void CBlock::update(CGameTime* gameTime)
{

}

void CBlock::updateBox()
{
	_box.x = _position.x - _size.x / 2;
	_box.y = _position.y + _size.y / 2;
	_box.vX = 0;
	_box.vY = 0;
	_box.width = _size.x;
	_box.height = _size.y;
}