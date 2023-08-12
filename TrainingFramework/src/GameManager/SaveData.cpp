#include "SaveData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

SaveData::SaveData()
{
	m_DataPath = "..\\Data\\SaveGame\\";

}

SaveData::~SaveData()
{

}

void SaveData::ClearDataFolder()
{
	try
	{
		for (auto& entry : std::filesystem::directory_iterator(m_DataPath))
			std::filesystem::remove_all(entry.path());

		std::cout << "Clear Data!" << std::endl;
	}
	catch (std::filesystem::filesystem_error const& ex)
	{
		printf("%s\n", ex.what());
	}
}

bool SaveData::IsNewGame()
{
	if(std::filesystem::is_empty(m_DataPath))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SaveData::Init(std::string& fileName)
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + fileName;
	fp = fopen(filePath.c_str(), "w+");

	if (fileName == "Level.txt")
	{
		fprintf(fp, "%s %d", "LevelPassed:", 0);
		std::printf("%s\n", "Init level!");
	}
	else if (fileName == "Player.txt")
	{
		// name/element/maxHP/maxMP/attack/defense/
		fprintf(fp, "%s\n", "Alder/fire/150/200/7/0");
		fprintf(fp, "%s\n", "Roland/water/250/200/4/1");
		fprintf(fp, "%s\n", "Gaius/earth/200/200/5/3");
		std::printf("%s\n", "Init Player!");
	}
	else if (fileName == "Coin.txt")
	{
		fprintf(fp, "%s %d\n", "coins:", 50);
		std::printf("%s\n", "Init Coin!");
	}
	fclose(fp);
}

void SaveData::SaveLevel(int numPassedlevel)
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Level.txt";
	fp = fopen(filePath.c_str(), "r+");

	if (fp != NULL)
	{
		if (this->LoadLevel() == numPassedlevel - 1)
		{
			fprintf(fp, "%s %d", "LevelPassed:", numPassedlevel);
		}
		fclose(fp);
		std::printf("%s\n", "Save Level!");
	}
}

int SaveData::LoadLevel()
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Level.txt";
	fp = fopen(filePath.c_str(), "r");
	int numPassedLevel = 0;
	char sTmp[100];
	if (fp == NULL)
		this->Init(std::string("Level.txt"));
	else
	{
		int success = fscanf(fp, "%s %d", sTmp, &numPassedLevel);
		fclose(fp);
		//std::printf("%s %d\n", "LevelPassed:", numPassedLevel);
	}
	return numPassedLevel;
}

void SaveData::SavePlayer(std::shared_ptr<Entity> player)
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Player.txt";
	fp = fopen(filePath.c_str(), "w");

	if (fp != NULL)
	{
		fprintf(fp, "%s %s\n", "Name:", player->GetName().c_str());
		fprintf(fp, "%s %d\n", "MaxHP:", player->GetMaxHp());
		fprintf(fp, "%s %d\n", "MaxMP:", player->GetMaxMana());
		fprintf(fp, "%s %d\n", "Attack:", player->GetAttack());
		fprintf(fp, "%s %d\n", "Defense:", player->GetDefense());

		fclose(fp);
		std::printf("%s\n", "Save Player!");
	}
}

std::vector<std::shared_ptr<Entity>> SaveData::LoadPlayer()
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Player.txt";
	fp = fopen(filePath.c_str(), "r");

	char name[20] = { 0 };
	char element[20] = { 0 };
	int maxHP = 0;
	int maxMP = 0;
	int attack = 0;
	int defense = 0;
	int success = 0;

	std::vector<std::shared_ptr<Entity>> listPlayer;

	if (fp == NULL)
		this->Init(std::string("Player.txt"));
	else
	{
		for (int i = 0; i < 3; i++)
		{
			success = fscanf(fp, "%[^/]/%[^/]/%d/%d/%d/%d\n", name, element, &maxHP, &maxMP, &attack, &defense);
			std::shared_ptr<Entity> player = std::make_shared<Entity>(name, element, maxHP, maxMP, attack, defense);
			listPlayer.push_back(player);
			std::cout << name << " " << element << " " << maxHP << " " << maxMP << " " << attack << " " << defense << "\n";
		}

		fclose(fp);
	}

	return listPlayer;
}

std::shared_ptr<Entity> SaveData::LoadEnemy(int level)
{
	FILE* fp = NULL;
	std::string filePath = "..\\Data\\Enemy.txt";
	fp = fopen(filePath.c_str(), "r");

	char name[20] = { 0 };
	int maxHP = 0;
	int maxMP = 0;
	int attack = 0;
	int defense = 0;
	int index = 0;
	int element = 0;
	if (fp != NULL)
	{
		do
		{
			int success = fscanf(fp, "%*d %s %d %d %d %d ", name, &maxHP, &maxMP, &attack, &defense);
			std::cout << name << " " << maxHP << " " << maxMP << " " << attack << " " << defense << "\n";
			index++;
		} while (index < level);
		fclose(fp);
	}
	std::shared_ptr<Entity> enemy = std::make_shared<Entity>();
	enemy->SetName(name);
	enemy->SetMaxHp(maxHP);
	enemy->SetMaxMana(maxMP);
	enemy->SetAttack(attack);
	enemy->SetDefense(defense);
	//enemy->SetElement(element);
	return enemy;
}

