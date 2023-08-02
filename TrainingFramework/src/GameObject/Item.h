#pragma once
#include "Sprite2D.h"

class Item : public Sprite2D
{
private:
	std::string m_name;
	int m_amount;
	int m_price;
	int m_ID;

public:
	
	Item(std::string m_name, int m_amount, int m_price, int m_ID) 
	{
		this->m_name = m_name;
		this->m_amount = m_amount;
		this->m_price = m_price;
		this->m_ID = m_ID;
	};
	Item(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, std::string m_name, int m_amount, int m_price, int m_ID)
		: Sprite2D(model, shader, texture)
	{
		this->m_name = m_name;
		this->m_amount = m_amount;
		this->m_price = m_price;
		this->m_ID = m_ID;
	};

	std::string GetName() { return m_name; };
	int GetAmount() { return m_amount; };
	int GetPrice() { return m_price; };
	int GetID() { return m_ID; };

	void SetAmount(int amount) { m_amount = amount; };
};