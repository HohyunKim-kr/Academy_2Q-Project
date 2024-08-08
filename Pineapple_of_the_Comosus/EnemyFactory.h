#pragma
#include "SwordMan.h"
#include "BombCart.h"
#include "Griffin.h"
#include "HeavyKnight.h"
#include "MusketShooter.h"
//#include "../D2DEngine/Scene.h"

class Scene;
class EnemyFactory 
{
public:
    EnemyFactory(Scene* scene) : scene(scene) {}

    // ���� �����ϴ� �޼���
    Enemy* CreateEnemy(int type);

private:
    Scene* scene;
};

