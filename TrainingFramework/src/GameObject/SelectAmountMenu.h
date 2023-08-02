#pragma once
#include "Text.h"
#include "Sprite2D.h"
#include "GameButton.h"
#include "Item.h"
#include "Shop.h"

class Shop;
class SelectAmountMenu : public Sprite2D
{
private:
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Sprite2D>				m_bgMenu;
	std::shared_ptr<Text>					m_text;
	
public:

	SelectAmountMenu(int index, bool isEquipment, int coin, Shop* shop);
	~SelectAmountMenu();

	void Init(int index, bool isEquipment, int coin, Shop* shop);
	void Draw();
	void Update(float deltaTime);
	void HandleTouchEvents(int x, int y, bool isPressed);
};