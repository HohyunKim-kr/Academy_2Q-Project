#pragma once  // #pragma once�� ��� ������ �� ���� ���Եǵ��� �����մϴ�.

#include "SwordMan.h"
#include "BombCart.h"
#include "Griffin.h"
#include "HeavyKnight.h"
#include "MusketShooter.h"
#include "../D2DEngine/Scene.h"  // Scene ����� �����մϴ�.

#include <vector>
#include <random>

class EnemyFactory
{
public:
    EnemyFactory(Scene* scene);
    ~EnemyFactory();

    // ���� �����ϴ� �޼���
    Enemy* CreateEnemy(int type);

    // ���� ���� �����ϴ� �޼���
    Enemy* CreateRandomEnemy();

    // Ǯ���� ���� �������� �޼���
    Enemy* GetEnemyFromPool();

    // ���� Ǯ�� ��ȯ�ϴ� �޼���
    void ReturnEnemyToPool(Enemy* enemy);

    void InitializePool(); // �� Ǯ �ʱ�ȭ �޼���
private:
    

    Scene* scene;
    std::vector<Enemy*> m_EnemyPool;  // �� Ǯ�� �����ϴ� ����
    const int initialPoolSize = 20;   // �ʱ� Ǯ ũ�� (���Ƿ� ����, �ʿ信 ���� ���� ����)
};
