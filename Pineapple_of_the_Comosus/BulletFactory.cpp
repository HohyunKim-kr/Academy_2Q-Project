#include "BulletFactory.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/GameObject.h"
#include "Bullet.h"


BulletFactory::BulletFactory(Scene* scene)
    : scene(scene)
{
    InitializePool();
}

BulletFactory::~BulletFactory()
{
    m_BulletPool.clear();
}

void BulletFactory::InitializePool()
{
    for (int i = 0; i < initialPoolSize; ++i)
    {
        auto bullet = CreateBullet();  // Bullet ����
        bullet->gameObject->isActive = false;
        m_BulletPool.push_back(bullet);
    }
}

Bullet* BulletFactory::CreateBullet()
{
    auto bulletObj = scene->CreateGameObject<GameObject>();
    auto spriteRenderer = bulletObj->CreateComponent<SpriteRenderer>();
    auto movement = bulletObj->CreateComponent<SideMovement>();  // SideMovement ���
    auto collider = bulletObj->CreateComponent<BoxCollider>();
    collider->SetCollisionType(CollisionType::Overlap);

    spriteRenderer->LoadTexture(L"../Resource/circle.png");  // �Ѿ� �ؽ�ó �ε�

    Bullet* bullet = bulletObj->CreateComponent<Bullet>();
    bullet->move = movement;
    bullet->pBoxcollider = collider;

    return bullet;
}

Bullet* BulletFactory::GetBulletFromPool()
{
    if (m_BulletPool.empty())
    {
        auto bullet = CreateBullet();  // Ǯ�� �Ѿ��� ������ ���� ����
        m_BulletPool.push_back(bullet);
    }

    Bullet* bullet = m_BulletPool.back();
    bullet->gameObject->isActive = true;
    m_BulletPool.pop_back();
    return bullet;
}

void BulletFactory::ReturnBulletToPool(Bullet* bullet)
{
    m_BulletPool.push_back(bullet);
    bullet->gameObject->isActive = false;

    // �Ѿ� ���� �ʱ�ȭ
    bullet->Reset();
}
