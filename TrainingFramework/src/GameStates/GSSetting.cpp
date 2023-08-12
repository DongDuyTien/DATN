#include "GameSetting.h"
#include "GSSetting.h"
#include "ResourceManagers.h"

GSSetting::GSSetting()
{
}

GSSetting::~GSSetting()
{
}

void GSSetting::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu2.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	int w = Globals::screenHeight * 16 / 9;
	int h = Globals::screenHeight;
	m_background->Set2DPosition(w / 2, h / 2);
	m_background->SetSize(w, h);

	texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");
	std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);
	sprite->SetSize(400.0f, 300.0f);
	m_listSprite2D.push_back(sprite);

	// header
	texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f - 140.0f);
	sprite->SetSize(200.0f, 75.0f);
	m_listSprite2D.push_back(sprite);

	// button
	// back
	texture = ResourceManagers::GetInstance()->GetTexture("btn_home.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(50.0f, 50.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
	// music on
	texture = ResourceManagers::GetInstance()->GetTexture("btn_sound_on.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2.0f + 100.0f, (float)Globals::screenHeight / 2.0f - 55.0f);
	button->SetOnClick([this]() {
		GameSetting::GetInstance()->SetTurnOnMusic(0);
		ResourceManagers::GetInstance()->StopSound("gravity_fall_theme_sound.wav");
		});
	m_listButton.push_back(button);
	// music off
	texture = ResourceManagers::GetInstance()->GetTexture("btn_sound_off.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2.0f + 100.0f, (float)Globals::screenHeight / 2.0f - 55.0f);
	button->SetOnClick([this]() {
		ResourceManagers::GetInstance()->PlaySound("gravity_fall_theme_sound.wav");
		GameSetting::GetInstance()->SetTurnOnMusic(1);
		});
	m_listButton.push_back(button);
	// sound effect on
	texture = ResourceManagers::GetInstance()->GetTexture("btn_sound_on.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2.0f + 100.0f, (float)Globals::screenHeight / 2.0f + 15.0f);
	button->SetOnClick([this]() {
		GameSetting::GetInstance()->SetTurnOnSoundEffect(0);
		});
	m_listButton.push_back(button);
	// sound effect off
	texture = ResourceManagers::GetInstance()->GetTexture("btn_sound_off.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2.0f + 100.0f, (float)Globals::screenHeight / 2.0f + 15.0f);
	button->SetOnClick([this]() {
		ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
		GameSetting::GetInstance()->SetTurnOnSoundEffect(1);
		});
	m_listButton.push_back(button);

	// txt
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "SETTING", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.5f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 2.0f - 50.0f, (float)Globals::screenHeight / 2.0f - 130.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, "Music:", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.2f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 2.0f - 150.0f, (float)Globals::screenHeight / 2.0f - 50.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, "Sound Effect:", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.2f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 2.0f - 150.0f, (float)Globals::screenHeight / 2.0f + 20.0f));
	m_listText.push_back(text);

	if (GameSetting::GetInstance()->GetTurnOnMusic())
	{
		std::string name = "gravity_fall_theme_sound.wav";
		ResourceManagers::GetInstance()->PlaySound(name, true);
	}
}

void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}

void GSSetting::Exit()
{
	if (GameSetting::GetInstance()->GetTurnOnMusic())
	{
		std::string soundName = "gravity_fall_theme_sound.wav";
		ResourceManagers::GetInstance()->StopSound(soundName);
	}
}

void GSSetting::HandleEvents()
{
}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSSetting::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSSetting::HandleMouseMoveEvents(float x, float y)
{
}

void GSSetting::Update(float deltaTime)
{
	int x = m_background->Get2DPosition().x;
	int y = m_background->Get2DPosition().y;
	x = ((100 * x - 100 * Globals::screenWidth + 50 * MN_bgWidth + int(7000 * deltaTime)) % (100 * MN_deltaX)) / 100 + Globals::screenWidth - MN_bgWidth / 2;
	m_background->Set2DPosition(x, y);

	if (GameSetting::GetInstance()->GetTurnOnMusic())
	{
		m_listButton[1]->SetSize(60.0f, 60.0f);
		m_listButton[2]->SetSize(0, 0);
	}
	else
	{
		m_listButton[2]->SetSize(60.0f, 60.0f);
		m_listButton[1]->SetSize(0, 0);
	}

	if (GameSetting::GetInstance()->GetTurnOnSoundEffect())
	{
		m_listButton[3]->SetSize(60.0f, 60.0f);
		m_listButton[4]->SetSize(0, 0);
	}
	else
	{
		m_listButton[4]->SetSize(60.0f, 60.0f);
		m_listButton[3]->SetSize(0, 0);
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listSprite2D)
	{
		it->Update(deltaTime);
	}
}

void GSSetting::Draw()
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
}