#include "Bullet.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/Scene.h"
#include "BulletFactory.h"
#include "Enemy.h"
#include "EnemyColliderNotify.h"



Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

//void Bullet::Init(float initSpeed, const Vector2& initDirection)
//{
//    speed = initSpeed;
//    direction = initDirection;
//
//    if (move)
//    {
//        // ���� ����
//        //move->SetDirection(D2D1_VECTOR_2F{ direction.x, direction.y });
//
//        // �ӵ� ����
//        //move->SetSpeed(speed);
//
//        move->AddForce(direction * speed);
//    }
//}

void Bullet::Update(float deltaTime)
{
    

    // BoxCollider�� ����� �浹 ó��
    // �浹 ó���� ���õ� ������ ���⼭ ������ �� ����
    //if (pBoxcollider)
    //{
    //    AABB bound = pBoxcollider->GetBound();
    //    if (bound.m_Center.x < 0 || bound.m_Center.x > 1920 ||
    //        bound.m_Center.y < 0 || bound.m_Center.y > 1080)
    //    {
    //        // ȭ�� ������ ������ �Ѿ��� ��Ȱ��ȭ
    //        //gameObject->isActive = false;
    //    }
    //}
    float x = gameObject->transform->m_WorldTransform.dx;
    float y = gameObject->transform->m_WorldTransform.dy;
    if (x < -1920.f || x > 1920.f || y < -600.f || y > 1600.f) {
        bulletFactory->ReturnBulletToPool(this);
    }
    OnGround();
}

void Bullet::Reset()
{
    gameObject->transform->pos.worldPosition = { 0.f, 0.f };
    // �Ѿ��� ���¸� �ʱ�ȭ
    if (move)
    {
        move->SetSpeed(0.0f);
        move->SetDirection(Vector2{ 0.0f, 0.0f });
    }

    // �ڽ� �ݶ��̴� �ʱ�ȭ (�ʿ��)
    if (pBoxcollider)
    {
        pBoxcollider->SetCenter(Vector2(0.0f, 0.0f));
        pBoxcollider->SetExtent(Vector2(50.0f, 50.0f));
    }

    // ��Ÿ �ʿ��� �ʱ�ȭ �ڵ��
    //speed = 0.0f;
    //direction = Vector2(0.0f, 0.0f);

    bombRange = 0.f;
    attackPower = 0.f;
    penetratingPower = 0;
    moveSpeed = 0.f;
    slowPower = 0.f;
    slowTime = 0.f;
}

void Bullet::SetAttackValue(const Vector2& direction, float _bombRange, float _attackPower, int _penetratingPower, float _moveSpeed, float _slowPower, float _slowTime, BulletType _bulletType)
{
    bombRange = _bombRange;
    attackPower = _attackPower;
    penetratingPower = _penetratingPower;
    moveSpeed = _moveSpeed;
    slowPower = _slowPower;
    slowTime = _slowTime;
    bulletType = _bulletType;

    if (move)
    {
        Vector2 dir = direction;
        move->AddForce(dir * moveSpeed);
    }
}

void Bullet::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Bullet::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
    auto e = pOtherComponent->gameObject->GetComponent<EnemyColliderNotify>();
    if (e != nullptr) {

        //gameObject->isActive = false;
        if (bombRange > 0.f) {
            
        }
        penetratingPower--;
        /*e->gameObject->isActive = false;
        e->gameObject->GetComponent<FiniteStateMachine>()->SetState("Dead");*/
        e->enemy->Ondamage(attackPower,bulletType);
        std::cout << "bulletID: " <<gameObject->GetInstanceID() << "instanceid: " << e->GetInstanceID() << std::endl;
        if (penetratingPower <= 0) {
            gameObject->isActive = false;
            if (bulletType == BulletType::burst) {
                OnBurst(bombRange);
            }
            bulletFactory->ReturnBulletToPool(this);
        }
    }
}

void Bullet::OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Bullet::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Bullet::OnGround()
{
    if (gameObject->transform->pos.worldPosition.y < -300) {
        gameObject->isActive = false;
        if (bulletType == BulletType::burst) {
            OnBurst(bombRange);
        }
        bulletFactory->ReturnBulletToPool(this);
			
    }
	
}

void Bullet::OnBurst(float _bombRange) {
    auto iter = gameObject->ownerScene->m_GameObjects.begin();
    for(iter; iter != gameObject->ownerScene->m_GameObjects.end(); iter++) {
		auto e = (*iter)->GetComponent<EnemyColliderNotify>();
        if(e == nullptr || e->enemy == nullptr) continue;
        else if(e->enemy->gameObject->transform->pos.worldPosition.x > gameObject->transform->pos.worldPosition.x - _bombRange &&
			e->enemy->gameObject->transform->pos.worldPosition.x < gameObject->transform->pos.worldPosition.x + _bombRange &&
			e->enemy->gameObject->transform->pos.worldPosition.y > gameObject->transform->pos.worldPosition.y - _bombRange &&
			e->enemy->gameObject->transform->pos.worldPosition.y < gameObject->transform->pos.worldPosition.y + _bombRange) {
			e->enemy->Ondamage(attackPower, bulletType);
		}
	}

}
