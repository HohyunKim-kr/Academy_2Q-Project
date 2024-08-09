#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"

class SideMovement;
class BoxCollider;

class Bullet : public Component
{
public:
    Bullet();
    ~Bullet();

    void Init(float speed, const Vector2& direction);
    void Update(float deltaTime) override;
    void Reset();

    // Movement�� BoxCollider�� BulletFactory���� ����
    SideMovement* move;
    BoxCollider* pBoxcollider;

private:
    float speed;
    Vector2 direction;
};
