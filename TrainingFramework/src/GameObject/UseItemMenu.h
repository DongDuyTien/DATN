#pragma once
#include "Text.h"
#include "Sprite2D.h"
#include "GameButton.h"
#include "InventoryMenu.h"
#include "Item.h"

class InventoryMenu;
class UseItemMenu : public Sprite2D
{
private:
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Text>>		m_listText;

public:
	UseItemMenu(float x, float y, InventoryMenu* inventoryMenu, int index, bool isEquipment = false, 
		EquipmentType type = EquipmentType::None, bool isEquiped = false);
	~UseItemMenu();

	void Init(float x, float y, InventoryMenu* inventoryMenu, int index, bool isEquipment = false,
		EquipmentType type = EquipmentType::None, bool isEquiped = false);
	void Draw();
	void HandleTouchEvents(int x, int y, bool isPressed);
};