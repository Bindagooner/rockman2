#include "ResourceManager.h"

CResourceManager* CResourceManager::_instance = NULL;
bool CResourceManager::isPlaySound = true;

CResourceManager::CResourceManager()
{
}


CResourceManager::~CResourceManager()
{
}

int CResourceManager::init(HWND hwnd)
{
	if (_instance == NULL)
		_instance = new CResourceManager();

	if (CResourceManager::_instance->initDirectSound(hwnd) == 0) return 0;
	
#pragma region Add sound
	//CResourceManager::_instance->addSound(123, 0, L"Resources/Sound/pathsoundname.mp3");

#pragma endregion

#pragma region Add Sprite
	CResourceManager::_instance->_listSprite.insert(pair<int, CSprite*>(ID_ROCKMAN_STAND, new CSprite(L"Resources//Sprites//Rockman//rockman_stand.png", 1, 2, 2, 600, D3DCOLOR_XRGB(0, 102, 102))));
	CResourceManager::_instance->_listSprite.insert(pair<int, CSprite*>(ID_ROCKMAN_RUN, new CSprite(L"Resources//Sprites//Rockman//rockman_run.png", 1, 3, 3, 100, D3DCOLOR_XRGB(0, 102, 102))));
	CResourceManager::_instance->_listSprite.insert(pair<int, CSprite*>(ID_ROCKMAN_JUMP, new CSprite(L"Resources//Sprites//Rockman//rockman_jump.png", 1, 1, 1, 600, D3DCOLOR_XRGB(0, 102, 102))));
	CResourceManager::_instance->_listSprite.insert(pair<int, CSprite*>(ID_ROCKMAN_STAND_FIRE, new CSprite(L"Resources//Sprites//Rockman//rockman_stand_fire.png", 1, 1, 1, 0, D3DCOLOR_XRGB(0, 102, 102))));
#pragma endregion

	return 1;
}

int CResourceManager::initDirectSound(HWND hWnd)
{
	HRESULT result;

	//create Direct Manage Sound Object
	_soundManager = new CSoundManager();

	//initializa DirectSound
	result = _soundManager->Initialize(hWnd, DSSCL_PRIORITY);
	if (result != DS_OK) return 0;// lỗi
	Trace(L"SoundManager has been initialize success.");

	//set the primaty buffer format
	result = _soundManager->SetPrimaryBufferFormat(2, 22050, 16);
	if (result != DS_OK) return 0;// lỗi
	Trace(L"SetPrimaryBufferFormat SoundManager has been success.");

	//return success
	return 1;
}

void CResourceManager::addSound(int soundID, bool isLooping, wchar_t* fileName)
{
	CSound* sound = this->loadSound(isLooping, fileName);
	if (sound != NULL)
		_listSound.insert(pair<int, CSound*>(soundID, sound));
}

CSound* CResourceManager::loadSound(bool isLooping, wchar_t* fileName)
{
	HRESULT result;

	CSound *wave;

	result = _soundManager->Create(&wave, fileName);
	if (result != DS_OK) return NULL;// lỗi
	Trace(L"The ", fileName, L" has been created successfully");

	wave->loop = isLooping;
	return wave;
}

void CResourceManager::playASound(int soundID)
{
	if (CResourceManager::isPlaySound)
	{
		map<int, CSound*>::iterator it = CResourceManager::_instance->_listSound.find(soundID);
		if (it != CResourceManager::_instance->_listSound.end())
		{
			CSound* sound = it->second;

			if (sound->loop)
			{
				sound->Play(0, 1);
				CResourceManager::_instance->_idSoundBGDefault = it->first;
			}
			else if (!sound->IsSoundPlaying())
				sound->Play();
		}
	}
}

void CResourceManager::stopSound(int soundID)
{
	if (CResourceManager::isPlaySound)
	{
		map<int, CSound*>::iterator it = CResourceManager::_instance->_listSound.find(soundID);
		if (it != CResourceManager::_instance->_listSound.end())
		{
			CSound* sound = it->second;

			sound->Stop();
		}
	}
}
void CResourceManager::replaySound()
{
	for (map<int, CSound*>::iterator it = CResourceManager::_instance->_listSound.begin(); it != CResourceManager::_instance->_listSound.end(); it++)
	{
		CSound* sound = it->second;
		if (it->first == CResourceManager::_instance->_idSoundBGDefault)
		{
			sound->Play(0, 1);
			isPlaySound = true;
			break;
		}
	}

}
void CResourceManager::muteSound()
{
	for (map<int, CSound*>::iterator it = CResourceManager::_instance->_listSound.begin(); it != CResourceManager::_instance->_listSound.end(); it++)
		if (it != CResourceManager::_instance->_listSound.end())
		{
			CSound* sound = it->second;
			sound->Stop();
		}
	isPlaySound = false;
}

CSprite CResourceManager::getSprite(int spriteID)
{
	return *CResourceManager::_instance->_listSprite.find(spriteID)->second;
}

void CResourceManager::addSprite(int spriteID, CSprite* sprite)
{
	CSprite* spriteTmp = CResourceManager::_instance->_listSprite.find(spriteID)->second;

	if (spriteTmp == NULL)
		CResourceManager::_instance->_listSprite.insert(pair<int, CSprite*>(spriteID, sprite));
	else
	{
		CResourceManager::_instance->_listSprite.erase(spriteID);
		CResourceManager::_instance->_listSprite.insert(pair<int, CSprite*>(spriteID, sprite));
	}
}