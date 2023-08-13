#pragma once
#include "GameManager/Singleton.h"
#include <string>

class GameSetting : public CSingleton<GameSetting>
{
private:
	int m_turnOnMusic;
	int m_turnOnSoundEffect;
	int m_displayNotification;
	std::string m_text;

public:
	GameSetting() 
	{
		m_turnOnMusic = 1;
		m_turnOnSoundEffect = 1;
		m_displayNotification = 0;
		m_text = "";
	};

	void SetTurnOnMusic(int mode)
	{
		m_turnOnMusic = mode;
	}
	void SetTurnOnSoundEffect(int mode)
	{
		m_turnOnSoundEffect = mode;
	}
	void SetDisplayNotification(int mode)
	{
		m_displayNotification = mode;
	}
	int GetDisplayNotification()
	{
		return m_displayNotification;
	}
	int GetTurnOnMusic()
	{
		return m_turnOnMusic;
	}
	int GetTurnOnSoundEffect()
	{
		return m_turnOnSoundEffect;
	}
	std::string GetText()
	{
		return m_text;
	}
	void SetText(std::string text)
	{
		m_text = text;
	}
};
