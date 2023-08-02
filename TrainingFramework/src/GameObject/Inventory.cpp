#include "Inventory.h"
#include "SaveData.h"

Inventory::Inventory()
{
	m_listItem = SaveData::GetInstance()->LoadItem();
	m_listEquipment = SaveData::GetInstance()->LoadEquipment();
	memset(m_buff, 0, sizeof(m_buff));
	for (int i = 0; i < m_listEquipment.size(); i++)
	{
		if (m_listEquipment[i]->GetIsEquiped() == true)
		{
			this->Equip(i, m_listEquipment[i]->GetEquipmentType());
		}
	}
}

Inventory::~Inventory()
{

}

void Inventory::ResetBuff()
{
	memset(m_buff, 0, sizeof(m_buff));
}

void Inventory::AddItemToInventory(std::shared_ptr<Item> item)
{
	m_listItem = SaveData::GetInstance()->LoadItem();
	if (m_listItem.size() == 0)
	{
		m_listItem.push_back(item);
		SaveData::GetInstance()->SaveItem(m_listItem);
		return;
	}
	for (int i = 0; i < m_listItem.size(); i++)
	{
		if (m_listItem[i]->GetID() == item->GetID())
		{
			m_listItem[i]->SetAmount(m_listItem[i]->GetAmount() + item->GetAmount());
			SaveData::GetInstance()->SaveItem(m_listItem);
			return;
		}
	}
	m_listItem.push_back(item);
	SaveData::GetInstance()->SaveItem(m_listItem);
}

void Inventory::AddEquipmentToInventory(std::shared_ptr<Equipment> equipment)
{
	m_listEquipment = SaveData::GetInstance()->LoadEquipment();
	/*if (m_listEquipment.size() == 0)
	{
		m_listEquipment.push_back(equipment);
		SaveData::GetInstance()->SaveEquipment(m_listEquipment);
		return;
	}
	for (int i = 0; i < m_listEquipment.size(); i++)
	{
		if (m_listEquipment[i]->GetName() == equipment->GetName())
		{
			m_listEquipment[i]->SetAmount(m_listEquipment[i]->GetAmount() + equipment->GetAmount());
			SaveData::GetInstance()->SaveEquipment(m_listEquipment);
			return;
		}
	}*/
	m_listEquipment.push_back(equipment);
	SaveData::GetInstance()->SaveEquipment(m_listEquipment);
}

void Inventory::RemoveItem(int index)
{
	m_listItem = SaveData::GetInstance()->LoadItem();
	m_listItem.erase(m_listItem.begin() + index);
	SaveData::GetInstance()->SaveItem(m_listItem);
}

void Inventory::RemoveEquipment(int index)
{
	m_listEquipment = SaveData::GetInstance()->LoadEquipment();
	m_listEquipment.erase(m_listEquipment.begin() + index);
	SaveData::GetInstance()->SaveEquipment(m_listEquipment);
}

void Inventory::UseItem(int index)
{
	m_listItem = SaveData::GetInstance()->LoadItem();
	m_listItem[index]->SetAmount(m_listItem[index]->GetAmount() - 1);
	std::vector<std::string> v = SaveData::GetInstance()->GetItemInformation(m_listItem[index]->GetID());
	if (v[3] == "Buff")
	{
		int buff[] = { stoi(v[1]), stoi(v[2]), 0, 0 };
		this->SetBuff(buff);
	}
	else
	{
		int buff[] = { -stoi(v[1]), -stoi(v[2]), 0, 0 };
		this->SetBuff(buff);
	}

	if (m_listItem[index]->GetAmount() == 0)
		RemoveItem(index);
	SaveData::GetInstance()->SaveItem(m_listItem);
}

void Inventory::Equip(int index, EquipmentType type)
{
	m_listEquipment = SaveData::GetInstance()->LoadEquipment();
	// m_listEquipment[index]->SetAmount(m_listEquipment[index]->GetAmount() - 1);
	/*if (m_listEquipment[index]->GetAmount() == 0)
		RemoveEquipment(index);*/
	for (int i = 0; i < m_listEquipment.size(); i++)
	{
		if (m_listEquipment[i]->GetEquipmentType() == m_listEquipment[index]->GetEquipmentType())
		{
			m_listEquipment[i]->SetIsEquiped(false);
		}
	}
	m_listEquipment[index]->SetIsEquiped(true);
	std::vector<std::string> v = SaveData::GetInstance()->GetEquipmentInformation(m_listEquipment[index]->GetID(), type);
	if (type == EquipmentType::WEAPON)
	{
		int buff[] = {0, 0, stoi(v[1]), 0 };
		this->SetBuff(buff);
	}
	else if(type == EquipmentType::SHIELD)
	{
		int buff[] = { 0, 0, 0, stoi(v[1]) };
		this->SetBuff(buff);
	}
	SaveData::GetInstance()->SaveEquipment(m_listEquipment);
}

void Inventory::UnEquip(int index, EquipmentType type)
{
	m_listEquipment = SaveData::GetInstance()->LoadEquipment();
	m_listEquipment[index]->SetIsEquiped(false);
	std::vector<std::string> v = SaveData::GetInstance()->GetEquipmentInformation(m_listEquipment[index]->GetID(), type);
	if (type == EquipmentType::WEAPON)
	{
		int buff[] = { 0, 0, -stoi(v[1]), 0 };
		this->SetBuff(buff);
	}
	else if (type == EquipmentType::SHIELD)
	{
		int buff[] = { 0, 0, 0, -stoi(v[1]) };
		this->SetBuff(buff);
	}
	SaveData::GetInstance()->SaveEquipment(m_listEquipment);
}

bool Inventory::HasEquipment(std::shared_ptr<Equipment> equipment)
{
	m_listEquipment = SaveData::GetInstance()->LoadEquipment();
	if (m_listEquipment.empty())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < m_listEquipment.size(); i++)
		{
			if (m_listEquipment[i]->GetID() == equipment->GetID()
				&& m_listEquipment[i]->GetEquipmentType() == equipment->GetEquipmentType())
				return true;
		}
	}
	return false;
}