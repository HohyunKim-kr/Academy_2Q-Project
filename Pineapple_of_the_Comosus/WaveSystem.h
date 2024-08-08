#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/Movement.h"
#include <vector>

class Scene;
class Enemy;
class SwordMan;
class WaveSystem : public Component
{
private:
    float waveTimer = 1.0f;   // Wave Ÿ�̸�
    int currentWave = 1;       // ���� ���� ���� wave
    static const int maxWave = 56; // �ִ� wave ��

    std::vector<SwordMan*> m_MonsterPool;
    std::vector<SwordMan*> m_Monster;

    // ���� Ǯ�� �ʱ� ũ��
    static const int initialPoolSize = 10;

    // Ǯ���� ���͸� �������� �޼���
    SwordMan* GetMonsterFromPool();
    // Ǯ�� ���͸� ��ȯ�ϴ� �޼���
    void ReturnMonsterToPool(SwordMan* monster);
    void InitializePool();         // Ǯ �ʱ�ȭ
public:
    Vector2 rightPos; 
    Vector2 leftPos;

    Scene* scene;

    int getCurrentWave() { return currentWave; }
    virtual void Update(float deltaTime); // �� ������ ȣ��, wave Ÿ�̸� ������Ʈ
    void SpawnWave();              // ���ο� wave ����
    bool IsMapEmpty();             // �ʿ� ���Ͱ� �ϳ��� ������ Ȯ�� (���� �ʿ��� ��� ���)
    virtual ~WaveSystem(); // �Ҹ��� ����
private:
    void StartNextWave();          // ���� wave�� �Ѿ��

};

