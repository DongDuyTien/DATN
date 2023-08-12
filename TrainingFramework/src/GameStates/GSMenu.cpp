#include "GSMenu.h"
#include "Camera.h"
#include "SaveData.h"
#include "Inventory.h"
#include "Shop.h"
#include "GameSetting.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), 
	m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_listText(std::list<std::shared_ptr<Text>>{})
{
}

GSMenu::~GSMenu()
{
}

void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu2.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	int w = Globals::screenHeight * 16 / 9;
	int h = Globals::screenHeight;
	m_background->Set2DPosition(w/2, h/2);
	m_background->SetSize(w, h);

	// bg button
	// continue
	texture = ResourceManagers::GetInstance()->GetTexture("bg_btn.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f - 180.0f);
	button->SetSize(300, 100);
	if (!SaveData::GetInstance()->IsNewGame())
	{
		button->SetOnClick([this]() {
			if (GameSetting::GetInstance()->GetTurnOnSoundEffect())
			{
				ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
			}
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_LEVEL);
			SaveData::GetInstance()->SetIsNewGame(false);
			
			});	
	}
	else
	{
		button->SetOnClick([this]() {
			});
	}
	m_listButton.push_back(button);

	// new game
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f - 70.0f);
	button->SetSize(300, 100);
	button->SetOnClick([this]() {
		SaveData::GetInstance()->ClearDataFolder();
		SaveData::GetInstance()->SetIsNewGame(true);
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_LEVEL);
		if (GameSetting::GetInstance()->GetTurnOnSoundEffect())
		{
			ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
		}
		});
	m_listButton.push_back(button);

	// game setting
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f + 40.0f);
	button->SetSize(300, 100);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_SETTING);
		if (GameSetting::GetInstance()->GetTurnOnSoundEffect())
		{
			ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
		}
		});
	m_listButton.push_back(button);

	// guide
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f + 150.0f);
	button->SetSize(300, 100);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_GUIDE);
		if (GameSetting::GetInstance()->GetTurnOnSoundEffect())
		{
			ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
		}
		});
	m_listButton.push_back(button);

	// exit
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f + 260.0f);
	button->SetSize(300, 100);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	// text for btn
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "CONTINUE", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.8f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 70.0f, Globals::screenHeight / 2.0f - 170.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, "NEW GAME", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.8f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 80.0f, Globals::screenHeight / 2.0f - 60.0f));
	m_listText.push_back(text);
	
	text = std::make_shared<Text>(shader, font, "SETTING", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.8f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 55.0f, Globals::screenHeight / 2.0f + 50.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, "GUIDE", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.8f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f -40.0f, Globals::screenHeight / 2.0f + 160.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, "EXIT", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.8f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 30.0f, Globals::screenHeight / 2.0f + 270.0f));
	m_listText.push_back(text);

	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	//font = ResourceManagers::GetInstance()->GetFont("Woodlook-nvyP.ttf");
	text = std::make_shared<Text>(shader, font, "Warrior Battle", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f, TextAlign::CENTER);
	text->Set2DPosition(100, 100);
	//text->Set2DPosition(Vector2(200, 200));
	m_listText.push_back(text);

	if (GameSetting::GetInstance()->GetTurnOnMusic())
	{
		std::string name = "gravity_fall_theme_sound.wav";
		ResourceManagers::GetInstance()->PlaySound(name, true);
	}
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
	SaveData::FreeInstance();
	Inventory::FreeInstance();
	Shop::FreeInstance();
	GameSetting::FreeInstance();
}


void GSMenu::Pause()
{
	ResourceManagers::GetInstance()->StopSound("gravity_fall_theme_sound.wav");
}

void GSMenu::Resume()
{
	if (GameSetting::GetInstance()->GetTurnOnMusic())
	{
		std::string name = "gravity_fall_theme_sound.wav";
		ResourceManagers::GetInstance()->PlaySound(name, true);
	}
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(float x, float y)
{
}

void GSMenu::Update(float deltaTime)
{
	int x = m_background->Get2DPosition().x;
	int y = m_background->Get2DPosition().y;
	//x = (x - Globals::screenWidth+ w / 2 + (int)(10*deltaTime)) % (w-Globals::screenWidth) + Globals::screenWidth - w / 2;

	x = ((100 * x - 100 * Globals::screenWidth + 50 * MN_bgWidth + int(7000 * deltaTime)) % (100 * MN_deltaX)) / 100 + Globals::screenWidth - MN_bgWidth / 2;
	m_background->Set2DPosition(x, y);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
}
