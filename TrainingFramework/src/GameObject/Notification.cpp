#include "ResourceManagers.h"
#include "Notification.h"
#include "GameSetting.h"

Notification::Notification()
{
	time = 0.0f;
	Init();
}

Notification::~Notification()
{
	
}

void Notification::Init()
{
	std::cout << "Init noti\n";
	std::string text = GameSetting::GetInstance()->GetText();
	std::cout << text << "\n";
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	m_bg = std::make_shared<Sprite2D>(model, shader, texture);
	m_bg->Set2DPosition(Globals::screenWidth - 150.0f, Globals::screenHeight - 50.0f);
	m_bg->SetSize(300, 70);

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("SpicyPotatos-7Ba64.ttf");
	m_text = std::make_shared<Text>(shader, font, text, TextColor::BLACK, 1.0f);
	m_text->Set2DPosition(Globals::screenWidth - 250.0f, Globals::screenHeight - 45.0f);
}

void Notification::Draw()
{
	m_bg->Draw();
	m_text->Draw();
}

void Notification::Update(float deltaTime)
{
	m_bg->Update(deltaTime);
	m_text->Update(deltaTime);
	std::string text = GameSetting::GetInstance()->GetText();
	m_text->SetText(text);
	if (time > 1.0f)
	{
		//GameSetting::GetInstance()->SetDisplayNotification(0);
		std::cout << "Turn off notification\n";
		GameSetting::GetInstance()->SetText("");
		time = 0;
	}
	else
	{
		time += deltaTime;
	}
}

void Notification::Move(float fromX, float fromY, float toX, float toY)
{

}