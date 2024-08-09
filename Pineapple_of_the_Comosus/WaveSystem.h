#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/Movement.h"
#include <vector>

class Scene;
class Enemy;
class EnemyFactory;
class BulletFactory;

class WaveSystem : public Component
{
private:
    float waveTimer = 1.0f;   // Wave Ÿ�̸�
    int currentWave = 1;       // ���� ���� ���� wave
    static const int maxWave = 56; // �ִ� wave ��

    std::vector<Enemy*> m_EnemyPool; 
    std::vector<Enemy*> m_Enemies;   

    // ���� Ǯ�� �ʱ� ũ��
    static const int initialPoolSize = 10;
    
    
public:
    EnemyFactory* enemyFactory;  
    BulletFactory* bulletFactory;
    Vector2 rightPos; 
    Vector2 leftPos;

    Scene* scene = nullptr;
    // Ǯ���� ���͸� �������� �޼���
    //Enemy* GetEnemyFromPool(); // SwordMan -> Enemy�� ����
    //void ReturnEnemyToPool(Enemy* enemy); // SwordMan -> Enemy�� ����
    //void InitializePool();         // Ǯ �ʱ�ȭ
    int getCurrentWave() { return currentWave; }
    virtual void Init();
    virtual void Update(float deltaTime); // �� ������ ȣ��, wave Ÿ�̸� ������Ʈ
    void SpawnWave();              // ���ο� wave ����
    bool IsMapEmpty();             // �ʿ� ���Ͱ� �ϳ��� ������ Ȯ�� (���� �ʿ��� ��� ���)
    WaveSystem();
    virtual ~WaveSystem(); // �Ҹ��� ����
private:
    void StartNextWave();          // ���� wave�� �Ѿ��

};

