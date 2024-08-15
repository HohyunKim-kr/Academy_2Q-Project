#include "Enemy.h"

#include "WaveSystem.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/GameTime.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "EnemyFactory.h"
#include "BulletFactory.h"

WaveSystem::WaveSystem()
{
    
}

WaveSystem::~WaveSystem()
{
    delete enemyFactory; // EnemyFactory ��ü ����
    //m_Enemies.clear();
}

void WaveSystem::SpawnWave()
{
    int numEnemiesToSpawn = 1; // �ϴ��� ���̺� 1���� ����

    //m_Enemies.clear();  // ���� ���̺꿡�� ������ ���� ���� (�ʿ��� ���)

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distY(-240.0f, -100.f);
    std::uniform_real_distribution<float> flyDistY(300.f,400.0f);
    std::bernoulli_distribution distSide(0.5); // 50% Ȯ���� true �Ǵ� false ����

    for (int i = 0; i < numEnemiesToSpawn; ++i)
    {
        Enemy* newEnemy = enemyFactory->GetEnemyFromPool(30601);
     
        bool spawnOnLeft = distSide(gen); // 50% Ȯ���� ���� �Ǵ� �����ʿ��� ����

        float spawnY = distY(gen);
        float skySpanY = flyDistY(gen);

        Vector2 spawnPosition;
        Vector2 moveDirection;

        auto type = enemyFactory->enemyType;
        if (type == 2)
        {
            if (spawnOnLeft)
            {
                spawnPosition = Vector2(-800.0f, skySpanY);
                moveDirection = Vector2(1.0f, 0.0f);

                newEnemy->gameObject->GetComponent<SpriteRenderer>()->SetFilp(true, false);
            }
            else
            {
                spawnPosition = Vector2(900.0f, skySpanY);
                moveDirection = Vector2(-1.0f, 0.0f);

            }
        }
        else
        {
            if (spawnOnLeft)
            {
                spawnPosition = Vector2(-800.0f, spawnY);
                moveDirection = Vector2(1.0f, 0.0f);
            }
            else
            {
                spawnPosition = Vector2(900.0f, spawnY);
                moveDirection = Vector2(-1.0f, 0.0f);
                newEnemy->gameObject->GetComponent<SpriteRenderer>()->SetFilp(true, false);
            }
        }

        

        newEnemy->gameObject->transform->pos.worldPosition = spawnPosition;
        newEnemy->move->SetDirection(moveDirection);
        //newEnemy->move->SetSpeed(50.0f);
        newEnemy->tmpY = spawnPosition.y;
        newEnemy->move->SetSpeed(newEnemy->enemyData.moveSpeed);
        newEnemy->gameObject->SetActive(true);
        //m_Enemies.push_back(newEnemy);
        std::cout << "���� �����Ǿ����ϴ�" << std::endl;
    }
}

void WaveSystem::LoadWaveData()
{
    leftEnemyDatas.clear();
    leftEnemyDatas.assign(DataManager::GetInstance().GetWaveData(currentWave)->leftWaveData.begin(), 
            DataManager::GetInstance().GetWaveData(currentWave)->leftWaveData.end());
    rightEnemyDatas.clear();
    rightEnemyDatas.assign(DataManager::GetInstance().GetWaveData(currentWave)->rightWaveData.begin(),
            DataManager::GetInstance().GetWaveData(currentWave)->rightWaveData.end());

}

