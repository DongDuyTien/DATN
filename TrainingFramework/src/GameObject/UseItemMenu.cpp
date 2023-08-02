#include "UseItemMenu.h"
#include "ResourceManagers.h"

UseItemMenu::UseItemMenu(float x, float y, InventoryMenu* inventoryMenu, int index, bool isEquipment,
	EquipmentType type, bool isEquiped)
{
	this->SetSize(200, 200);
	Init(x, y, inventoryMenu, index, isEquipment, type, isEquiped);
}

UseItemMenu::~UseItemMenu() {}

void UseItemMenu::Init(float x, float y, InventoryMenu* inventoryMenu, int index, bool isEquipment,
	EquipmentType type, bool isEquiped)
{
	// bg
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// button
	auto texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(x + 60.0f, y - 20.0f);
	button->SetSize(60.0f, 40.0f);
	if (!isEquipment)
	{
		button->SetOnClick([this, inventoryMenu, index]() {
			std::string itemName = Inventory::GetInstance()->GetItemList()[index]->GetName();
			if (itemName == "Bomb")
			{
				ResourceManagers::GetInstance()->PlaySoundWithDuration("explosion.wav", 0.5f);
			}
			else ResourceManagers::GetInstance()->PlaySoundWithDuration("eat.wav", 0.2f);
			this->SetSize(0, 0);
			inventoryMenu->SetIsSelect(false);
			Inventory::GetInstance()->UseItem(index);
			});
	}
	else
	{
		if (!isEquiped)
		{
			button->SetOnClick([this, inventoryMenu, index, type]() {
				this->SetSize(0, 0);
				inventoryMenu->SetIsSelect(false);
				Inventory::GetInstance()->Equip(index, type);
				});
		}
		else
		{
			button->SetOnClick([this, inventoryMenu, index, type]() {
				this->SetSize(0, 0);
				inventoryMenu->SetIsSelect(false);
				Inventory::GetInstance()->UnEquip(index, type);
				});
		}
	}
	m_listButton.push_back(button);
	texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(x + 60.0f, y + 20.0f);
	button->SetSize(60.0f, 40.0f);
	if (!isEquipment)
	{
		button->SetOnClick([this, inventoryMenu, index]() {
			ResourceManagers::GetInstance()->PlaySoundWithDuration("throwDownItem.wav", 0.2f);
			this->SetSize(0, 0);
			inventoryMenu->SetIsSelect(false);
			Inventory::GetInstance()->RemoveItem(index);
			});
	}
	else
	{
		button->SetOnClick([this, inventoryMenu, index]() {
			ResourceManagers::GetInstance()->PlaySoundWithDuration("throwDownItem.wav", 0.2f);
			this->SetSize(0, 0);
			inventoryMenu->SetIsSelect(false);
			Inventory::GetInstance()->RemoveEquipment(index);
			});
		
	}
	m_listButton.push_back(button);
	// cancel
	texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(x + 60.0f, y + 60.0f);
	button->SetSize(60.0f, 40.0f);
	button->SetOnClick([this, inventoryMenu]() {
		ResourceManagers::GetInstance()->PlaySoundWithDuration("cancel.wav", 0.2f);
		this->SetSize(0, 0);
		inventoryMenu->SetIsSelect(false);
		});
	m_listButton.push_back(button);

	// text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("EvilEmpire-4BBVK.ttf");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "Exit", Vector4(0.0f, 0.0f, 0.0f, 1.0f), 0.6f);
	text->Set2DPosition(x + 50.0f, y + 62.0f);
	m_listText.push_back(text);
	text = std::make_shared<Text>(shader, font, "Remove", Vector4(0.0f, 0.0f, 0.0f, 1.0f), 0.6f);
	text->Set2DPosition(x + 40.0f, y + 22.0f);
	m_listText.push_back(text);
	std::string s;
	float pos1 = x + 40.0f;
	if (!isEquipment)
	{
		s = "Use";
		pos1 = x + 50.0f;
	}
	else
	{
		if (!isEquiped)
		{
			s = "Equip";
			pos1 = x + 50.0f;
		}	
		else
		{
			s = "Unequip";
		}
	}
	text = std::make_shared<Text>(shader, font, s, Vector4(0.0f, 0.0f, 0.0f, 1.0f), 0.6f);
	text->Set2DPosition(pos1, y - 18.0f);
	m_listText.push_back(text);

}

void UseItemMenu::Draw()
{
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
}
void UseItemMenu::HandleTouchEvents(int x, int y, bool isPressed)
{
	for (auto it : m_listButton)
	{
		it->HandleTouchEvents(x, y, isPressed);
	}
 }