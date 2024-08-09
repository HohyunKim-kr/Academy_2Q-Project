#include "Bullet.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "Enemy.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Init(float initSpeed, const Vector2& initDirection)
{
    speed = initSpeed;
    direction = initDirection;

    if (move)
    {
        // ���� ����
        //move->SetDirection(D2D1_VECTOR_2F{ direction.x, direction.y });

        // �ӵ� ����
        //move->SetSpeed(speed);

        move->AddForce(direction * speed);
    }
}

void Bullet::Update(float deltaTime)
{
    

    // BoxCollider�� ����� �浹 ó��
    // �浹 ó���� ���õ� ������ ���⼭ ������ �� ����
    if (pBoxcollider)
    {
        AABB bound = pBoxcollider->GetBound();
        if (bound.m_Center.x < 0 || bound.m_Center.x > 1920 ||
            bound.m_Center.y < 0 || bound.m_Center.y > 1080)
        {
            // ȭ�� ������ ������ �Ѿ��� ��Ȱ��ȭ
            //gameObject->isActive = false;
        }
    }
}

void Bullet::Reset()
{
    // �Ѿ��� ���¸� �ʱ�ȭ
    if (move)
    {
        move->SetSpeed(0.0f);
        move->SetDirection(D2D1_VECTOR_2F{ 0.0f, 0.0f });
    }

    // �ڽ� �ݶ��̴� �ʱ�ȭ (�ʿ��)
    if (pBoxcollider)
    {
        pBoxcollider->SetCenter(Vector2(0.0f, 0.0f));
        pBoxcollider->SetExtent(Vector2(50.0f, 50.0f));
    }

    // ��Ÿ �ʿ��� �ʱ�ȭ �ڵ��
    speed = 0.0f;
    direction = Vector2(0.0f, 0.0f);
}

void Bullet::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Bullet::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
    auto e = pOtherComponent->gameObject->GetComponent<Enemy>();
    if(e!= nullptr)
        gameObject->isActive = false;
}

void Bullet::OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Bullet::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}
