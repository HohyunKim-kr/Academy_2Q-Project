#include "Enemy.h"
//#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Scene.h"

class SpriteRenderer;
class SwordMan : public Enemy
{
public:
    SwordMan() = default;
    void Init();  // ������ Init �޼���
    void Update(float delta) override;
    void Render(D2D1_MATRIX_3X2_F cameraMat) override;

    //void Attack();
    // ������ ���
    Movement* move;
    BoxCollider* pBoxcollider;
    float tmpY;
    SpriteRenderer* loadMon;
    float elapsedTime;
private:
   
};
