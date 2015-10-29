#include "Texture.h"

CTexture::CTexture()
{

}

CTexture::CTexture(char* pNamePath, Color color)
{
	this->_pNamePath = pNamePath;
	loadImageFromFile(_pNamePath, color);
}
CTexture::~CTexture()
{

}
void CTexture::loadImageFromFile(char* pNamePath, Color color)
{
	HRESULT result;
	ImageInfo info;

	// Lấy thông tin từ file ảnh
	result = D3DXGetImageInfoFromFileA(pNamePath, &info);
	if (result != D3D_OK)
	{
		// hiển thị một thông báo lỗi 
		Trace(L"RROR] Failed to get info from inage file!!! File path: %s. Error code: %d", pNamePath, result);
		return;
	}

	_width = info.Width;
	_height = info.Height;

	// Lấy thiết bị 
	Device pd3ddev = CGraphic::getInstance()->getDevice();
	if (pd3ddev)
		result = D3DXCreateTextureFromFileExA( // Tạo texture từ file ảnh
		pd3ddev,
		pNamePath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,// bộ nhớ chổ nào còn thì lưu texture tại đó
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		color,
		&info,
		NULL,
		&_texture);
	if (result != D3D_OK)
	{
		Trace(L"[ERROR] Failed to create texture from file!!! File path: %s. Error code: %d.", pNamePath, result);
		return;
	}
}
Texture CTexture::getTexture()
{

	return _texture;
}
int CTexture::getHeight()
{
	return _height;
}
int CTexture::getWidth()
{
	return _width;
}