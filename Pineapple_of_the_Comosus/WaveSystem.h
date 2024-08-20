#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/Movement.h"
#include "DayNightCycle.h"
#include "DataManager.h"
#include <vector>

class Scene;
class Enemy;
class EnemyFactory;
class BulletFactory;
class MainPineApple;

class WaveSystem : public Component
{
private:
    const float maxWaveTimer = 15.f;
    float waveTimer = 3.f;   // Wave Ÿ�̸�
    int currentWave = 0;       // ���� ���� ���� wave
    static const int maxWave = 56; // �ִ� wave ��

    std::vector<WaveEnemyData> leftEnemyDatas;
    std::vector<WaveEnemyData> rightEnemyDatas;
    
public:
    EnemyFactory* enemyFactory;  
    BulletFactory* bulletFactory;
    MainPineApple* mainPineApple;
    DayNightCycle* dayNightCycle;
    Vector2 rightPos; 
    Vector2 leftPos;

    GameObject* tutorial;
	


    Scene* scene = nullptr;
    // Ǯ���� ���͸� �������� �޼���
    //Enemy* GetEnemyFromPool(); // SwordMan -> Enemy�� ����
    //void ReturnEnemyToPool(Enemy* enemy); // SwordMan -> Enemy�� ����
    //void InitializePool();         // Ǯ �ʱ�ȭ
    int getCurrentWave() { return currentWave; }
    virtual void Init();
    virtual void Update(float deltaTime); // �� ������ ȣ��, wave Ÿ�̸� ������Ʈ
    //void SpawnWave();              // ���ο� wave ����

    void LoadWaveData();
    void Generator();
	void pullingTutorial(float deltaTime);

    bool IsFly(int id);

    //bool IsMapEmpty();             // �ʿ� ���Ͱ� �ϳ��� ������ Ȯ�� (���� �ʿ��� ��� ���)

    WaveSystem();
    virtual ~WaveSystem(); // �Ҹ��� ����
private:
    void StartNextWave();          // ���� wave�� �Ѿ��

};