int SaveData::GetCoins()
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Coin.txt";
	fp = fopen(filePath.c_str(), "r");
	int coins = 0;
	char sTmp[100];
	if (fp == NULL)
		this->Init(std::string("Coin.txt"));
	else
	{
		int success = fscanf(fp, "%s %d", sTmp, &coins);
		fclose(fp);
		//std::printf("%s %d\n", "coins:", coins);
	}
	return coins;
}

void SaveData::SaveCoins(int coins)
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Coin.txt";
	fp = fopen(filePath.c_str(), "r+");

	if (fp != NULL)
	{
		fprintf(fp, "%s %d\n", "coins:", coins);
		fclose(fp);
		std::printf("%s\n", "Save Coins!");
	}
}

void SaveData::SaveItem(std::vector<std::shared_ptr<Item>> listItem)
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Item.txt";
	fp = fopen(filePath.c_str(), "r+");

	if (fp == NULL)
	{
		fp = fopen(filePath.c_str(), "w+");
	}
	else
	{
		remove(filePath.c_str());
		fp = fopen(filePath.c_str(), "w+");
	}
	for (int i = 0; i < listItem.size(); i++)
	{
		fprintf(fp, "%d/%s/%d\n", listItem[i]->GetID(), listItem[i]->GetName().c_str(), listItem[i]->GetAmount());
	}
	fclose(fp);
	std::printf("%s\n", "Save Item!");
}

void SaveData::SaveEquipment(std::vector<std::shared_ptr<Equipment>> listEquipment)
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Equipment.txt";
	fp = fopen(filePath.c_str(), "r+");

	if (fp == NULL)
	{
		fp = fopen(filePath.c_str(), "w+");
	}
	else
	{
		remove(filePath.c_str());
		fp = fopen(filePath.c_str(), "w+");
	}
	for (int i = 0; i < listEquipment.size(); i++)
	{
		fprintf(fp, "%d/%s/%d/%d/%d\n", listEquipment[i]->GetID(), listEquipment[i]->GetName().c_str(), 
			listEquipment[i]->GetAmount(), static_cast<int>(listEquipment[i]->GetEquipmentType()), (int)listEquipment[i]->GetIsEquiped());
	}
	fclose(fp);
	std::printf("%s\n", "Save Equipment!");
}

std::vector<std::shared_ptr<Item>> SaveData::LoadItem()
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Item.txt";
	fp = fopen(filePath.c_str(), "r");
	std::vector<std::shared_ptr<Item>> listItem;
	char name[50] = { 0 };
	int amount;
	int ID;

	if (fp != NULL)
	{
		while (fscanf(fp, "%d/%[^/]/%d\n", &ID, name, &amount) != EOF)
		{
			//printf("%s %d\n", name, amount);
			std::shared_ptr<Item> item = std::make_shared<Item>(name, amount, 0, ID);
			listItem.push_back(item);
		}
		fclose(fp);
	}
	return listItem;
}

std::vector<std::string> SaveData::GetItemInformation(int ID)
{
	std::ifstream file("..\\Data\\ItemInformation.json");
	json data;
	file >> data;

	std::string str = data["Item" + std::to_string(ID)];
	std::vector<std::string> v = SplitString(str, '/');

	file.close();
	return v;
}

std::string SaveData::GetItemName(int ID)
{
	std::vector<std::string> v = GetItemInformation(ID);
	return v[0];
}

std::vector<std::shared_ptr<Equipment>> SaveData::LoadEquipment()
{
	FILE* fp = NULL;
	std::string filePath = m_DataPath + "Equipment.txt";
	fp = fopen(filePath.c_str(), "r");
	std::vector<std::shared_ptr<Equipment>> listEquipment;
	char name[50] = { 0 };
	int amount;
	int ID;
	int type;
	int isEquiped;

	if (fp != NULL)
	{
		while (fscanf(fp, "%d/%[^/]/%d/%d/%d\n", &ID, name, &amount, &type, &isEquiped) != EOF)
		{
			bool b = isEquiped != 0;
			std::shared_ptr<Equipment> equipment = std::make_shared<Equipment>(name, amount, 0, ID, static_cast<EquipmentType>(type), b);
			listEquipment.push_back(equipment);
		}
		fclose(fp);
	}
	return listEquipment;
}

std::vector<std::string> SaveData::GetEquipmentInformation(int ID, EquipmentType type)
{
	std::ifstream file("..\\Data\\ItemInformation.json");
	json data;
	file >> data;
	std::string str;

	if (type == EquipmentType::WEAPON)
	{
		str = data["Weapon" + std::to_string(ID)];
	}
	else if (type == EquipmentType::SHIELD)
	{
		str = data["Shield" + std::to_string(ID)];
	}
	std::vector<std::string> v = SplitString(str, '/');

	file.close();
	return v;
}

std::vector<std::string> SaveData::SplitString(const std::string& input, char delimiter) {
	std::vector<std::string> result;
	std::stringstream ss(input);
	std::string item;

	while (std::getline(ss, item, delimiter)) {
		result.push_back(item);
	}

	return result;
}