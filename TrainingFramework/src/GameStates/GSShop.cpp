#include "GSShop.h"
#include "Camera.h"
#include "SaveData.h"
#include "ResourceManagers.h"
#include "GameSetting.h"

GSShop::GSShop()
{
	m_page = 1;
}


GSShop::~GSShop()
{
}

void GSShop::Init()
{
	m_coinToReset = 50;
	m_coins = SaveData::GetInstance()->GetCoins();
	m_shop = Shop::GetInstance();
	m_moneyShop = std::make_shared<MoneyShop>();

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// bg menu
	texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");
	std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f);
	sprite->SetSize(Globals::screenWidth - 80, Globals::screenHeight / 2 + 200);
	m_listSprite2D.push_back(sprite);

	// bg reset
	/*texture = ResourceManagers::GetInstance()->GetTexture("bg_resetshop.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f - 210.0f);
	sprite->SetSize(200, 60);
	m_listSprite2D.push_back(sprite);*/

	// header
	texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f - 280.0f);
	sprite->SetSize(220.0f, 70.0f);
	m_listSprite2D.push_back(sprite);

	// button
	// back
	texture = ResourceManagers::GetInstance()->GetTexture("btn_back.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(50.0f, 50.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		if (GameSetting::GetInstance()->GetTurnOnSoundEffect())
		{
			ResourceManagers::GetInstance()->PlaySoundWithDuration("smallSelect.wav", 0.1f);
		}
		});
	m_listButton.push_back(button);
	// reset
	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f + 200.0f, Globals::screenHeight / 2.0f - 210.0f);
	button->SetSize(30.0f, 30.0f);
	button->SetOnClick([this]() {
		if (GameSetting::GetInstance()->GetTurnOnSoundEffect())
		{
			ResourceManagers::GetInstance()->PlaySoundWithDuration("smallSelect.wav", 0.1f);
		}
		m_shop->CreateItem();
		m_coins = m_coins - m_coinToReset;
		SaveData::GetInstance()->SaveCoins(m_coins);
		});
	m_listButton.push_back(button);
	// next page
	texture = ResourceManagers::GetInstance()->GetTexture("btn_resume.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0f, Globals::screenHeight / 2.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this]() {
		m_page = 2;
		if (GameSetting::GetInstance()->GetTurnOnSoundEffect())
		{
			ResourceManagers::GetInstance()->PlaySoundWithDuration("smallSelect.wav", 0.1f);
		}
		});
	m_listButton.push_back(button);
	// back shop
	texture = ResourceManagers::GetInstance()->GetTexture("btn_back.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(50.0f, Globals::screenHeight / 2.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this]() {
		m_page = 1;
		if (GameSetting::GetInstance()->GetTurnOnSoundEffect())
		{
			ResourceManagers::GetInstance()->PlaySoundWithDuration("smallSelect.wav", 0.1f);
		}
		});
	m_listButton.push_back(button);
	// text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "SHOP", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.8f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 30.0f, Globals::screenHeight / 2.0f - 270.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, std::to_string(m_coinToReset), Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f + 160.0f, Globals::screenHeight / 2.0f - 205.0f));
	m_listText.push_back(text);

	m_coinsTxt = std::make_shared<Text>(shader, font, std::to_string(m_coins), Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.5f);
	m_coinsTxt->Set2DPosition(Vector2(Globals::screenWidth - 120.0f, 50.0f));

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("coin.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth - 30.0f, 40.0f);
	sprite->SetSize(30, 30);
	m_listSprite2D.push_back(sprite);
}

void GSShop::Exit()
{
	
}


void GSShop::Pause()
{
	
}

void GSShop::Resume()
{
	
}


void GSShop::HandleEvents()
{
}

void GSShop::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSShop::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	if (m_page == 1)
	{
		m_shop->HandleTouchEvents(x, y, bIsPressed);
	}
	else if (m_page == 2)
	{
		m_moneyShop->HandleTouchEvents(x, y, bIsPressed);
	}

	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSShop::HandleMouseMoveEvents(float x, float y)
{
	m_shop->HandleMouseMoveEvents(x, y);
}

void GSShop::Update(float deltaTime)
{
	m_coins = SaveData::GetInstance()->GetCoins();
	m_coinsTxt->SetText(std::to_string(m_coins));

	if (m_page == 1)
	{
		m_shop->Update(deltaTime);
		m_listText[0]->SetText("SHOP");
		m_listText[0]->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 30.0f, Globals::screenHeight / 2.0f - 270.0f));
		m_listSprite2D[1]->SetSize(220.0f, 70.0f);
	}
	else if (m_page == 2)
	{
		m_moneyShop->Update(deltaTime);
		m_listText[0]->SetText("MONEY SHOP");
		m_listText[0]->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 90.0f, Globals::screenHeight / 2.0f - 270.0f));
		m_listSprite2D[1]->SetSize(240.0f, 80.0f);

		m_moneyShop->Update(deltaTime);

	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSShop::Draw()
{
	m_background->Draw();
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
	m_coinsTxt->Draw();
	if (m_page == 1)
	{
		m_shop->Draw();
	}
	else if (m_page == 2)
	{
		m_moneyShop->Draw();
	}
}
