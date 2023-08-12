#pragma once
#include "Sprite2D.h"
#include "GameButton.h"
#include "Text.h"
#include "Item.h"
#include "Equipment.h"
#include "SelectAmountMenu.h"
#include "Singleton.h"

class SelectAmountMenu;
class MoneyShop : public Sprite2D
{
public:
	MoneyShop();
	~MoneyShop();

	void Init();
	void Update(float deltaTime);
	void Draw();
	void HandleTouchEvents(int x, int y, bool isPressed);

	void SetIsPause(bool isPause) { m_isPause = isPause; };

private:
	std::vector<std::shared_ptr<Sprite2D>>		m_listSprite2D;
	std::vector<std::shared_ptr<Sprite2D>>		m_listSlot;
	std::list<std::shared_ptr<GameButton>>		m_listButton;
	std::vector<std::shared_ptr<Text>>			m_listText;
	std::shared_ptr<SelectAmountMenu>			m_menu;
	bool										m_isPause;

};
