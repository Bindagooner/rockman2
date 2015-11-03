#include "Camera.h"

CCamera* CCamera::_instance = NULL;

CCamera::CCamera()
{
	D3DXMatrixIdentity(&_matrixTransform);
	_matrixTransform._22 = -1;
	this->setCamPosition(D3DXVECTOR2(0, (float)SCREEN_HEIGHT));
}


CCamera::~CCamera()
{
	if (_instance != NULL) _instance == NULL;
}

CCamera* CCamera::getInstance()
{
	if (_instance == NULL)
		_instance = new CCamera();
	return _instance;
}

void CCamera::setCamPosition(D3DXVECTOR2 pos, bool isFollow)
{
	_camPosition = pos;
	// xac dinh ma tran bien doi
	_matrixTransform._41 = -_camPosition.x;
	_matrixTransform._42 = _camPosition.y;
}

D3DXVECTOR2 CCamera::transform(D3DXVECTOR2 pos)
{
	D3DXVECTOR4 result;	
	D3DXVec3Transform(&result, &D3DXVECTOR3(pos.x, pos.y, 0.0f), &_matrixTransform);
	return D3DXVECTOR2(static_cast<int>(result.x), static_cast<int>(result.y));
}

D3DXVECTOR2 CCamera::getCameraPosition()
{
	return _camPosition;
}

RECT CCamera::getViewport()
{
	RECT rs;
	rs.left = _camPosition.x;
	rs.top = _camPosition.y;
	rs.right = rs.left + SCREEN_WIDTH;
	rs.bottom = rs.top - SCREEN_HEIGHT;
	return rs;
}

