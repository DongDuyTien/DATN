#include "Shop.h"
#include "ResourceManagers.h"
#include "SaveData.h"
#include "Inventory.h"
#include <cstdlib>
#include <ctime>
#include <cmath>


Shop::Shop()
{
	this->Init();
	//m_isPause = false;
}

Shop::~Shop()
{

}

void Shop::Init()
{
	this->CreateItem();
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("item1.tga");
	
	float pos1 = Globals::screenWidth / 2.0f - 140.0f;
	float pos2 = Globals::screenHeight / 2.0f - 100.0f;
	float pos3 = Globals::screenHeight / 2.0f + 110.0f;
	
	// item
	for (int i = 0; i < 3; i++)
	{
		// line1
		m_listItem[i]->SetSize(60, 90);
		m_listItem[i]->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f, pos2);
		
		shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		texture = ResourceManagers::GetInstance()->GetTexture("bg_item.tga");
		std::shared_ptr<Sprite2D> slot = std::make_shared<Sprite2D>(model, shader, texture);
		slot->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f, pos2 + 30.0f);
		slot->SetSize(140, 200);
		m_listSlot.push_back(slot);
		slot = std::make_shared<Sprite2D>(model, shader, texture);
		slot->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f, pos3 + 30.0f);
		slot->SetSize(140, 200);
		m_listSlot.push_back(slot);
		
		// line2
		EquipmentType type;
		if (i == 0)
		{
			type = EquipmentType::WEAPON;
			texture = ResourceManagers::GetInstance()->GetTexture("weapon1.tga");
		}
		else if (i == 1)
		{
			type = EquipmentType::SHIELD;
			texture = ResourceManagers::GetInstance()->GetTexture("shield1.tga");
		}
		else
		{
			type = EquipmentType::SHIELD;
			texture = ResourceManagers::GetInstance()->GetTexture("chest.tga");
		}
		
		std::vector<std::string> EquipmentInfor = SaveData::GetInstance()->GetEquipmentInformation(1, type);
		std::shared_ptr<Equipment> equipment = std::make_shared<Equipment>(model, shader, texture, EquipmentInfor[0], 1, stoi(EquipmentInfor[2]), 1, type, false);
		if (Inventory::GetInstance()->HasEquipment(equipment))
		{
			texture = ResourceManagers::GetInstance()->GetTexture(i == 0 ? "weapon1_sold.tga" : "shield1_sold.tga");
			equipment->SetTexture(texture);
		}
		switch (i)
		{
		case 0:
			equipment->SetSize(60, 90);
			break;
		case 1:
			equipment->SetSize(75, 90);
			break;
		case 2:
			equipment->SetSize(75, 60);
			break;
		default:
			break;
		}
		equipment->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f, pos3);
		m_listEquipment.push_back(equipment);

		// buy btn1
		texture = ResourceManagers::GetInstance()->GetTexture("btn_buy.tga");
		std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f, pos2 + 80.0f);
		button->SetSize(100.0f, 50.0f);
		button->SetOnClick([this, i]() {
			int coins = SaveData::GetInstance()->GetCoins();
			if (coins >= m_listItem[i]->GetPrice() * m_listItem[i]->GetAmount())
			{
				ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
				m_isPause = true;
				m_menu = std::make_shared<SelectAmountMenu>(i, false, coins, this);

			}
			else printf("%s\n", "Not enough coin!");
			});
		m_listButton.push_back(button);
		// buy btn2
		texture = ResourceManagers::GetInstance()->GetTexture("btn_buy.tga");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f, pos3 + 80.0f);
		button->SetSize(100.0f, 50.0f);
		if (i < 2)
		{
			if (Inventory::GetInstance()->HasEquipment(equipment))
			{
				button->SetOnClick([]() {
					printf("%s\n", "Already have");
					});
			}
			else
			{
				button->SetOnClick([this, i]() {
					int coins = SaveData::GetInstance()->GetCoins();
					if (coins >= m_listEquipment[i]->GetPrice())
					{
						ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
						m_isPause = true;
						m_menu = std::make_shared<SelectAmountMenu>(i, true, coins, this);
					}
					else printf("%s\n", "Not enough coin!");
					});
			}
		}
		else
		{
			button->SetOnClick([]() {
				
				});
		}
		m_listButton.push_back(button);

		// coin1
		texture = ResourceManagers::GetInstance()->GetTexture("coin.tga");
		std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(model, shader, texture);
		sprite->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f + 25.0f , pos2 + 77.0f);
		sprite->SetSize(20, 20);
		m_listSprite2D.push_back(sprite);
		// coin2
		if (i < 2)
		{
			texture = ResourceManagers::GetInstance()->GetTexture("coin.tga");
			sprite = std::make_shared<Sprite2D>(model, shader, texture);
			sprite->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f + 25.0f, pos3 + 77.0f);
			sprite->SetSize(20, 20);
			m_listSprite2D.push_back(sprite);
		}
		// price1
		shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
		std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, std::to_string(m_listItem[i]->GetPrice()), Vector4(50.0f, 30.0f, 0.0f, 1.2f), 1.0f);
		int numDigits = static_cast<int>(std::log10(std::abs(m_listItem[i]->GetPrice()))) + 1; // countDigit of item's price
		text->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f - 7.0f * numDigits, pos2 + 85.0f);
		m_listItemPrice.push_back(text);
		// price2
		if (i < 2)
		{
			text = std::make_shared<Text>(shader, font, std::to_string(equipment->GetPrice()), Vector4(50.0f, 30.0f, 0.0f, 1.2f), 1.0f);
			text->Set2DPosition(pos1 + 145.0f * i - 7.0f * numDigits, pos3 + 85.0f);
		}
		else
		{
			text = std::make_shared<Text>(shader, font, "?", Vector4(50.0f, 30.0f, 0.0f, 1.2f), 1.0f);
			text->Set2DPosition(pos1 + 145.0f * i - 7.0f * numDigits, pos3 + 85.0f);
		}
		m_listEquipmentPrice.push_back(text);
		// amount1
		font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
		text = std::make_shared<Text>(shader, font, "x" + std::to_string(m_listItem[i]->GetAmount()), Vector4(50.0f, 30.0f, 0.0f, 1.2f), 1.0f);
		text->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f + 25.0f, pos2 + 40.0f);
		m_listAmount.push_back(text);
	}
}

