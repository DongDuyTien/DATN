#include "MoneyShop.h"
#include "ResourceManagers.h"
#include "SaveData.h"

MoneyShop::MoneyShop()
{
	this->Init();
}

MoneyShop::~MoneyShop() {}

void MoneyShop::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_item.tga");
	float pos1 = Globals::screenWidth / 2.0f - 140.0f;
	float pos2 = Globals::screenHeight / 2.0f - 100.0f;

	for (int i = 0; i < 2; i++)
	{
		shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		texture = ResourceManagers::GetInstance()->GetTexture("bg_item.tga");
		std::shared_ptr<Sprite2D> slot = std::make_shared<Sprite2D>(model, shader, texture);
		slot->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f, pos2 + 30.0f);
		slot->SetSize(140, 200);
		m_listSlot.push_back(slot);
		
		if (i == 0)
		{
			texture = ResourceManagers::GetInstance()->GetTexture("bagOfCoin.tga");
			std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(model, shader, texture);
			sprite->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f, pos2);
			sprite->SetSize(50, 45);
			m_listSprite2D.push_back(sprite);

			shader = ResourceManagers::GetInstance()->GetShader("TextShader");
			auto font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
			auto text = std::make_shared<Text>(shader, font, "x 100", Vector4(50.0f, 30.0f, 0.0f, 1.2f), 1.0f);
			text->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f - 30.0f, pos2 + 50.0f);
			m_listText.push_back(text);

			font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
			text = std::make_shared<Text>(shader, font, "1 USD", Vector4(50.0f, 30.0f, 0.0f, 1.2f), 1.0f);
			text->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f - 25.0f, pos2 + 85.0f);
			m_listText.push_back(text);
		}
		else if (i == 1)
		{
			texture = ResourceManagers::GetInstance()->GetTexture("crown.tga");
			std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(model, shader, texture);
			sprite->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f, pos2);
			sprite->SetSize(60, 45);
			m_listSprite2D.push_back(sprite);

			shader = ResourceManagers::GetInstance()->GetShader("TextShader");
			auto font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
			auto text = std::make_shared<Text>(shader, font, "x 1000", Vector4(50.0f, 30.0f, 0.0f, 1.2f), 1.0f);
			text->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f - 40.0f, pos2 + 50.0f);
			m_listText.push_back(text);

			font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
			text = std::make_shared<Text>(shader, font, "10 USD", Vector4(50.0f, 30.0f, 0.0f, 1.2f), 1.0f);
			text->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f - 25.0f, pos2 + 85.0f);
			m_listText.push_back(text);
		}
		shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		texture = ResourceManagers::GetInstance()->GetTexture("btn_buy.tga");
		std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(pos1 + 2 * i / 3.0f * 210.0f, pos2 + 80.0f);
		button->SetSize(100.0f, 40.0f);
		if (i == 0)
		{
			button->SetOnClick([this]() {
				int coins = SaveData::GetInstance()->GetCoins();
				SaveData::GetInstance()->SaveCoins(coins + 100);
				});
		}
		else if (i == 1)
		{
			button->SetOnClick([this]() {
				int coins = SaveData::GetInstance()->GetCoins();
				SaveData::GetInstance()->SaveCoins(coins + 1000);
				});
		}
		m_listButton.push_back(button);
	}
}

void MoneyShop::Draw()
{
	for (auto it : m_listSlot)
	{
		it->Draw();
	}
	for (auto it : m_listSprite2D)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
}

void MoneyShop::Update(float deltaTime)
{
	for (auto it : m_listSlot)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listSprite2D)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listText)
	{
		it->Update(deltaTime);
	}
}

void MoneyShop::HandleTouchEvents(int x, int y, bool isPressed)
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