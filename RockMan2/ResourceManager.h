#pragma once

#include "Sprite.h"
#include "Global.h"
#include "DSUtil.h"
#include "Trace.h"
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

class CResourceManager
{
private:
	static CResourceManager* _instance;
	CSoundManager* _soundManager;
	map<int, CSprite*> _listSprite;
	map<int, CSound*>  _listSound;
	int _idSoundBGDefault;
public:

	//-----------------------------------------------------------------------------
	// Khởi tạo Direct Sound
	//-----------------------------------------------------------------------------
	int initDirectSound(HWND hWnd);

	//-----------------------------------------------------------------------------
	// Thêm một file audio vào danh sách âm thanh
	// + type: Loại audio
	// + loop: Có lặp lại audio đó không
	// + fileName: Đường dẫn file audio
	//-----------------------------------------------------------------------------
	void addSound(int soundID, bool isLooping, wchar_t* fileName);

	//-----------------------------------------------------------------------------
	// Load file audio
	// + loop: Có lặp lại audio đó không
	// + fileName: Đường dẫn file audio
	//-----------------------------------------------------------------------------
	CSound* loadSound(bool isLooping, wchar_t* fileName);

	//-----------------------------------------------------------------------------
	// Phát âm thanh
	// + soundID: ID của sound muốn phát
	//-----------------------------------------------------------------------------
	static void playASound(int soundID);

	//-----------------------------------------------------------------------------
	// Stop âm thanh
	// + soundID: ID của sound muốn dừng
	//-----------------------------------------------------------------------------
	static void stopSound(int soundID);

	//-----------------------------------------------------------------------------
	// Lấy đối tượng Sprite được load sẵn với spriteID cụ thể
	// + spriteID:  ID của Sprite muốn lấy
	//-----------------------------------------------------------------------------
	static CSprite getSprite(int spriteID);

	//-----------------------------------------------------------------------------
	// Thêm đối tượng Sprite được load sẵn với spriteID cụ thể
	// + spriteID:  ID của Sprite muốn lấy
	// + sprite: Sprite muốn load vào hệ thống
	//-----------------------------------------------------------------------------
	static void addSprite(int spriteID, CSprite* sprite);

	static void muteSound();
	static void replaySound();
	static bool isPlaySound;

	static int init(HWND hwnd);
	CResourceManager();
	~CResourceManager();
};

