#pragma once
#include "Sprite2D.h"
#include "GameButton.h"
#include "Text.h"
#include "Item.h"
#include "Equipment.h"
#include "SelectAmountMenu.h"
#include "Singleton.h"

class SelectAmountMenu;
class Shop : public Sprite2D, public CSingleton<Shop>
{
public:
	Shop();
	~Shop();

	void Init();
	void Update(float deltaTime);
	void Draw();
	void HandleTouchEvents(int x, int y, bool isPressed);

	void SetIsPause(bool isPause) { m_isPause = isPause; };
	std::vector<std::shared_ptr<Item>> GetItemList() { return m_listItem; };
	std::vector<std::shared_ptr<Equipment>>	GetEquipmentList() { return m_listEquipment; };
	void CreateItem();

private:
	std::list<std::shared_ptr<GameButton>>		m_listButton;
	std::vector<std::shared_ptr<Text>>			m_listItemPrice;
	std::vector<std::shared_ptr<Text>>			m_listEquipmentPrice;
	std::vector<std::shared_ptr<Text>>			m_listAmount;
	std::vector<std::shared_ptr<Sprite2D>>		m_listSprite2D;
	std::vector<std::shared_ptr<Sprite2D>>		m_listSlot;
	std::vector<std::shared_ptr<Item>>			m_listItem;
	std::vector<std::shared_ptr<Equipment>>		m_listEquipment;
	std::shared_ptr<SelectAmountMenu>			m_menu;
	bool										m_isPause;
};
