#include "Level.h"
#include "ResourceManagers.h"
#include "SaveData.h"
#include "GameStates/GameStateMachine.h"

Level::Level()
{
	Init();
}

Level::~Level()
{
}

void Level::Init()
{
	

	m_numPassedLevel = SaveData::GetInstance()->LoadLevel();
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// bg
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");
	std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(3*Globals::screenWidth / 4, Globals::screenHeight / 2.0f);
	sprite->SetSize(Globals::screenWidth / 2.0 - 30, Globals::screenHeight / 2);
	m_listSprite2D.push_back(sprite);

	// header
	texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(3 * Globals::screenWidth / 4, Globals::screenHeight / 2.0f - 180.0f);
	sprite->SetSize(220.0f, 70.0f);
	m_listSprite2D.push_back(sprite);

	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");

	// btn
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int curLevel = i * 3 + j + 1;
			shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			texture = ResourceManagers::GetInstance()->GetTexture("btn_level.tga");
			std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
			if (curLevel > m_numPassedLevel + 1)
			{
				button->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_level_unclear.tga"));
			}
			button->SetOnClick([this, curLevel]() {
				ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
				if(curLevel<=m_numPassedLevel+1)
					this->SetSelectedLevel(curLevel);
					});
			float posX = Globals::screenWidth / 2.0f + 70.0f;
			float posY = Globals::screenHeight / 2.0f - 100.0f;
			button->Set2DPosition(posX + j * 75.0f, posY + i * 70.0f);
			button->SetSize(60, 60);
			m_listButton.push_back(button);

			shader = ResourceManagers::GetInstance()->GetShader("TextShader");
			std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, std::to_string(curLevel), Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f);
			text->Set2DPosition(posX - 5.0f - (curLevel / 10) * 3.0f + j * 75.0f, posY + 5.0f + i / 2.0 * 140.0f);
			m_listText.push_back(text);
		}
	}
	// text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "LEVEL", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.2f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 2.0f + 120.0f, (float)Globals::screenHeight / 2.0f - 172.0f));
	m_listText.push_back(text);
}

void Level::Draw()
{
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

void Level::Update(float deltaTime) 
{
	m_numPassedLevel = SaveData::GetInstance()->LoadLevel();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int curLevel = i * 3 + j + 1;
			if (curLevel <= m_numPassedLevel + 1)
			{
				auto texture = ResourceManagers::GetInstance()->GetTexture("btn_level.tga");
				m_listButton[curLevel - 1]->SetTexture(texture);
				m_listButton[curLevel - 1]->SetOnClick([this, curLevel]() {
					ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
					this->SetSelectedLevel(curLevel);
					});
			}
			else
			{
				auto texture = ResourceManagers::GetInstance()->GetTexture("btn_level_unclear.tga");
				m_listButton[curLevel - 1]->SetTexture(texture);
				m_listButton[curLevel - 1]->SetOnClick([]() {

					});
			}
		}
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void Level::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}