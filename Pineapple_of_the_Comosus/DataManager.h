#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

enum class EnemyID {
	swordMan = 30601, 
	swordMan_solid,
	swordMan_fast,
	swordMan_hero,
	musketeer,
	musketeer_solid,
	musketeer_fast,
	musketeer_hero,
	heavyArmor,
	heavyArmor_solid,
	heavyArmor_fast,
	heavyArmor_hero,
	griffin,
	griffin_solid,
	griffin_fast,
	griffin_hero,
	bombCarrier,
	bombCarrier_solid,
	bombCarrier_fast,
	bombCarrier_hero,
	boss1,
	boss2,
};


struct EnemyData {
	EnemyData() = default;
	EnemyData(int _id) : id(_id) {};
	~EnemyData() = default;

	int id;
	int eliteType;

	int resistArrow;
	int resistBullet;
	int resistBurst;
	int resistComosus;

	int hp;
	int moveSpeed;
	int attack;
	int attackRate;
	int range;

	int reward;
	int expReward;
};

struct TurretData
{
	TurretData(int _id) : id(_id) {}; //id�� �ȵ��� ��� ���� ���ɼ� ���� ����.
	~TurretData() = default;
	int id;
	int cost;
	int refund;

	float burstRange;
	int damage;
	float fireRate;
	int penetration;

	int bulletType;
	float bulletSpeed;
	int slowRate;
	float slowDuration;

	float angle;
};

class DataManager
{
private:
	DataManager()=default;
	~DataManager() {
		for (auto& enemyData : enemyDataMap) {
			delete enemyData.second;
		}
		enemyDataMap.clear();
		for (auto& turretData : turretDataMap) {
			delete turretData.second;
		}
		turretDataMap.clear();
	};
public:
	

	static DataManager& GetInstance() {
		static DataManager instance;
		return instance;
	}

	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;


	std::map<int, EnemyData*> enemyDataMap;
	std::map<int ,TurretData*> turretDataMap;

	bool LoadEnemySheetFromCSV(const wchar_t* fileName)
	{
		std::wifstream file(fileName);
		if (!file.is_open()) {
			std::cout << "������ �� �� �����ϴ�." << std::endl;
			std::wcout << fileName << std::endl;
			return false;
		}
		std::wstring line;			// ������ ���ڿ�	
		int DataCount = 0;			// ���� �� ������ ����
		std::getline(file, line);		// ù��° �� �б�
		{
			std::getline(file, line);   // �ι�° �� �б� (������ ����)
			std::wstringstream wss(line);
			wss >> DataCount;
		}

		for (int j = 0; j < DataCount; j++)
		{

			getline(file, line);		// ���� �б�
			std::wstringstream wss(line);    // ������ �о wstringstream�� ����
			std::wstring token;
			{
				getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и� ID
				EnemyData* Enemy = new EnemyData(_wtoi(token.c_str()));
				getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и� Name
				getline(wss, token, L',');  // wss�� ������ ,�� �������� ���ڿ��� �и� Size
				getline(wss, token, L',');  // EliteType
				Enemy->eliteType = _wtoi(token.c_str());

				getline(wss, token, L',');  // wss�� ������ ,�� �������� ���ڿ��� �и� Resist
				Enemy->resistArrow = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->resistBullet = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->resistBurst = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->resistComosus = _wtoi(token.c_str());

				getline(wss, token, L',');  // wss�� ������ ,�� �������� ���ڿ��� �и� Stat
				Enemy->hp = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->moveSpeed = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->attack = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->attackRate = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->range = _wtoi(token.c_str());

				getline(wss, token, L',');
				Enemy->reward = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->expReward = _wtoi(token.c_str());
				enemyDataMap.insert(std::make_pair(Enemy->id, Enemy));
			}
		}
		file.close();
		return true;
	}

	bool LoadTurretSheetFromCSV(const wchar_t* fileName) {
		std::wifstream file(fileName);
		if (!file.is_open()) {
			std::cout << "������ �� �� �����ϴ�." << std::endl;
			std::wcout << fileName << std::endl;
			return false;
		}
		std::wstring line;			// ������ ���ڿ�	
		int DataCount = 0;			// ���� �� ������ ����
		for (int i = 0; i < 6; i++) { // 6��° �� ���� ���������.
			std::getline(file, line);
		}

		{
			std::getline(file, line);   // 7��° �� �б� (������ ����)
			std::wstringstream wss(line);
			std::wstring token;
			getline(wss, token, L',');
			while (_wtoi(token.c_str()) == 0) {
				getline(wss, token, L',');
				if (_wtoi(token.c_str()) != 0) break;
			}
			DataCount = _wtoi(token.c_str());
		}

		for (int j = 0; j < DataCount; j++)
		{

			getline(file, line);		// ���� �б�
			std::wstringstream wss(line);    // ������ �о wstringstream�� ����
			std::wstring token;
			{
				while (_wtoi(token.c_str()) == 0) {
					getline(wss, token, L',');
					if (_wtoi(token.c_str()) != 0) break;
				}
				TurretData* Turret = new TurretData(_wtoi(token.c_str()));
				getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и� Name
				getline(wss, token, L',');  // wss�� ������ ,�� �������� ���ڿ��� �и� Size

				getline(wss, token, L',');  // wss�� ������ ,�� �������� ���ڿ��� �и� Cost
				Turret->cost = _wtoi(token.c_str());
				getline(wss, token, L',');  // Refund
				Turret->refund = _wtoi(token.c_str());

				getline(wss, token, L',');  // wss�� ������ ,�� �������� ���ڿ��� �и� Stat
				Turret->burstRange = _wtof(token.c_str());
				getline(wss, token, L',');
				Turret->damage = _wtoi(token.c_str());
				getline(wss, token, L',');
				Turret->fireRate = _wtof(token.c_str());
				getline(wss, token, L',');
				Turret->penetration = _wtoi(token.c_str());

				getline(wss, token, L',');
				Turret->bulletType = _wtoi(token.c_str());//����ü Ÿ��
				getline(wss, token, L',');
				Turret->bulletSpeed = _wtof(token.c_str());
				getline(wss, token, L',');
				Turret->slowRate = _wtof(token.c_str());
				getline(wss, token, L',');
				Turret->slowDuration = _wtof(token.c_str());

				getline(wss, token, L',');
				Turret->angle = _wtof(token.c_str());
				turretDataMap.insert(std::make_pair(Turret->id, Turret));
			}
		}
		file.close();
		return true;
	}

	EnemyData* GetEnemyData(int id) {
		
		return enemyDataMap[id];
	}

	TurretData* GetTurretData(int id) {
		
		return turretDataMap[id];
	}
};

