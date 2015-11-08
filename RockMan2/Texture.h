#pragma once
#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_
#include <d3dx9.h>
#include "Global.h"
#include "Camera.h"
#include "Graphic.h"
#include "Trace.h"
class CTexture
{
protected:
	Texture _texture;// texture chính của hàm 
	int _height;// chiều cao của bức ảnh
	int _width;// chiều rộng của bức ảnh
	wchar_t* _pNamePath;// tên đường dẫn file
	void loadImageFromFile(wchar_t* pNamePath, Color color);//load texture 
public:
	
	CTexture();
	CTexture(wchar_t* pNamePath, Color color);
	~CTexture();
	Texture getTexture();
	int getHeight();
	int getWidth();
};
#endif