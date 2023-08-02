#pragma once
#include "GameManager/Singleton.h"
#include <string>
#include <filesystem>
#include "Player.h"
#include "Item.h"
#include "Equipment.h"

class SaveData : public CSingleton<SaveData>
{
public:
	SaveData();
	~SaveData();

	void ClearDataFolder();
	void Init(std::string &fileName);

	void SaveLevel(int numPassedlevel);
	int LoadLevel();

	void SavePlayer(std::shared_ptr<Entity> player);
	std::vector<std::shared_ptr<Entity>> LoadPlayer();

	std::shared_ptr<Entity> LoadEnemy(int level);

	void SaveCoins(int coins);
	int GetCoins();

	void SaveItem(std::vector<std::shared_ptr<Item>> listItem);
	void SaveEquipment(std::vector<std::shared_ptr<Equipment>> listEquipment);
	std::vector<std::shared_ptr<Item>> LoadItem();
	std::vector<std::shared_ptr<Equipment>> LoadEquipment();
	std::vector<std::string> GetItemInformation(int ID);
	std::vector<std::string> GetEquipmentInformation(int ID, EquipmentType type);
	std::string GetItemName(int ID);

	bool IsNewGame();
	void SetIsNewGame(bool isNewGame) { m_isNewGame = isNewGame; };
	bool GetIsNewGame() { return m_isNewGame; };

	std::vector<std::string> SplitString(const std::string& input, char delimiter);
	
private:
	std::string m_DataPath;
	bool m_isNewGame;
};
