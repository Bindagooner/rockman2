#include "Screen.h"


CScreen::CScreen(){
	_isFinished = false;
	_camera = new CCamera();
	_cameraPath = new CCameraPath();
	_nextScreen = NULL;
}

CScreen::~CScreen(){
	_isFinished = true;
	SAFE_DELETE(_camera);
//	SAFE_DELETE(_cameraPath);
	SAFE_DELETE(_nextScreen);
}

bool CScreen::isFinished(){
	return _isFinished;
}

CScreen* CScreen::getNextScreen(){
	return _nextScreen;
}

int CScreen::getTypeID()
{
	return _typeID;
}