#include "SelectAmountMenu.h"
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "SaveData.h"
#include "Inventory.h"
#include "GameSetting.h"

SelectAmountMenu::SelectAmountMenu(int index, bool isEquipment, int coin, Shop* shop) : Sprite2D()
{
	this->SetSize(200, 200);
	this->Init(index, isEquipment, coin, shop);
}

SelectAmountMenu::~SelectAmountMenu() {}

void SelectAmountMenu::Init(int index, bool isEquipment, int coin, Shop* shop)
{
	
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");
	m_bgMenu = std::make_shared<Sprite2D>(model, shader, texture);
	m_bgMenu->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);
	m_bgMenu->SetSize(400.0f, 200.0f);

	// btn
	// cancel
	texture = ResourceManagers::GetInstance()->GetTexture("btn_cancel.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2.0f - 50.0f, (float)Globals::screenHeight / 2.0f + 50.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this, shop]() {
		ResourceManagers::GetInstance()->PlaySoundWithDuration("cancel.wav", 0.2f);
		this->SetSize(0, 0);
		shop->SetIsPause(false);
		});
	m_listButton.push_back(button);
	// ok
	texture = ResourceManagers::GetInstance()->GetTexture("btn_ok.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2.0f + 50.0f, (float)Globals::screenHeight / 2.0f + 50.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this, index, isEquipment, coin, shop]() {
		if (!isEquipment)
		{
			ResourceManagers::GetInstance()->PlaySoundWithDuration("purchase.wav", 0.2f);
			std::shared_ptr<Item> item = Shop::GetInstance()->GetItemList()[index];
			int cost = item->GetPrice() * item->GetAmount();
			SaveData::GetInstance()->SaveCoins(coin - cost);
			Inventory::GetInstance()->AddItemToInventory(item);
			GameSetting::GetInstance()->SetText("You got " + std::to_string(item->GetAmount()) + " " + item->GetName());
		}
		else
		{
			ResourceManagers::GetInstance()->PlaySoundWithDuration("purchase.wav", 0.2f);
			std::shared_ptr<Equipment> equipment = Shop::GetInstance()->GetEquipmentList()[index];
			SaveData::GetInstance()->SaveCoins(coin - equipment->GetPrice());
			Inventory::GetInstance()->AddEquipmentToInventory(equipment);
			GameSetting::GetInstance()->SetText("You got " + std::to_string(1) + " " + equipment->GetName());
		}
		SelectAmountMenu::SetSize(0, 0);
		shop->SetIsPause(false);
		});
	m_listButton.push_back(button);

	// text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
	m_text = std::make_shared<Text>(shader, font, "ARE YOU SURE?", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.8f);
	m_text->Set2DPosition(Vector2((float)Globals::screenWidth / 2.0f - 100.0f, (float)Globals::screenHeight / 2.0f - 25.0f));
}

void SelectAmountMenu::Update(float deltaTime)
{
}

void SelectAmountMenu::Draw()
{
	m_bgMenu->Draw();
	m_text->Draw();

	for (auto it : m_listButton)
	{
		it->Draw();
	}
}

void SelectAmountMenu::HandleTouchEvents(int x, int y, bool isPressed)
{
	for (auto it : m_listButton)
	{
		it->HandleTouchEvents(x, y, isPressed);
	}
}