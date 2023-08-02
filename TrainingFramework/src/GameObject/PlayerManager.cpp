#include "PlayerManager.h"
#include "ResourceManagers.h"
#include "SaveData.h"
#include "GameStates/GameStateMachine.h"
#include "Entity.h"
#include "WaterCharacter.h"
#include "FireCharacter.h"
#include "WoodCharacter.h"


PlayerManager::PlayerManager()
{
	Init();
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::Init()
{
	if (SaveData::GetInstance()->GetIsNewGame())
	{
		std::string fileName = "Player.txt";
		SaveData::GetInstance()->Init(fileName);
	}
	
	std::shared_ptr<Entity> player = SaveData::GetInstance()->LoadPlayer()[0];
	int* buff = Inventory::GetInstance()->GetBuff();
	std::string name = player->GetName();
	int maxHP = player->GetMaxHp();
	int maxMP = player->GetMaxMana();
	int attack = player->GetAttack();
	int defense = player->GetDefense();

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
	auto nameTxt = std::make_shared<Text>(shader, font, name, Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	nameTxt->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 200.0f, Globals::screenHeight / 2.0f - 100.0f));
	m_listText.push_back(nameTxt);

	// bg for menu
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");
	std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.0f - 150.0f, Globals::screenHeight / 2.0f);
	sprite->SetSize(Globals::screenWidth / 2.0 - 40, Globals::screenHeight / 2);
	m_listSprite2D.push_back(sprite);

	// back
	texture = ResourceManagers::GetInstance()->GetTexture("btn_back.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f - 280.0f, Globals::screenHeight / 2.0f);	
	button->SetSize(50, 50);
	button->SetOnClick([this, nameTxt]() {
		ResourceManagers::GetInstance()->PlaySoundWithDuration("smallSelect.wav", 0.1f);
		m_currentCharacter = (m_currentCharacter + 2) % 3;
		m_player = m_listCharacter[m_currentCharacter];
		nameTxt->SetText(m_player->GetName());
		m_listPlayerInfor[0]->SetText(std::to_string(m_player->GetMaxHp()));
		m_listPlayerInfor[1]->SetText(std::to_string(m_player->GetMaxMana()));
		m_listPlayerInfor[2]->SetText(std::to_string(m_player->GetAttack()));
		m_listPlayerInfor[3]->SetText(std::to_string(m_player->GetDefense()));
		m_skillList = m_player->GetSkillList();
		for (int i = 0; i < 3; i++) {
			m_skillList[i]->Set2DPosition(Globals::screenWidth / 6 + 50 * i, 2 * Globals::screenHeight / 3);
			m_skillList[i]->SetSize(40, 40);
		}
		});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("bg_info.tga");
	m_info = std::make_shared<Sprite2D>(model, shader, texture);

	// next
	texture = ResourceManagers::GetInstance()->GetTexture("btn_resume.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f - 20.0f, Globals::screenHeight / 2.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this,nameTxt]() {
		ResourceManagers::GetInstance()->PlaySoundWithDuration("smallSelect.wav", 0.1f);
		m_currentCharacter = (m_currentCharacter + 1) % 3;
		m_player = m_listCharacter[m_currentCharacter];
		nameTxt->SetText(m_player->GetName());
		m_listPlayerInfor[0]->SetText(std::to_string(m_player->GetMaxHp()));
		m_listPlayerInfor[1]->SetText(std::to_string(m_player->GetMaxMana()));
		m_listPlayerInfor[2]->SetText(std::to_string(m_player->GetAttack()));
		m_listPlayerInfor[3]->SetText(std::to_string(m_player->GetDefense()));
		m_skillList = m_player->GetSkillList();
		for (int i = 0; i < 3; i++) {
			m_skillList[i]->Set2DPosition(Globals::screenWidth / 6 + 50 * i, 2 * Globals::screenHeight / 3);
			m_skillList[i]->SetSize(40, 40);
		}

		});
	m_listButton.push_back(button);
	// weapon
	texture = ResourceManagers::GetInstance()->GetTexture("socket.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f - 230.0f, Globals::screenHeight / 2.0f - 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
		m_isPause = true;
		m_menu = std::make_shared<InventoryMenu>();
		});
	m_listButton.push_back(button);
	texture = ResourceManagers::GetInstance()->GetTexture("weapon_placeholder.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.0f - 230.0f, Globals::screenHeight / 2.0f - 50.0f);
	sprite->SetSize(50, 50);
	m_listPlaceholder.push_back(sprite);
	// shield
	texture = ResourceManagers::GetInstance()->GetTexture("socket.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f - 230.0f, Globals::screenHeight / 2.0f + 10.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		ResourceManagers::GetInstance()->PlaySoundWithDuration("bigSelect.wav", 0.2f);
		m_isPause = true;
		m_menu = std::make_shared<InventoryMenu>();
		});
	m_listButton.push_back(button);
	texture = ResourceManagers::GetInstance()->GetTexture("shield_placeholder.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.0f - 230.0f, Globals::screenHeight / 2.0f + 10.0f);
	sprite->SetSize(50, 50);
	m_listPlaceholder.push_back(sprite);

	// header
	texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 4, Globals::screenHeight / 2.0f - 180.0f);
	sprite->SetSize(220.0f, 70.0f);
	m_listSprite2D.push_back(sprite);
	
	// animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	std::vector<std::shared_ptr<Entity>> listCharacter = SaveData::GetInstance()->LoadPlayer();
	for (auto it : listCharacter)
	{
		switch (it->GetElement())
		{
			case FIRE:
			{
				std::shared_ptr<FireCharacter> fC = std::make_shared<FireCharacter>(model, shader, texture, 6, 1, 0, 0.1f, it->GetName(), it->GetMaxHp(), it->GetMaxMana(), it->GetAttack() + buff[ATK], it->GetDefense() + buff[DEF]);
				m_listCharacter.push_back(fC);
				break;
			}
			case WATER:
			{
				std::shared_ptr<WaterCharacter> wC = std::make_shared<WaterCharacter>(model, shader, texture, 6, 1, 0, 0.1f, it->GetName(), it->GetMaxHp(), it->GetMaxMana(), it->GetAttack() + buff[ATK], it->GetDefense() + buff[DEF]);
				m_listCharacter.push_back(wC);
				break;
			}
			case EARTH:
			{
				std::shared_ptr<EarthCharacter> woC = std::make_shared<EarthCharacter>(model, shader, texture, 6, 1, 0, 0.1f, it->GetName(), it->GetMaxHp(), it->GetMaxMana(), it->GetAttack() + buff[ATK], it->GetDefense() + buff[DEF]);
				m_listCharacter.push_back(woC);
				break;
			}
		}
	}

	m_currentCharacter = 0;
	m_player = m_listCharacter[m_currentCharacter];
	m_skillList = m_player->GetSkillList();
	for (int i = 0; i < 3; i++) {
		m_skillList[i]->Set2DPosition(Globals::screenWidth / 6 + 50 * i, 2*Globals::screenHeight / 3);
		m_skillList[i]->SetSize(40, 40);
	}
	for (auto x : m_listCharacter) {
		x->SetTexture(ResourceManagers::GetInstance()->GetTexture(x->GetName() + "_idle.tga"), true);
		x->Set2DPosition(Globals::screenWidth / 2.0f - 150.0f, Globals::screenHeight / 2.0f - 50.0f);
		x->SetSize(200, 200);
	}

	// text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "PLAYER", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.2f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 2.0f - 190.0f, (float)Globals::screenHeight / 2.0f - 172.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, "HP: ", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 250.0f, Globals::screenHeight / 2.0f + 65.0f));
	m_listText.push_back(text);
	text = std::make_shared<Text>(shader, font, "MP: ", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 250.0f, Globals::screenHeight / 2.0f + 90.0f));
	m_listText.push_back(text);
	text = std::make_shared<Text>(shader, font, "Atk: ", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 120.0f, Globals::screenHeight / 2.0f + 65.0f));
	m_listText.push_back(text);
	text = std::make_shared<Text>(shader, font, "Def: ", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 120.0f, Globals::screenHeight / 2.0f + 90.0f));
	m_listText.push_back(text);
	text = std::make_shared<Text>(shader, font, std::to_string(maxHP), Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 200.0f, Globals::screenHeight / 2.0f + 65.0f));
	m_listPlayerInfor.push_back(text);
	text = std::make_shared<Text>(shader, font, std::to_string(maxMP), Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 200.0f, Globals::screenHeight / 2.0f + 90.0f));
	m_listPlayerInfor.push_back(text);
	text = std::make_shared<Text>(shader, font, std::to_string(attack), Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 70.0f, Globals::screenHeight / 2.0f + 65.0f));
	m_listPlayerInfor.push_back(text);
	text = std::make_shared<Text>(shader, font, std::to_string(defense), Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 70.0f, Globals::screenHeight / 2.0f + 90.0f));
	m_listPlayerInfor.push_back(text);
	Inventory::GetInstance()->ResetBuff();
}
std::shared_ptr<Entity>	PlayerManager::GetPlayer() {
	return m_player;
}

