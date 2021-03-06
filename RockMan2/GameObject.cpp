#include "GameObject.h"


CGameObject::CGameObject(){
	_position = Vector2(0, 0);
	_origin = Vector2(0, 0);
	_size = Vector2(0, 0);
}

CGameObject::~CGameObject(){

}

void CGameObject::updateBox()
{
	_box.x = _position.x;
	_box.y = _position.y;
	_box.width = _size.x;
	_box.height = _size.y;
	_box.vX = 0.0f;
	_box.vY = 0.0f;
}

Box CGameObject::getBox()
{
	return _box;
}

Rect CGameObject::getBoundingRectangle(){
	Rect boundingRect;
	boundingRect.left = _position.x;
	boundingRect.top = _position.y;
	boundingRect.right = boundingRect.left + _size.x;
	boundingRect.bottom = boundingRect.top + _size.y;

	return boundingRect;
}

Vector2 CGameObject::getPositionCenter()
{
	return Vector2(_position.x/* + _origin.x*/, _position.y/* + _origin.y*/);
}

CDynamicObject::CDynamicObject() : CGameObject()
{
	_v = Vector2(0.0f, 0.0f);
	_a = Vector2(0.0f, 0.0f);
	_hp = 0;
	_dam = 0;
}

//float CDynamicObject::checkCollision(CGameObject* gameObj, float& normalX, float& normalY, float deltatime)
//{
//	float timeCollision = deltatime;
//	Box mybox = this->getBox();
//	Box objbox = gameObj->getBox();
//
//	mybox.vX -= objbox.vX;
//	mybox.vY -= objbox.vY;
//	objbox.vX = 0.0f;
//	objbox.vY = 0.0f;
//
//	Box sweptbroadphasebox = CCollision::getSweptBroadphaseBox(mybox, deltatime);
//
//	if (CCollision::checkBeforeAABB(sweptbroadphasebox, objbox))
//	{
//		timeCollision = CCollision::SweepAABB(mybox, objbox, normalX, normalY, deltatime);
//		if (timeCollision = deltatime && CCollision::checkBeforeAABB(mybox, objbox))
//			return 0;
//	}
//
//	return timeCollision;
//}


CDynamicObject::~CDynamicObject()
{

}

CStaticObject::CStaticObject() : CGameObject()
{

}

CStaticObject::~CStaticObject()
{

}