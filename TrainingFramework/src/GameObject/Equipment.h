#pragma once
#include "Item.h"

enum class EquipmentType
{
	WEAPON,
	SHIELD,
	None
};

class Equipment : public Item
{
private:
	bool m_isEquiped = false;
	EquipmentType m_type;

public:
	Equipment(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, 
		std::string m_name, int m_amount, int m_price, int m_ID, EquipmentType m_type, bool m_isEquiped) 
		: Item(model, shader, texture, m_name, m_amount, m_price, m_ID) 
	{
		this->m_type = m_type;
		this->m_isEquiped = m_isEquiped;
	};
	Equipment(std::string m_name, int m_amount, int m_price, int m_ID, EquipmentType m_type, bool m_isEquiped) 
		: Item(m_name, m_amount, m_price, m_ID)
	{
		this->m_type = m_type;
		this->m_isEquiped = m_isEquiped;
	};

	EquipmentType GetEquipmentType() { return m_type; };
	bool GetIsEquiped() { return m_isEquiped; };
	void SetIsEquiped(bool isEquiped) { m_isEquiped = isEquiped; };
};