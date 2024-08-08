#include "Enemy.h"
#include "WaveSystem.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/BoxCollider.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "EnemyFactory.h"

WaveSystem::WaveSystem()
{
    
}

WaveSystem::~WaveSystem()
{
    delete enemyFactory; // EnemyFactory ��ü ����
    m_Enemies.clear();
}

void WaveSystem::SpawnWave()
{
    int numEnemiesToSpawn = 1; // �ϴ��� ���̺� 1���� ����

    m_Enemies.clear();  // ���� ���̺꿡�� ������ ���� ���� (�ʿ��� ���)

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distY(-240.0f, -100.f);
    std::bernoulli_distribution distSide(0.5); // 50% Ȯ���� true �Ǵ� false ����

    for (int i = 0; i < numEnemiesToSpawn; ++i)
    {
        Enemy* newEnemy = enemyFactory->GetEnemyFromPool();

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

void WaveSystem::Init()
{
    enemyFactory = new EnemyFactory(scene); // EnemyFactory ����
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