void Shop::Draw()
{
	for (auto it : m_listSlot)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listItemPrice)
	{
		it->Draw();
	}
	for (auto it : m_listEquipmentPrice)
	{
		it->Draw();
	}
	for (auto it : m_listAmount)
	{
		it->Draw();
	}
	for (auto it : m_listSprite2D)
	{
		it->Draw();
	}
	for (auto it : m_listItem)
	{
		it->Draw();
	}
	for (auto it : m_listEquipment)
	{
		it->Draw();
	}
	if(m_isPause == true)
		m_menu->Draw();
}

void Shop::Update(float deltaTime)
{
	if(m_isPause == true)
		m_menu->Update(deltaTime);
	else
	{
		for (auto it : m_listItem)
		{
			it->Update(deltaTime);
		}
		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
		for (int i = 0; i < m_listItem.size(); i++)
		{
			m_listAmount[i]->SetText("x" + std::to_string(m_listItem[i]->GetAmount()));
			m_listItemPrice[i]->SetText(std::to_string(m_listItem[i]->GetAmount() * m_listItem[i]->GetPrice()));
		}
		for (int i = 0; i < m_listEquipment.size(); i++)
		{
			if (Inventory::GetInstance()->HasEquipment(m_listEquipment[i]))
			{
				auto texture = ResourceManagers::GetInstance()->GetTexture(i == 0 ? "weapon1_sold.tga" : "shield1_sold.tga");
				m_listEquipment[i]->SetTexture(texture);
			}
		}
	}
	
}

void Shop::HandleTouchEvents(int x, int y, bool isPressed)
{
	if (m_isPause == true)
		m_menu->HandleTouchEvents(x, y, isPressed);
	else
	{
		for (auto button : m_listButton)
		{
			if (button->HandleTouchEvents(x, y, isPressed))
			{
				break;
			}
		}
	}
}

void Shop::CreateItem()
{
	srand(time(NULL));
	for (int i = 0; i < 3; i++)
	{
		// create random
		int random = rand() % 100;
		int amount = 0;
		if (random < 10)
		{
			amount = 8 + rand() % 3; // random in range [8, 10]
		}
		else if (random < 40)
		{
			amount = 4 + rand() % 4; // random in range [4, 7]
		}
		else
		{
			amount = 1 + rand() % 3; // random in range [1, 3]
		}
		if (m_listItem.size() == 3)
		{
			m_listItem[i]->SetAmount(amount);
		}
		else
		{
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			auto texture = ResourceManagers::GetInstance()->GetTexture("item" + std::to_string(i+1) + ".tga");
			std::vector<std::string> itemInfor = SaveData::GetInstance()->GetItemInformation(i+1);
			std::shared_ptr<Item> item = std::make_shared<Item>(model, shader, texture, itemInfor[0], amount, stoi(itemInfor[4]), i + 1);
			m_listItem.push_back(item);
		}
		
	}
}