#pragma once
#include "Text.h"
#include "Sprite2D.h"
#include "GameButton.h"
#include <list>

class GSPlay;
class EndGameMenu : public Sprite2D
{
private:
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Sprite2D>				m_bgMenu;
	std::shared_ptr<Sprite2D>				m_header;
	std::list<std::shared_ptr<Sprite2D>>	m_listSprite;
	std::vector<std::shared_ptr<Text>>		m_listText;
	bool									m_isWon;
	bool									m_isFirstWin;

public:
	EndGameMenu(bool isWon, bool isFirstWin);
	~EndGameMenu();

	void Init(bool isFirstWin);
	//void Update(float deltaTime);
	void Draw();
	void HandleTouchEvents(int x, int y, bool isPressed);
};