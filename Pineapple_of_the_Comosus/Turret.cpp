#include "Turret.h"
#include "BulletFactory.h"
#include "MainPineApple.h"
#include "Bullet.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "DynamicData.h"
#include "../D2DEngine/SoundManager.h"
void Turret::Init()
{
    auto data = dynamicData->GetStaticTurretData(turretType);
    auto rewardData = dynamicData->GetRewardTurretData(turretType);
    float shootTimer = data->fireRate + rewardData.fireRate;

    timeSinceLastShot = 0.f;
}

void Turret::Update(float delta)
{
    __super::Update(delta);
    // 총알을 발사할 조건이 만족되면 발사
    auto data = dynamicData->GetStaticTurretData(turretType);
    auto rewardData = dynamicData->GetRewardTurretData(turretType);
    float shootTimer = data->fireRate + rewardData.fireRate;
    shootTimer = 1.f / shootTimer;

    timeSinceLastShot += delta;

    if (timeSinceLastShot >= shootTimer)
    {
        Shoot();
        timeSinceLastShot -= shootTimer;  // 타이머 초기화
    }

    reboundTime += delta;
    if (reboundTime >= 1.f) reboundTime = 1.f;

    float lerpX = rebound.x * (1.f - reboundTime);
    float lerpY = rebound.y * (1.f - reboundTime);

    gameObject->transform->pos.worldPosition = { lerpX, lerpY };
}

void Turret::Shoot()
{
    if (turretType != TurretType::GrowthPromoter) {
        if (parentPineApple->bulletFactory)
        {
            // BulletFactory에서 Bullet을 가져온다
            Bullet* bullet = parentPineApple->bulletFactory->GetBulletFromPool();
            // 총알의 위치를 MusKetShooter의 위치로 설정
            bullet->gameObject->transform->pos.worldPosition = { fireTr->transform->m_WorldTransform.dx, fireTr->transform->m_WorldTransform.dy };

            // 총알 초기화 (속도와 방향 설정)
            Vector2 shootDirection = { 1.0f, 0.0f };  // 예를 들어 오른쪽으로 발사

            float angle = gameObject->transform->m_RelativeRotation;
            shootDirection.x = std::cosf(angle / 180.f * 3.14159f);
            shootDirection.y = std::sinf(angle / 180.f * 3.14159f);

            auto data = dynamicData->GetStaticTurretData(turretType);//DataManager::GetInstance().GetTurretData((int)turretType);
            auto rewardData = dynamicData->GetRewardTurretData(turretType);
            //float bulletSpeed = 1000.0f;
            //bullet->Init(bulletSpeed, shootDirection);

            reboundTime = 0.f;
            rebound = shootDirection * float(data->damage + rewardData.damage) * -1.f;

            bullet->SetAttackValue(shootDirection,
                data->id,
                data->burstRange + rewardData.burstRange,
                data->damage + rewardData.damage,
                data->penetration + rewardData.penetration,
                data->bulletSpeed + rewardData.bulletSpeed,
                data->slowRate + rewardData.slowRate,
                data->slowDuration + rewardData.slowDuration,
                static_cast<BulletType>(data->bulletType));
            bullet->bulletSprite->LoadTexture(data->bulletImagePath);
            auto spr = bullet->bulletSprite;
            switch (turretType)
            {
            case TurretType::Crossbow:
                SoundManager::GetInstance().PlaySoundW(L"CrossbowFire_Se", false);

                spr->LoadAnimationAsset(L"30306");
                spr->SetAnimation(0, false);
                break;
            case TurretType::Musket:
                SoundManager::GetInstance().PlaySoundW(L"MusketFire_Se", false);

                spr->LoadAnimationAsset(L"30307");
                spr->SetAnimation(0, false);
                break;
            case TurretType::Cannon:
                SoundManager::GetInstance().PlaySoundW(L"MortarFire_Se", false);

                bullet->explode->LoadTexture(L"../Resource/30318.png");
                bullet->explode->LoadAnimationAsset(L"30318");

                spr->LoadAnimationAsset(L"30308");
                spr->SetAnimation(0, false);
                break;
            case TurretType::SuperCrossbow:
                SoundManager::GetInstance().PlaySoundW(L"SuperCrossbowFire_Se", false);

                spr->LoadAnimationAsset(L"30306");
                spr->SetAnimation(0, false);
                break;
            case TurretType::SlowWand:
                SoundManager::GetInstance().PlaySoundW(L"SlowWandFire_Se", false);

                bullet->explode->LoadTexture(L"../Resource/30319.png");
                bullet->explode->LoadAnimationAsset(L"30319");

                spr->LoadAnimationAsset(L"30309");
                spr->SetAnimation(0, false);
                break;
            case TurretType::GrowthPromoter:
                //SoundManager::GetInstance().PlaySoundW(L"MortarFire_Se", false);

                spr->LoadAnimationAsset(L"30308");
                spr->SetAnimation(0, false);
                break;
            }
        }
    }
    else {
        if (parentPineApple->rewardData->isHarvest == true) return;
        auto data = dynamicData->GetStaticTurretData(turretType);
        auto rewardData = dynamicData->GetRewardTurretData(turretType);
        parentPineApple->AddExp(data->damage + rewardData.damage);
    }
}

void Turret::SelectTurret()
{
    selectOutline->gameObject->isActive = true;
    auto data = dynamicData->GetStaticTurretData(turretType);
    selectOutline->LoadTexture(data->highlightPath.c_str());
}

void Turret::DeSelectTurret()
{
    selectOutline->gameObject->isActive = false;
    auto data = dynamicData->GetStaticTurretData(turretType);
    selectOutline->LoadTexture(data->highlightPath.c_str());
}

void Turret::Refund()
{
    if (gameObject->isActive == false) return;

    int refund = DataManager::GetInstance().GetTurretData((int)turretType)->refund;
    parentPineApple->acquireGold(refund);
    //std::cout << "refund : " << refund << std::endl;
    ResetTurret();
}

void Turret::ResetTurret()
{
    prevAngle = 0.f;
    currAngle = 0.f;
    gameObject->transform->m_RelativeRotation = 0.f;
    gameObject->isActive = false;
}

void Turret::UpdateTurretImage()
{
    if (gameObject->isActive == false) return;
    auto lv = dynamicData->GetTurretLevel(turretType);
    anim->LoadAnimationAsset(dynamicData->GetStaticTurretData(turretType)->csvPath.c_str());
	anim->SetAnimation(lv, false);
}
