#include "BulletFactory.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
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
    bulletObj->transform->SetSortingLayer(INT_MAX);
    bulletObj->SetActive(false);
    auto spriteRenderer = bulletObj->CreateComponent<SpriteAnimation>();
    auto movement = bulletObj->CreateComponent<SideMovement>();  // SideMovement ���
    movement->freezeRotate = false;
    auto collider = bulletObj->CreateComponent<BoxCollider>();
    collider->ignoreEventSystem = true;
    collider->SetCollisionType(CollisionType::Overlap);

    spriteRenderer->LoadTexture(L"../Resource/arrow.png");  // �Ѿ� �ؽ�ó �ε�
 
    Bullet* bullet = bulletObj->CreateComponent<Bullet>();
    bullet->move = movement;
    bullet->pBoxcollider = collider;
    bullet->bulletFactory = this;

    SpriteAnimation* explode = bullet->gameObject->CreateComponent<SpriteAnimation>();
    bullet->explode = explode;
    bullet->bulletSprite = spriteRenderer;
    
    explode->LoadTexture(L"../Resource/30318.png");
    explode->LoadAnimationAsset(L"30318");
    explode->SetAnimation(1, false);


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
    bullet->gameObject->transform->SetSortingLayer(INT_MAX);
    
	SpriteAnimation* bulletSprite = bullet->gameObject->GetComponent<SpriteAnimation>();
	SpriteAnimation* explode = bullet->explode;
    if (bullet->id >= 30521 && bullet->id <= 30525) { //�ͷ� ���̵� �ڰ����϶�
        explode->LoadTexture(L"../Resource/30318.png");
        explode->LoadAnimationAsset(L"30318");

    }
    else if (bullet->id >= 30541 && bullet->id <= 30545) { //�ͷ� ���̵� ���ο�Ÿ���϶�
        explode->LoadTexture(L"../Resource/30318.png");
        explode->LoadAnimationAsset(L"30318");
    }
    m_BulletPool.pop_back();
    return bullet;
}

void BulletFactory::ReturnBulletToPool(Bullet* bullet)
{
    m_BulletPool.push_back(bullet);
    bullet->gameObject->isActive = false;
    bullet->gameObject->transform->pos.worldPosition = Vector2(0.f, 0.f);
    bullet->gameObject->transform->SetSortingLayer(INT_MIN);
    // �Ѿ� ���� �ʱ�ȭ
    bullet->Reset();
}
