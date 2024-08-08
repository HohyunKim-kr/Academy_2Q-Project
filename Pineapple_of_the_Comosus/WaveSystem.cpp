#include "Enemy.h"
#include "SwordMan.h"
#include "WaveSystem.h"
#include "../D2DEngine/Scene.h"
#include"../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/BoxCollider.h"

#include <iostream> 
#include <cstdlib>  // rand() �Լ� ����� ���� ����
#include <ctime>    // �ð� ��� �õ� ����
#include <random>   // ���� ������ ����ϱ� ���� ����

void WaveSystem::InitializePool()
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // ���� �õ� ����

    for (int i = 0; i < initialPoolSize; ++i)
    {
        auto  mon = scene->CreateGameObject<GameObject>();
        auto loadMon = mon->CreateComponent<SpriteRenderer>();
        loadMon->LoadTexture(L"../Resource/swordsman.png");
        mon->isActive = false;
        auto monster = mon->CreateComponent<SwordMan>();
        m_MonsterPool.push_back(monster);
    }
}

SwordMan* WaveSystem::GetMonsterFromPool()
{
    if (m_MonsterPool.empty())
    {
        // Ǯ�� ���Ͱ� ������ ���� ����
        auto  mon = scene->CreateGameObject<GameObject>();
        auto loadMon = mon->CreateComponent<SpriteRenderer>();
        auto movement = mon->CreateComponent<Movement>();
        auto collider = mon->CreateComponent<BoxCollider>();
        loadMon->LoadTexture(L"../Resource/swordsman.png");
        auto monster = mon->CreateComponent<SwordMan>();
        monster->move = movement;
        monster->pBoxcollider = collider;

        m_MonsterPool.push_back(monster);
    }

    SwordMan* monster = m_MonsterPool.back();
    monster->gameObject->isActive = true;
    m_MonsterPool.pop_back();
    return monster;
}

void WaveSystem::ReturnMonsterToPool(SwordMan* monster)
{
    m_MonsterPool.push_back(monster);
    monster->gameObject->isActive = false;
}

void WaveSystem::Update(float deltaTime)
{
    // ���Ͱ� �ʿ� �����ִ��� Ȯ���ϴ� �κ��� RemoveMonster�� �ƴ� �ٸ� �ý��ۿ��� ó��
    waveTimer -= deltaTime;  // deltaTime ��ŭ waveTimer ����

    if (waveTimer <= 0.0f && !m_Monster.empty())
    {
        auto monster = m_Monster.front();
        monster->gameObject->isActive = true;
        m_Monster.erase(m_Monster.begin());  // �̹� �׷��� ���ʹ� ��Ͽ��� ����

        waveTimer = 1.0f / currentWave;  // ���� ���Ͱ� ��Ÿ��������� �ð� ����
    }

    if (m_Monster.empty() && currentWave > 0)
    {
        StartNextWave();  // ��� ���Ͱ� ������ �� ���� ���̺�� �Ѿ
    }
}

// SpawnWave �Լ�: ���� wave�� �ش��ϴ� ���͸� ����.  
void WaveSystem::SpawnWave()
{
    int numMonstersToSpawn = 1; // �ϴ��� ���̺� 1���� ����

    m_Monster.clear();  // ���� ���̺꿡�� ������ ���͸� ���� (�ʿ��� ���)

    // ���� ���� �� ���� ����
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distY(-240.0f, 0.0f); // y��ǥ�� ������ ����

    for (int i = 0; i < numMonstersToSpawn; ++i)
    {
        // Ǯ���� ���͸� �����ɴϴ�.
        SwordMan* newMonster = GetMonsterFromPool();

        // �����ϰ� ���� �Ǵ� �����ʿ��� ����
        bool spawnOnLeft = rand() % 2 == 0;

        // ������ x ��ǥ�� ������ y ��ǥ�� ����Ͽ� ��ġ ����
        float spawnY = distY(gen);

        Vector2 spawnPosition;
        Vector2 moveDirection;  // �̵� ������ ������ ����

        if (spawnOnLeft)
        {
            spawnPosition = Vector2(-800.0f, spawnY);
            moveDirection = Vector2(1.0f, 0.0f);  // ���������� �̵�
        }
        else
        {
            spawnPosition = Vector2(900.0f, spawnY);
            moveDirection = Vector2(-1.0f, 0.0f);  // �������� �̵�
            newMonster->gameObject->GetComponent<SpriteRenderer>()->SetFilp(true, false);
        }

        newMonster->gameObject->transform->pos.worldPosition = spawnPosition;

        // �̵� ����� �ӵ��� �����մϴ�.
        //std::cout << moveDirection.x <<std::endl ;
        newMonster->move->SetDirection(moveDirection);
        newMonster->move->SetSpeed(50.0f);  // ���ϴ� �̵� �ӵ��� ����
        newMonster->tmpY = spawnPosition.y;

        m_Monster.push_back(newMonster);
        std::cout << "���Ͱ� �����Ǿ����ϴ�" << std::endl;
    }
}

// StartNextWave �Լ�: wave�� �����Ű�� Ÿ�̸Ӹ� �ʱ�ȭ
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

// IsMapEmpty �Լ�: �ʿ� ���Ͱ� �ϳ��� ������ Ȯ��
bool WaveSystem::IsMapEmpty()
{
    // �ʿ��� ���Ͱ� �����ִ��� Ȯ���ϴ� ���� (�ʿ� �� ���)
    return m_Monster.empty();  // �⺻������ false ��ȯ
}

WaveSystem::~WaveSystem()
{
    m_Monster.clear();

    m_MonsterPool.clear();
}