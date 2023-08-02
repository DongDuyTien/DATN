#include "InventoryMenu.h"
#include "ResourceManagers.h"
#include "GameStates/GSPlay.h"
#include "UseItemMenu.h"
#include "PlayerManager.h"

InventoryMenu::InventoryMenu(GSPlay* gs) : Sprite2D()
{
	this->SetSize(200, 200);
	Init(gs);
}

InventoryMenu::InventoryMenu() : Sprite2D()
{
	this->SetSize(200, 200);
	Init();
}

InventoryMenu::~InventoryMenu() {}

void InventoryMenu::Init(GSPlay *gs)
{
	m_listItem = Inventory::GetInstance()->GetItemList();
	m_viewOnly = false;
	// bg
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_inventory.tga");
	m_bgPause = std::make_shared<Sprite2D>(model, shader, texture);
	m_bgPause->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);
	m_bgPause->SetSize(370.0f, 370.0f);

	// btn
	// cancel
	texture = ResourceManagers::GetInstance()->GetTexture("btn_cancel.tga");
	m_btnBack = std::make_shared<GameButton>(model, shader, texture);
	m_btnBack->Set2DPosition((float)Globals::screenWidth / 2.0f + 190.0f, (float)Globals::screenHeight / 2.0f - 180.0f);
	m_btnBack->SetSize(50.0f, 50.0f);
	m_btnBack->SetOnClick([this, gs]() {
		this->SetSize(0, 0);
		gs->SetIsPause(false);
		gs->SetIsInventoryPressed(false);
		});
	// change tab
	texture = ResourceManagers::GetInstance()->GetTexture("itemTab.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->SetSize(60, 60);
	button->Set2DPosition(Globals::screenWidth / 2.0f - 150.0f , Globals::screenHeight / 2.0f - 180.0f);
	button->SetOnClick([this]() {
		ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
		m_isEquipmentTab = false;
		m_viewOnly = false;
		});
	m_listTab.push_back(button);
	texture = ResourceManagers::GetInstance()->GetTexture("equipmentTab.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->SetSize(60, 60);
	button->Set2DPosition(Globals::screenWidth / 2.0f - 90.0f, Globals::screenHeight / 2.0f - 180.0f);
	button->SetOnClick([this]() {
		ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
		m_isEquipmentTab = true;
		m_viewOnly = true;
		});
	m_listTab.push_back(button);

	float pos1 = Globals::screenWidth / 2.0f - 130.0f;
	float pos2 = Globals::screenHeight / 2.0f - 110.0f;

	//item
	for (int i = 0; i < m_listItem.size(); i++)
	{
		int ID = m_listItem[i]->GetID();
		std::string name = m_listItem[i]->GetName();
		int amount = m_listItem[i]->GetAmount();
		int price = m_listItem[i]->GetPrice();
		shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		texture = ResourceManagers::GetInstance()->GetTexture("socket1.tga");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->SetSize(60, 60);
		button->Set2DPosition(pos1 + 60 * i + 10.0f, pos2);
		button->SetOnClick([this, i, pos1, pos2]() {
			ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
			m_isSelect = true;
			m_useItemMenu = std::make_shared<UseItemMenu>(pos1 + 60 * i + 10.0f, pos2, this, i);
			});
		m_listItemButton.push_back(button);

		texture = ResourceManagers::GetInstance()->GetTexture("item" + std::to_string(ID) + ".tga");
		std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(model, shader, texture);
		sprite->SetSize(30, 45);
		sprite->Set2DPosition(pos1 + 60 * i + 10.0f, pos2);
		m_listItemSprite.push_back(sprite);

		// amount
		shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
		m_txtAmount = std::make_shared<Text>(shader, font, std::to_string(amount), Vector4(0.0f, 0.0f, 0.0f, 1.0f), 0.6f);
		m_txtAmount->Set2DPosition(pos1 + 60 * i + 25.0f - 7.0f * (CountDigits(amount)-1), pos2 + 20.0f);
		m_listText.push_back(m_txtAmount);
	}
}

void InventoryMenu::Init() 
{
	m_listEquipment = Inventory::GetInstance()->GetEquipmentList();
	m_isEquipmentTab = true;
	m_viewOnly = false;
	// bg
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_inventory.tga");
	m_bgPause = std::make_shared<Sprite2D>(model, shader, texture);
	m_bgPause->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);
	m_bgPause->SetSize(370.0f, 370.0f);

	// btn
	// cancel
	texture = ResourceManagers::GetInstance()->GetTexture("btn_cancel.tga");
	m_btnBack = std::make_shared<GameButton>(model, shader, texture);
	m_btnBack->Set2DPosition((float)Globals::screenWidth / 2.0f + 190.0f, (float)Globals::screenHeight / 2.0f - 180.0f);
	m_btnBack->SetSize(50.0f, 50.0f);
	m_btnBack->SetOnClick([this]() {
		this->SetSize(0, 0);
		PlayerManager::GetInstance()->SetIsPause(false);
		});
	// change tab
	texture = ResourceManagers::GetInstance()->GetTexture("itemTab.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->SetSize(60, 60);
	button->Set2DPosition(Globals::screenWidth / 2.0f - 150.0f, Globals::screenHeight / 2.0f - 180.0f);
	button->SetOnClick([this]() {
		ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
		m_isEquipmentTab = false;
		m_viewOnly = true;
		});
	m_listTab.push_back(button);
	texture = ResourceManagers::GetInstance()->GetTexture("equipmentTab.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->SetSize(60, 60);
	button->Set2DPosition(Globals::screenWidth / 2.0f - 90.0f, Globals::screenHeight / 2.0f - 180.0f);
	button->SetOnClick([this]() {
		ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
		m_isEquipmentTab = true;
		m_viewOnly = false;
		});
	m_listTab.push_back(button);

	float pos1 = Globals::screenWidth / 2.0f - 130.0f;
	float pos2 = Globals::screenHeight / 2.0f - 110.0f;

	for (int i = 0; i < m_listEquipment.size(); i++)
	{
		int ID = m_listEquipment[i]->GetID();
		std::string name = m_listEquipment[i]->GetName();
		int amount = m_listEquipment[i]->GetAmount();
		int price = m_listEquipment[i]->GetPrice();
		EquipmentType type = m_listEquipment[i]->GetEquipmentType();
		bool isEquiped = m_listEquipment[i]->GetIsEquiped();
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("socket1.tga");
		std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
		button->SetSize(60, 60);
		button->Set2DPosition(pos1 + 60 * i + 10.0f, pos2);
		button->SetOnClick([this, i, pos1, pos2, type, isEquiped]() {
			m_isSelect = true;
			m_useItemMenu = std::make_shared<UseItemMenu>(pos1 + 60 * i + 10.0f, pos2, this, i, true, type, isEquiped);
			});
		m_listEquipmentButton.push_back(button);

		std::string sType;
		if (type == EquipmentType::WEAPON) sType = "weapon";
		else sType = "shield";
		texture = ResourceManagers::GetInstance()->GetTexture(sType + std::to_string(ID) + ".tga");
		std::shared_ptr<Sprite2D> sprite = std::make_shared<GameButton>(model, shader, texture);
		sprite->SetSize(30, 45);
		sprite->Set2DPosition(pos1 + 60 * i + 10.0f, pos2);
		m_listEquipmentSprite.push_back(sprite);
	}
}

void InventoryMenu::Update(float deltaTime)
{
	if (!m_isEquipmentTab)
	{
		float pos1 = Globals::screenWidth / 2.0f - 130.0f;
		float pos2 = Globals::screenHeight / 2.0f - 110.0f;
		m_listItem = Inventory::GetInstance()->GetItemList();
		if (m_listItem.size() < m_listItemButton.size() || m_listText.empty())
		{
			m_listItemButton.clear();
			m_listText.clear();
			m_listItemSprite.clear();
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			for (int i = 0; i < m_listItem.size(); i++)
			{
				int ID = m_listItem[i]->GetID();
				std::string name = m_listItem[i]->GetName();
				int amount = m_listItem[i]->GetAmount();
				int price = m_listItem[i]->GetPrice();
				auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
				auto texture = ResourceManagers::GetInstance()->GetTexture("socket1.tga");
				std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
				button->SetSize(60, 60);
				button->Set2DPosition(pos1 + 60 * i + 10.0f, pos2);
				if (m_viewOnly == true)
				{
					button->SetOnClick([]() {
						});
				}
				else
				{
					button->SetOnClick([this, i, pos1, pos2]() {
						ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
						m_isSelect = true;
						m_useItemMenu = std::make_shared<UseItemMenu>(pos1 + 60 * i + 10.0f, pos2, this, i, false, EquipmentType::None);
						});

				}
				m_listItemButton.push_back(button);

				texture = ResourceManagers::GetInstance()->GetTexture("item" + std::to_string(ID) + ".tga");
				std::shared_ptr<Sprite2D> sprite = std::make_shared<GameButton>(model, shader, texture);
				sprite->SetSize(30, 45);
				sprite->Set2DPosition(pos1 + 60 * i + 10.0f, pos2);
				m_listItemSprite.push_back(sprite);

				// amount
				shader = ResourceManagers::GetInstance()->GetShader("TextShader");
				std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
				m_txtAmount = std::make_shared<Text>(shader, font, std::to_string(amount), Vector4(0.0f, 0.0f, 0.0f, 1.0f), 0.6f);
				m_txtAmount->Set2DPosition(pos1 + 60 * i + 25.0f - 7.0f * (CountDigits(amount) - 1), pos2 + 20.0f);
				m_listText.push_back(m_txtAmount);
			}
		}
		else
		{
			for (int i = 0; i < m_listItem.size(); i++)
			{
				m_listText[i]->SetText(std::to_string(m_listItem[i]->GetAmount()));
			}
		}
	}
	else
	{
		m_listEquipment = Inventory::GetInstance()->GetEquipmentList();
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		float pos1 = Globals::screenWidth / 2.0f - 130.0f;
		float pos2 = Globals::screenHeight / 2.0f - 110.0f;
		for (int i = 0; i < m_listEquipment.size(); i++)
		{
			int ID = m_listEquipment[i]->GetID();
			std::string name = m_listEquipment[i]->GetName();
			int amount = m_listEquipment[i]->GetAmount();
			int price = m_listEquipment[i]->GetPrice();
			EquipmentType type = m_listEquipment[i]->GetEquipmentType();
			bool isEquiped = m_listEquipment[i]->GetIsEquiped();
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			auto texture = ResourceManagers::GetInstance()->GetTexture("socket1.tga");
			std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
			button->SetSize(60, 60);
			button->Set2DPosition(pos1 + 60 * i + 10.0f, pos2);
			if (m_viewOnly == false)
			{
				button->SetOnClick([this, i, pos1, pos2, type, isEquiped]() {
					m_isSelect = true;
					m_useItemMenu = std::make_shared<UseItemMenu>(pos1 + 60 * i + 10.0f, pos2, this, i, true, type, isEquiped);
					});
			}
			else
			{
				button->SetOnClick([]() {
					});
			}
			m_listEquipmentButton.push_back(button);

			std::string sType;
			if (type == EquipmentType::WEAPON) sType = "weapon";
			else sType = "shield";
			texture = ResourceManagers::GetInstance()->GetTexture(sType + std::to_string(ID) + ".tga");
			std::shared_ptr<Sprite2D> sprite = std::make_shared<GameButton>(model, shader, texture);
			sprite->SetSize(30, 45);
			sprite->Set2DPosition(pos1 + 60 * i + 10.0f, pos2);
			m_listEquipmentSprite.push_back(sprite);
		}
	}
}

void InventoryMenu::Draw()
{
	m_bgPause->Draw();
	m_btnBack->Draw();
	
	if (!m_isEquipmentTab)
	{
		for (auto it : m_listItemButton)
		{
			it->Draw();
		}
		for (auto it : m_listItemSprite)
		{
			it->Draw();
		}
		for (auto it : m_listText)
		{
			it->Draw();
		}
	}
	else
	{
		for (auto it : m_listEquipmentButton)
		{
			it->Draw();
		}
		for (auto it : m_listEquipmentSprite)
		{
			it->Draw();
		}
	}
	for (auto it : m_listTab)
	{
		it->Draw();
	}
	
	if(m_isSelect)
		m_useItemMenu->Draw();
}

void InventoryMenu::HandleTouchEvents(int x, int y, bool isPressed)
{
	if (m_isSelect)
	{
		m_useItemMenu->HandleTouchEvents(x, y, isPressed);
	}
	else
	{
		if (!m_isEquipmentTab)
		{
			for (auto it : m_listItemButton)
			{
				it->HandleTouchEvents(x, y, isPressed);
			}
		}
		else
		{
			for (auto it : m_listEquipmentButton)
			{
				it->HandleTouchEvents(x, y, isPressed);
			}
		}
		for (auto it : m_listTab)
		{
			it->HandleTouchEvents(x, y, isPressed);
		}
		m_btnBack->HandleTouchEvents(x, y, isPressed);
	}
}

int InventoryMenu::CountDigits(int number) {
	if (number == 0) {
		return 1; // Special case for number 0
	}

	int numDigits = static_cast<int>(std::log10(std::abs(number))) + 1;
	return numDigits;
}