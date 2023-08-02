#pragma once
#include "Text.h"
#include "Sprite2D.h"
#include "GameButton.h"
#include "Inventory.h"
#include "SaveData.h"
#include "Item.h"
#include "UseItemMenu.h"

class GSPlay;
class PlayerManager;
class UseItemMenu;
class InventoryMenu : public Sprite2D
{
private:
	
	std::vector<std::shared_ptr<GameButton>>	m_listItemButton;
	std::vector<std::shared_ptr<GameButton>>	m_listEquipmentButton;
	std::vector<std::shared_ptr<GameButton>>	m_listTab;
	std::shared_ptr<GameButton>					m_btnBack;
	std::shared_ptr<Sprite2D>					m_bgPause;
	std::vector<std::shared_ptr<Sprite2D>>		m_listItemSprite;
	std::vector<std::shared_ptr<Sprite2D>>		m_listEquipmentSprite;
	std::vector<std::shared_ptr<Text>>			m_listText;
	std::vector<std::shared_ptr<Item>>			m_listItem;
	std::vector<std::shared_ptr<Equipment>>		m_listEquipment;
	std::shared_ptr<UseItemMenu>				m_useItemMenu;
	std::shared_ptr<Text>						m_txtAmount;
	bool m_isSelect = false;
	bool m_isEquipmentTab = false;
	bool m_viewOnly = false;

public:
	InventoryMenu(GSPlay* gs);
	InventoryMenu();
	~InventoryMenu();

	void Init(GSPlay* gs);
	void Init();
	void Draw();
	void Update(float deltaTime);
	void HandleTouchEvents(int x, int y, bool isPressed);
	
	void SetIsSelect(bool b) { m_isSelect = b; };
	int CountDigits(int number);
};