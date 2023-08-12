#include "GSLevel.h"
#include "Camera.h"
#include "Player.h"
#include "Level.h"
#include "SaveData.h"
#include "PlayerManager.h"
#include "GSPlay.h"

GSLevel::GSLevel()
{
	if (GameSetting::GetInstance()->GetTurnOnMusic())
	{
		ResourceManagers::GetInstance()->PlaySound("woodsTheme.wav", true);
	}
}

GSLevel::~GSLevel()
{	
}

void GSLevel::Init()
{
	
	// bg
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button
	// back
	texture = ResourceManagers::GetInstance()->GetTexture("btn_home.tga");
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
	// shop
	texture = ResourceManagers::GetInstance()->GetTexture("header1.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 120.0f, 50.0f);
	button->SetSize(200.0f, 70.0f);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_SHOP);
		if (GameSetting::GetInstance()->GetTurnOnSoundEffect())
		{
			ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
		}
		});
	m_listButton.push_back(button);
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "GO TO SHOP", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.2f);
	text->Set2DPosition(Vector2(Globals::screenWidth - 180.0f, 55.0f));
	m_listText.push_back(text);

	// level
	m_level = Level::GetInstance();

	// player
	m_playerManager = PlayerManager::GetInstance();

}

void GSLevel::Exit()
{
	if (GameSetting::GetInstance()->GetTurnOnMusic())
	{
		ResourceManagers::GetInstance()->StopSound("woodsTheme.wav");
	}
}

void GSLevel::Pause()
{
	if (GameSetting::GetInstance()->GetTurnOnMusic())
	{
		ResourceManagers::GetInstance()->StopSound("woodsTheme.wav");
	}
}

void GSLevel::Resume()
{
	if (GameSetting::GetInstance()->GetTurnOnMusic())
	{
		ResourceManagers::GetInstance()->PlaySound("woodsTheme.wav", true);
	}
	m_level->Init();
	m_playerManager->GetPlayer()->SetTexture(ResourceManagers::GetInstance()->GetTexture(m_playerManager->GetPlayer()->	GetName() + "_idle.tga"), true);
	m_playerManager->GetPlayer()->Set2DPosition(Globals::screenWidth / 2.0f - 150.0f, Globals::screenHeight / 2.0f - 50.0f);
	m_playerManager->GetPlayer()->SetSize(200, 200);
	auto m_skillList = m_playerManager->GetPlayer()->GetSkillList();
	for (int i = 0; i < 3; i++) {
		m_skillList[i]->Set2DPosition(Globals::screenWidth / 6 + 50 * i, 2 * Globals::screenHeight / 3);
		m_skillList[i]->SetSize(40, 40);
	}
}

void GSLevel::HandleEvents()
{

}

void GSLevel::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSLevel::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	m_playerManager->HandleTouchEvents(x, y, bIsPressed);
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
	m_level->HandleTouchEvents(x, y, bIsPressed);
}

void GSLevel::HandleMouseMoveEvents(float x, float y)
{
	m_playerManager->HandleMouseMovesEvent(x, y);
}

void GSLevel::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	m_playerManager->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	if (m_level->GetSelectedLevel()) {
		GameStateMachine::GetInstance()->ChangeState(std::make_shared<GSPlay>(m_playerManager->GetPlayer(), m_level->GetSelectedLevel()));
		m_level->SetSelectedLevel(0);
	}
	m_level->Update(deltaTime);
}

void GSLevel::Draw()
{
	m_background->Draw();
	m_level->Draw();
	m_playerManager->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
}