#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"

#include <vector>

class Scene;
class testChar;
class WaveSystem : public Component
{
private:
    float waveTimer = 1.0f;   // Wave Ÿ�̸�
    int currentWave = 1;       // ���� ���� ���� wave
    static const int maxWave = 56; // �ִ� wave ��

    std::vector<testChar*> m_MonsterPool;
    std::vector<testChar*> m_Monster;

    // ���� Ǯ�� �ʱ� ũ��
    static const int initialPoolSize = 10;

    // Ǯ���� ���͸� �������� �޼���
    testChar* GetMonsterFromPool();
    // Ǯ�� ���͸� ��ȯ�ϴ� �޼���
    void ReturnMonsterToPool(testChar* monster);
    void InitializePool();         // Ǯ �ʱ�ȭ
public:
    Vector2 rightPos; 
    Vector2 leftPos;

    Scene* scene;

    virtual void Update(float deltaTime); // �� ������ ȣ��, wave Ÿ�̸� ������Ʈ
    void SpawnWave();              // ���ο� wave ����
    bool IsMapEmpty();             // �ʿ� ���Ͱ� �ϳ��� ������ Ȯ�� (���� �ʿ��� ��� ���)
    virtual ~WaveSystem(); // �Ҹ��� ����
private:
    void StartNextWave();          // ���� wave�� �Ѿ��

};