void PlayerManager::HandleMouseMovesEvent(float x, float y) {
	m_info->SetSize(0, 0);
	m_listSkillInfor.clear();
	for (int i = 0; i < 3; i++) {
		auto it = m_skillList[i];
		if ((it->Get2DPosition().x - it->GetScale().x / 2.0f <= x) && (x <= it->Get2DPosition().x + it->GetScale().x / 2.0f)
			&& (it->Get2DPosition().y - it->GetScale().y / 2.0f <= y) && (y <= it->Get2DPosition().y + it->GetScale().y / 2.0f))
		{
			// The button is being pressed down
			m_info->SetSize(200, 100);
			m_info->Set2DPosition(it->Get2DPosition().x + 100, it->Get2DPosition().y - 50);
			int x = it->Get2DPosition().x + 10;
			int y = it->Get2DPosition().y - 80;
			auto detail = m_player->GetDetailOfSkill(i);
			for (int j = 0; j < detail.size(); j++) {
				detail[j]->Set2DPosition(x, y + 10 * j);
				m_listSkillInfor.push_back(detail[j]);

			}
		}
	}
}
void PlayerManager::Draw()
{
	for (auto it : m_listSprite2D)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listPlaceholder)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
	for (auto it : m_listPlayerInfor)
	{
		it->Draw();
	}
	m_player->Draw();
	for (auto it : m_skillList) {
		it->Draw();
	}
	m_info->Draw();
	for (auto x : m_listSkillInfor) {
		x->Draw();
	}
	if (m_isPause)
	{
		m_menu->Draw();
	}
}

