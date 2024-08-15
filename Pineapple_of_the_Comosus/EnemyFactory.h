#pragma once  // #pragma once�� ��� ������ �� ���� ���Եǵ��� �����մϴ�.

#include "SwordMan.h"
#include "BombCart.h"
#include "Griffin.h"
#include "HeavyKnight.h"
#include "MusketShooter.h"
#include "../D2DEngine/Scene.h"  // Scene ����� �����մϴ�.

#include <vector>
#include <unordered_map>
#include <random>
class BulletFactory;
class MainPineApple;
class EnemyFactory
{
public:
    int enemyType;
    EnemyFactory(Scene* scene);
    ~EnemyFactory();

    // ���� �����ϴ� �޼���
    Enemy* CreateEnemy(int type);

    // ���� ���� �����ϴ� �޼���
    Enemy* CreateRandomEnemy();

    // Ǯ���� ���� �������� �޼���
    Enemy* GetEnemyFromPool(int type);

    // ���� Ǯ�� ��ȯ�ϴ� �޼���
    void ReturnEnemyToPool(Enemy* enemy);

    void InitializePool(); // �� Ǯ �ʱ�ȭ �޼���

    BulletFactory* bulletFactory;
    MainPineApple* mainPineApple;
private:
    Scene* scene;

    std::unordered_map<std::wstring, std::vector<Enemy*>> enemyPool;

    std::vector<Enemy*> m_EnemyPool;  // �� Ǯ�� �����ϴ� ����
    const int initialPoolSize = 20;   // �ʱ� Ǯ ũ�� (���Ƿ� ����, �ʿ信 ���� ���� ����)
};
