#include "Rock.h"


CRock::CRock() : CStaticObject()
{
}

CRock::~CRock()
{
}

int CRock::init()
{
	_texture = CTexture(L"Resources//Sprites//Others//rock.png", D3DCOLOR_XRGB(255, 0, 195));
	updateBox();
	return 0;
}



void CRock::render(CGameTime* gameTime, CGraphic* graphic)
{
	Rect rectBorder;
	rectBorder.left = _box.x;
	rectBorder.top = _box.y;
	rectBorder.right = _box.x + _texture.getWidth();
	rectBorder.bottom = _box.y + _texture.getHeight();

	graphic->draw(_texture.getTexture(), rectBorder, false, Vector2(_box.width / _texture.getWidth(), _box.height / _texture.getHeight()));
}



void CRock::updateBox()
{
	_box.x = _position.x - _size.x / 2;
	_box.y = _position.y + _size.y / 2;
	_box.vX = 0;
	_box.vY = 0;
	_box.width = _size.x;
	_box.height = _size.y;
}

void CRock::update(CGameTime* gameTime)
{

}