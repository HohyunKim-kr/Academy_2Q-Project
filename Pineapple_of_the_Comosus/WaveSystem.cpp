#include "Enemy.h"
#include "WaveSystem.h"
#include "../D2DEngine/Scene.h"
#include"../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/BoxCollider.h"

#include <iostream> 
#include <cstdlib>  // rand() �Լ� ����� ���� ����
#include <ctime>    // �ð� ��� �õ� ����
#include <random>   // ���� ������ ����ϱ� ���� ����
#include "EnemyFactory.h"

WaveSystem::WaveSystem()
{
    //InitializePool(); // �� Ǯ �ʱ�ȭ
}

WaveSystem::~WaveSystem()
{
    m_Enemies.clear();
    m_EnemyPool.clear();
    delete enemyFactory; // EnemyFactory ��ü ����
}

void WaveSystem::InitializePool()
{
    enemyFactory = new EnemyFactory(scene);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> floatDist(0.0f, 1.0f); // 0.0 ~ 1.0 ������ �Ǽ� ����

    for (int i = 0; i < initialPoolSize; ++i)
    {
        float randomValue = floatDist(gen); // 0.0 ~ 1.0 ������ ���� �� ����
        int enemyType;

        if (randomValue < 0.2f)
            enemyType = 0; // 20% Ȯ���� 0
        else if (randomValue < 0.4f)
            enemyType = 1; // 20% Ȯ���� 1
        else if (randomValue < 0.6f)
            enemyType = 2; // 20% Ȯ���� 2
        else if (randomValue < 0.8f)
            enemyType = 3; // 20% Ȯ���� 3
        else
            enemyType = 4; // 20% Ȯ���� 4

        auto enemy = enemyFactory->CreateEnemy(enemyType); // 0-4 ������ �� ����
        enemy->gameObject->isActive = false;
        m_EnemyPool.push_back(enemy);
    }
}

Enemy* WaveSystem::GetEnemyFromPool()
{
    if (m_EnemyPool.empty())
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> floatDist(0.0f, 1.0f); // 0.0 ~ 1.0 ������ �Ǽ� ����

        float randomValue = floatDist(gen); // 0.0 ~ 1.0 ������ ���� �� ����
        int enemyType;

        if (randomValue < 0.2f)
            enemyType = 0; // 20% Ȯ���� 0
        else if (randomValue < 0.4f)
            enemyType = 1; // 20% Ȯ���� 1
        else if (randomValue < 0.6f)
            enemyType = 2; // 20% Ȯ���� 2
        else if (randomValue < 0.8f)
            enemyType = 3; // 20% Ȯ���� 3
        else
            enemyType = 4; // 20% Ȯ���� 4

        auto enemy = enemyFactory->CreateEnemy(enemyType); // 0-4 ������ �� ����
        m_EnemyPool.push_back(enemy);
    }

    Enemy* enemy = m_EnemyPool.back();
    enemy->gameObject->isActive = true;
    m_EnemyPool.pop_back();
    return enemy;
}

void WaveSystem::ReturnEnemyToPool(Enemy* enemy)
{
    m_EnemyPool.push_back(enemy);
    enemy->gameObject->isActive = false;
}

void WaveSystem::SpawnWave()
{
    int numEnemiesToSpawn = 1; // �ϴ��� ���̺� 1���� ����

    m_Enemies.clear();  // ���� ���̺꿡�� ������ ���� ���� (�ʿ��� ���)

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distY(-240.0f, 0.0f);
    std::bernoulli_distribution distSide(0.5); // 50% Ȯ���� true �Ǵ� false ����


    for (int i = 0; i < numEnemiesToSpawn; ++i)
    {
        Enemy* newEnemy = GetEnemyFromPool();

        bool spawnOnLeft = distSide(gen); // 50% Ȯ���� ���� �Ǵ� �����ʿ��� ����

        float spawnY = distY(gen);

        Vector2 spawnPosition;
        Vector2 moveDirection;

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

        newEnemy->gameObject->transform->pos.worldPosition = spawnPosition;
        newEnemy->move->SetDirection(moveDirection);
        newEnemy->move->SetSpeed(50.0f);
        newEnemy->tmpY = spawnPosition.y;

        m_Enemies.push_back(newEnemy);
        std::cout << "���� �����Ǿ����ϴ�" << std::endl;
    }
}

void WaveSystem::StartNextWave()
{
    if (currentWave < maxWave)
    {
        currentWave++;
        waveTimer = 3.0f;  // Ÿ�̸� �ʱ�ȭ
        SpawnWave();        // ���ο� wave ����
    }
    // maxWave�� �������� ��� �߰����� ó�� �ʿ� (���� ���� �Ǵ� ���� ��)
}

bool WaveSystem::IsMapEmpty()
{
    return m_Enemies.empty();  // �⺻������ false ��ȯ
}


void WaveSystem::Update(float deltaTime)
{
    // ���̺� Ÿ�̸� ����
    waveTimer -= deltaTime;

    // ���̺� Ÿ�̸Ӱ� 0 ���ϰ� �Ǿ���, ���� ���� ������
    if (waveTimer <= 0.0f && !m_Enemies.empty())
    {
        // ���� Ȱ��ȭ�ϰ� �� ��Ͽ��� ����
        auto enemy = m_Enemies.front();
        enemy->gameObject->isActive = true;
        m_Enemies.erase(m_Enemies.begin());

        // ���̺� Ÿ�̸Ӹ� ���� ���̺꿡 �°� ����
        waveTimer = 1.0f / currentWave;
    }

    // ���̺갡 ���� �� ���� ���̺� ����
    if (m_Enemies.empty() && currentWave > 0)
    {
        StartNextWave();
    }
}