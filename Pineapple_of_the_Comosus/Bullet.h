#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/Collider.h"

class SideMovement;
class BoxCollider;
class BulletFactory;
class Bullet : public Component, public IColliderNotify
{
public:
    Bullet();
    ~Bullet();

    //void Init(float speed, const Vector2& direction);
    void Update(float deltaTime) override;
    void Reset();

    void SetAttackValue(const Vector2& direction, float _bombRange, float _attackPower, int _penetratingPower, float _moveSpeed, float _slowPower, float _slowTime);

    // Movement�� BoxCollider�� BulletFactory���� ����
    SideMovement* move;
    BoxCollider* pBoxcollider;

    BulletFactory* bulletFactory;
private:
    float bombRange = 0.f;
    float attackPower = 0.f;
    int penetratingPower = 0;
    float moveSpeed = 0.f;
    float slowPower = 0.f;
    float slowTime = 0.f;

private:
    // IColliderNotify��(��) ���� ��ӵ�
    void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};
