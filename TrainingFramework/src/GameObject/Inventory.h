#pragma once
#include "SaveData.h"
#include "Singleton.h"
#include "Item.h"
#include "Equipment.h"

#define HP 0
#define MP 1
#define ATK 2
#define DEF 3

class Inventory : public Sprite2D, public CSingleton<Inventory>
{
private:
	std::vector<std::shared_ptr<Item>>			m_listItem;
	std::vector<std::shared_ptr<Equipment>>		m_listEquipment;
	int											m_buff[4];

public:
	Inventory();
	~Inventory();

	std::vector<std::shared_ptr<Item>> GetItemList() { return m_listItem; };
	std::vector<std::shared_ptr<Equipment>> GetEquipmentList() { return m_listEquipment; };

	void AddItemToInventory(std::shared_ptr<Item> item);
	void RemoveItem(int index);
	void AddEquipmentToInventory(std::shared_ptr<Equipment> equipment);
	void RemoveEquipment(int index);
	void UseItem(int index);
	void Equip(int index, EquipmentType type);
	void UnEquip(int index, EquipmentType type);
	bool HasEquipment(std::shared_ptr<Equipment> equipment);
	void SetBuff(int buff[])
	{
		for (int i = 0; i < sizeof(buff); i++)
		{
			m_buff[i] = buff[i];
		}
	};
	int* GetBuff() { return m_buff; };
	void ResetBuff();
};