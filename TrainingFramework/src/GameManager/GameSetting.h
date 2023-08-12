#pragma once
#include "GameManager/Singleton.h"

class GameSetting : public CSingleton<GameSetting>
{
private:
	int m_turnOnMusic;
	int m_turnOnSoundEffect;

public:
	GameSetting() 
	{
		m_turnOnMusic = 1;
		m_turnOnSoundEffect = 1;
	};

	void SetTurnOnMusic(int mode)
	{
		m_turnOnMusic = mode;
	}
	void SetTurnOnSoundEffect(int mode)
	{
		m_turnOnSoundEffect = mode;
	}
	int GetTurnOnMusic()
	{
		return m_turnOnMusic;
	}
	int GetTurnOnSoundEffect()
	{
		return m_turnOnSoundEffect;
	}
};