void PlayerManager::Update(float deltaTime)
{
	if (!m_isPause)
	{
		m_player->Update(deltaTime);
		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
		m_listPlayerInfor[0]->SetText(std::to_string(m_player->GetMaxHp()));
		m_listPlayerInfor[1]->SetText(std::to_string(m_player->GetMaxMana()));
		m_listPlayerInfor[2]->SetText(std::to_string(m_player->GetAttack()));
		m_listPlayerInfor[3]->SetText(std::to_string(m_player->GetDefense()));
		std::vector<std::shared_ptr<Equipment>> listEquipment = Inventory::GetInstance()->GetEquipmentList();
		std::pair<int, int> flag = { 0, 0 };
		for (int i = 0; i < listEquipment.size(); i++)
		{
			if (listEquipment[i]->GetIsEquiped() == true)
			{
				if (listEquipment[i]->GetEquipmentType() == EquipmentType::WEAPON)
				{
					auto texture = ResourceManagers::GetInstance()->GetTexture("weapon" + std::to_string(listEquipment[i]->GetID()) + ".tga");
					m_listPlaceholder[0]->SetTexture(texture);
					m_listPlaceholder[0]->SetSize(25, 40);
					int *buff = Inventory::GetInstance()->GetBuff();
					//printf("%d\n", buff[ATK]);
					for (auto player : m_listCharacter)
					{
						player->SetAttack(player->GetAttack() + buff[ATK]);
					}
					Inventory::GetInstance()->ResetBuff();
					flag.first = 1;
				}
				else
				{
					auto texture = ResourceManagers::GetInstance()->GetTexture("shield" + std::to_string(listEquipment[i]->GetID()) + ".tga");
					m_listPlaceholder[1]->SetTexture(texture);
					int* buff = Inventory::GetInstance()->GetBuff();
					for (auto player : m_listCharacter)
					{
						player->SetDefense(player->GetDefense() + buff[DEF]);
					}
					Inventory::GetInstance()->ResetBuff();
					flag.second = 1;
				}
			}
		}
		if (flag.first == 0)
		{
			auto texture = ResourceManagers::GetInstance()->GetTexture("weapon_placeholder.tga");
			m_listPlaceholder[0]->SetTexture(texture);
			m_listPlaceholder[0]->SetSize(50, 50);
			int* buff = Inventory::GetInstance()->GetBuff();
			for (auto player : m_listCharacter)
			{
				player->SetAttack(player->GetAttack() + buff[ATK]);
			}
			Inventory::GetInstance()->ResetBuff();
		}
		if (flag.second == 0)
		{
			auto texture = ResourceManagers::GetInstance()->GetTexture("shield_placeholder.tga");
			m_listPlaceholder[1]->SetTexture(texture);
			int* buff = Inventory::GetInstance()->GetBuff();
			for (auto player : m_listCharacter)
			{
				player->SetDefense(player->GetDefense() + buff[DEF]);
			}
			Inventory::GetInstance()->ResetBuff();
		}
	}
	else
	{
		m_menu->Update(deltaTime);
	}

}

void PlayerManager::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	if (!m_isPause)
	{
		for (auto button : m_listButton)
		{
			if (button->HandleTouchEvents(x, y, bIsPressed))
			{
				break;
			}
		}
	}
	else
	{
		m_menu->HandleTouchEvents(x, y, bIsPressed);
	}
}