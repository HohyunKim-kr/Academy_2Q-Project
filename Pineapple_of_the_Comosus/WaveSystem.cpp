#include"testChar.h"
#include "WaveSystem.h"
#include "../D2DEngine/Scene.h"
#include"../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Transform.h"

#include <iostream> 
#include <cstdlib>  // rand() �Լ� ����� ���� ����
#include <ctime>    // �ð� ��� �õ� ����

void WaveSystem::InitializePool()
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // ���� �õ� ����

    for (int i = 0; i < initialPoolSize; ++i)
    {
        auto  mon = scene->CreateGameObject<GameObject>();
        auto loadMon = mon->CreateComponent<SpriteRenderer>();
        loadMon->LoadTexture(L"../Resource/Sun.png");
        mon->isActive = false;
        auto monster = mon->CreateComponent<testChar>();
        m_MonsterPool.push_back(monster);
    }
}

testChar* WaveSystem::GetMonsterFromPool()
{
    if (m_MonsterPool.empty())
    {
        // Ǯ�� ���Ͱ� ������ ���� ����
        auto  mon = scene->CreateGameObject<GameObject>();
        auto loadMon = mon->CreateComponent<SpriteRenderer>();
        loadMon->LoadTexture(L"../Resource/Sun.png");
        auto monster = mon->CreateComponent<testChar>();
        m_MonsterPool.push_back(monster);
    }

    testChar* monster = m_MonsterPool.back();
    monster->gameObject->isActive = true;
    m_MonsterPool.pop_back();
    return monster;
}

void WaveSystem::ReturnMonsterToPool(testChar* monster)
{
    m_MonsterPool.push_back(monster);
    monster->gameObject->isActive = false;
}

void WaveSystem::Update(float deltaTime)
{
    // ���Ͱ� �ʿ� �����ִ��� Ȯ���ϴ� �κ��� RemoveMonster�� �ƴ� �ٸ� �ý��ۿ��� ó��
    waveTimer -= deltaTime;  // deltaTime ��ŭ waveTimer ����
    if (waveTimer <= 0.0f)
    {
        StartNextWave();
    }
}

// SpawnWave �Լ�: ���� wave�� �ش��ϴ� ���͸� ����.  
void WaveSystem::SpawnWave()
{
    int numMonstersToSpawn = currentWave; // ���� ���̺� ��ȣ�� ���� ���� �� ����

    m_Monster.clear();  // ���� ���̺꿡�� ������ ���͸� ���� (�ʿ��� ���)

    for (int i = 0; i < numMonstersToSpawn; ++i)
    {
        // Ǯ���� ���͸� �����ɴϴ�.
        testChar* newMonster = GetMonsterFromPool();

        // �����ϰ� ���� �Ǵ� �����ʿ��� ����
        bool spawnOnLeft = rand() % 2 == 0;
        Vector2 spawnPosition;
        if (spawnOnLeft)
        {
            spawnPosition = Vector2(-600.0f, -240.0f);
        }
        else
        {
            spawnPosition = Vector2(600.0f, -240.0f);
        }
        newMonster->gameObject->transform->pos.worldPosition = spawnPosition;


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
        waveTimer = 1.0f;  // Ÿ�̸� �ʱ�ȭ
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
    /// ���͸� Ǯ�� ��ȯ
    for (testChar* monster : m_Monster)
    {
        ReturnMonsterToPool(monster);
    }
    m_Monster.clear();

    // Ǯ�� �ִ� ���͵��� ����
    for (testChar* monster : m_MonsterPool)
    {
        delete monster;
    }
    m_MonsterPool.clear();
}