void WaveSystem::Generator()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distY(-240.0f, -100.f);
    std::uniform_real_distribution<float> flyDistY(300.f, 400.0f);

    float delta = GameTime::GetInstance().GetDeltaTime();
    for (auto& left : leftEnemyDatas) {
        if (left.count > 0) {
            left.startTime -= delta;
            if (left.startTime < 0.f) {
                left.interval -= delta;
                if (left.interval < 0.f) {
                    left.count -= 1;
                    left.interval += left.maxInterval;
                    // ����ȯ
                    Enemy* enemy = enemyFactory->GetEnemyFromPool(left.id);

                    float spawnY = IsFly(left.id) ? flyDistY(gen) : distY(gen);
                    Vector2 spawnPosition = Vector2(-800.0f, spawnY);
                    Vector2 moveDirection = Vector2(1.0f, 0.0f);

                    enemy->gameObject->transform->pos.worldPosition = spawnPosition;
                    enemy->move->SetDirection(moveDirection);
                    enemy->tmpY = spawnPosition.y;
                    enemy->move->SetSpeed(enemy->enemyData.moveSpeed);
                    enemy->gameObject->SetActive(true);
                }
            }
        }
    }
    for (auto& right : rightEnemyDatas) {
        if (right.count > 0) {
            right.startTime -= delta;
            if (right.startTime < 0.f) {
                right.interval -= delta;
                if (right.interval < 0.f) {
                    right.count -= 1;
                    right.interval += right.maxInterval;
                    // ����ȯ
                    Enemy* enemy = enemyFactory->GetEnemyFromPool(right.id);

                    float spawnY = IsFly(right.id) ? flyDistY(gen) : distY(gen);
                    Vector2 spawnPosition = Vector2(900.0f, spawnY);
                    Vector2 moveDirection = Vector2(-1.0f, 0.0f);
                    enemy->gameObject->GetComponent<SpriteRenderer>()->SetFilp(true, false);

                    enemy->gameObject->transform->pos.worldPosition = spawnPosition;
                    enemy->move->SetDirection(moveDirection);
                    enemy->tmpY = spawnPosition.y;
                    enemy->move->SetSpeed(enemy->enemyData.moveSpeed);
                    enemy->gameObject->SetActive(true);
                }
            }
        }
    }
}

bool WaveSystem::IsFly(int id)
{
    if(id >= 30613 && id <= 30616)
        return true;
    return false;
}

void WaveSystem::StartNextWave()
{   
    if (currentWave < maxWave)
    {
        currentWave++;
        LoadWaveData();
        waveTimer = maxWaveTimer;  // Ÿ�̸� �ʱ�ȭ //���� 15��
        //SpawnWave();        // ���ο� wave ����
    }
    // maxWave�� �������� ��� �߰����� ó�� �ʿ� (���� ���� �Ǵ� ���� ��)
}

//bool WaveSystem::IsMapEmpty()
//{
//    return m_Enemies.empty();  // �⺻������ false ��ȯ
//}

void WaveSystem::Init()
{
    enemyFactory = new EnemyFactory(scene); // EnemyFactory ����
    enemyFactory->bulletFactory = bulletFactory;
    enemyFactory->mainPineApple = mainPineApple;
}

void WaveSystem::Update(float deltaTime)
{
    // ���̺� Ÿ�̸� ����
    waveTimer -= deltaTime;

    // ���̺� Ÿ�̸Ӱ� 0 ���ϰ� �Ǿ���, ���� ���� ������
    if (waveTimer <= 0.0f)
    {
        // ���� Ȱ��ȭ�ϰ� �� ��Ͽ��� ����
        //auto enemy = m_Enemies.front();
        //enemy->gameObject->isActive = true;
        //m_Enemies.erase(m_Enemies.begin());

        // ���̺� Ÿ�̸Ӹ� ���� ���̺꿡 �°� ����
        // waveTimer = 1.0f / currentWave;
        waveTimer += maxWaveTimer;
        StartNextWave();
    }

    Generator();

    // �¾� �̵�
    
    dayNightCycle->SunMove(GameTime::GetInstance().GetDeltaTime(), (currentWave + 2) % 4); //�ϵ��ڵ� �ϱ��ߴµ� +2�� �����Ҷ� �¾��� �߰��� ������ �ȵǼ� �׷�����!
    dayNightCycle->MoonMove(GameTime::GetInstance().GetDeltaTime(), (currentWave - 1) % 4); 
    dayNightCycle->ApplyNightEffects(currentWave); // ���� �Ǿ��� �� ������ ȿ��
    dayNightCycle->RemoveNightEffects(currentWave); // ���� �Ǿ��� �� ������ ȿ��
}
