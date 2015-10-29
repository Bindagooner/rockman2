#pragma once
#ifndef _CSPRITE_H_
#define _CSPRITE_H_
#include <d3dx9.h>
#include "Texture.h"
#include "GameTime.h"
class CSprite : public CTexture
{
private:

	int _index;// giá trị frame hiện tại
	int _countFrame;// tổng số frame
	int _countRow;// tổng frame trên một dòng
	int _countColumn;// tổng frame trên một cột 
	int _frameHeight;// chiều cao của mỗi frame
	int _frameWidth;// chiều dài của mỗi frame
	int _timeFrame;//
	float _tick;		// cộng dôn thời gian để chyển frame
	bool _isNextFrame;
	int _frameStart;
	int _frameEnd;
	
public:
	int _timeFrameDefault;
	CSprite();
	CSprite(char* pNamePath, int countRow, int countColumn, int countFrame, int timeframe, Color color);
	~CSprite();
	void setIndex(int index);
	int getIndex();
	void nextSprite();
	void update(CGameTime* gameTime);
	Rect getDestinationRectangle();

	int getColum();
	int getRow();

	int getFrameHeight();
	int getFrameWidth();

	int getCountFrame();

	bool isNextFrame();
	void reset();
	void setAllowAnimate(int timeFrame);

	int setFrame(int frameStart, int frameEnd);

};
#endif