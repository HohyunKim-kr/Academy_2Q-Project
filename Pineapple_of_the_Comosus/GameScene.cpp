#include "GameScene.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/SoundManager.h"
#include "../D2DEngine/InputManager.h"
#include <iostream>
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteRenderer.h"
#include"../D2DEngine/ImageUIRenderer.h"
#include"../D2DEngine/SceneManager.h"
#include "../D2DEngine/Button.h"
#include "../D2DEngine/BoxCollider.h"
#include "EnemyFactory.h"
#include "TurretUI.h"
#include "GamePlayManager.h"
#include "MainPineApple.h"
#include "SelectTurretContainer.h"
#include "BulletFactory.h"
#include "Turret.h"
#include "PineAppleTile.h"
#include "../D2DEngine/CircleCollider.h"
#include "../D2DEngine/TextUIRenderer.h"
#include "DataManager.h"
#include "DynamicData.h"
#include "Comosus.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "FSMHarvest.h"
#include <functional>
#include <algorithm>
#include "ramdomReward.h"
#include <random> // 랜덤시드

MainPineApple* testPineApple = nullptr;

GameScene::GameScene() {
    std::cout << "GameScene Constructor" << std::endl;
}

GameScene::~GameScene() {
    std::cout << "GameScene Destructor" << std::endl;
}

void GameScene::Start() {
    std::cout << "Entering GameScene" << std::endl;

    auto camera = CreateGameObject<GameObject>();
    auto pCam = camera->CreateComponent<Camera>();
    SetMainCamera(pCam);

    auto bulletFactory = new BulletFactory(this);

    //데이터 매니저 초기화
    auto& DataManager = DataManager::GetInstance();
    DataManager.LoadEnemySheetFromCSV(L"../Resource/EnemyData.csv");
    DataManager.LoadTurretSheetFromCSV(L"../Resource/TurretData.csv");
    DataManager.LoadWaveSheetFromCSV(L"../Resource/WaveData");

    // 게임 매니저 드래그엔 드롭, 파인애플 설치, 터렛 파인애플 몹 데이터 등을 관리함.
    auto gmObj = CreateGameObject<GameObject>();
    auto GameManager = gmObj->CreateComponent<GamePlayManager>();
    auto dynamicData = gmObj->CreateComponent<DynamicData>();
    dynamicData->Init();

    // pineapple random reward
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"단단한 껍질",L"최대체력 +50",[dynamicData]() {dynamicData->rewardPineAppleStat.maxHp += 50; }});
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"광기어린 광합성",L"광합성 +1",[dynamicData]() {dynamicData->rewardPineAppleStat.solarGain += 1; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"성장의 햇빛",L"햇빛 +1", [dynamicData]() {dynamicData->rewardPineAppleStat.morningValue += 1; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"성장의 달빛",L"달빛 +2",[dynamicData]() {dynamicData->rewardPineAppleStat.nightValue += 2; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"질 좋은 양분들",L"경험치량 +1",[dynamicData]() {dynamicData->rewardPineAppleStat.killMultiply += 0.1f; } });

    // comosus light reward
    // DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"성장의 달빛",[dynamicData]() {dynamicData->rewardPineAppleStat.nightValue += 2; } });
    // DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"질 좋은 양분들",[dynamicData]() {dynamicData->rewardPineAppleStat.offeringMultiply -= 0.1f; } });

    // Crossbow tower reward
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"석궁피해량",L"공격력 +2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow].damage += 2.f; }});
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"석궁 공격속도+",L"공격속도 +0.2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow].bulletSpeed += 0.2f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"석궁 관통력+",L"관통력 +1",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow].penetration += 1; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"무거운 화살촉",L"공격력 +5, 투사체 속도 -3.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow].damage += 5.f; dynamicData->rewardTurretStat[TurretType::Crossbow].damage -= 3.f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"독이 발린 화살촉",L"이동속도 감소량 +8%, 이동속도 감소 지속시간 3.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow].slowRate += 8.f; dynamicData->rewardTurretStat[TurretType::Crossbow].slowDuration += 3.f; } });

    // musket tower reward
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"머스킷 피해량+",L"머스킷타워 공격력 +2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Musket].damage += 2.f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"머스킷 공격속도+",L"머스킷타워 공격속도 +0.15",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Musket].bulletSpeed += 0.15f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"머스킷 관통력+",L"머스킷타워 관통력 +2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Musket].penetration += 2.f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"대구경 탄환",L"머스킷타워 공격속도 -0.3, 머스킷타워 관통력 +5",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Musket].bulletSpeed -= 0.3f; dynamicData->rewardTurretStat[TurretType::Musket].penetration += 5; } });

    // Cannon tower reward
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"박격포 피해량+",L"박격포타워 공격력 +2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].damage += 2; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"박격포 공격속도+",L"박격포타워 공격속도 +0.1",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].bulletSpeed += 0.1f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"박격포 관통력+",L"박격포타워 관통력 +1",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].penetration += 1; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"더많은 작약",L"폭밤범위 +15",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].burstRange += 15; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"포탄 경량화",L"폭발범위 -10, 투사체속도",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].burstRange -= 10;  } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"포탄 중량화",L"폭발범위 +35, 공격속도 -0.1",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].burstRange += 35; dynamicData->rewardTurretStat[TurretType::Cannon].bulletSpeed -= 10; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"제압탄",L"이동속도 감소 +15%, 이동속도 지속시간 +2.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].slowRate += 15.f; dynamicData->rewardTurretStat[TurretType::Cannon].slowDuration += 2.f; } });

    // superarrow tower reward
    //DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"독이 발린 화살촉",L"이동속도 감소량 +8%, 이동속도 감소 지속시간 3.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].slowRate += 15.f; dynamicData->rewardTurretStat[TurretType::Cannon].slowDuration += 2.f; });

    //slow wand
    //DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"독이 발린 화살촉",L"이동속도 감소량 +8%, 이동속도 감소 지속시간 3.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow]. += 2.f; } });
    //DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"독이 발린 화살촉",L"이동속도 감소량 +8%, 이동속도 감소 지속시간 3.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow]. += 2.f; } });

    ////
    //DataManager.harvestPopupStruct.push_back({ L"../Resource/30201.png",L"독이 발린 화살촉",L"이동속도 감소량 +8%, 이동속도 감소 지속시간 3.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow]. += 2.f; } });


    GameManager->camera = pCam;
    auto boxObj = CreateGameObject<GameObject>();
    boxObj->SetActive(false);
    auto boxColl = boxObj->CreateComponent<BoxCollider>();
    boxColl->ignoreEventSystem = true;
    boxColl->SetCollisionType(CollisionType::Overlap);
    auto selector = boxObj->CreateComponent<SelectTurretContainer>();
    GameManager->selectBoxObj = boxObj;
    GameManager->multiSelectBox = boxColl;
    GameManager->selectTurrets = selector;


    // 드래그 시 이미지 보여줄 오브젝트
    auto testDragObj = CreateGameObject<GameObject>();
    testDragObj->SetActive(false);
    auto sproper = testDragObj->CreateComponent<SpriteRenderer>();
    sproper->alpha = 0.7f;
    GameManager->dragObj = testDragObj;
    testDragObj->transform->SetSortingLayer(1);

    // 코모서스 파인애플 (겁나 큼)
    auto paObj = CreateGameObject<GameObject>();
    paObj->transform->SetSortingLayer(-1);
    paObj->transform->pos.worldPosition = { 0.f, 0.f };
    auto pineApple = paObj->CreateComponent<MainPineApple>();

    // 상태 생성
    /*auto pineFSM = paObj->CreateComponent<FiniteStateMachine>();
    pineApple->fsm = pineFSM;
    pineFSM->CreateState<TentacleDefault>("harveststart");
    pineFSM->CreateState<TentacleDownState>("TentacleDownState");
    pineFSM->CreateState<TentacleUpState>("TentacleUpState");
    pineFSM->CreateState<ShowPopupState>("ShowPopupState");*/

    pineApple->rewardData = dynamicData;
    testPineApple = pineApple;
    pineApple->bulletFactory = bulletFactory;
    auto pineappleSpr = paObj->CreateComponent<SpriteRenderer>();
    pineappleSpr->SetCenter({ 0.5f, 0.67f });
    pineappleSpr->LoadTexture(L"../Resource/pineApple_Actual.png");
    auto pineColl = paObj->CreateComponent<BoxCollider>();
    pineColl->ignoreEventSystem = true;
    pineColl->isKinemetic = true;
    pineColl->SetCenter({ 300.f, 100.f });
    pineColl->SetExtent({ 0.f, 400.f });
    pineColl = paObj->CreateComponent<BoxCollider>();
    pineColl->ignoreEventSystem = true;
    pineColl->isKinemetic = true;
    pineColl->SetCenter({ -300.f, 100.f });
    pineColl->SetExtent({ 0.f, 400.f });

    // 코모서스 강림
    auto comoObj = CreateGameObject<GameObject>();
    comoObj->transform->pos.worldPosition = { 0.f,250.f };
    auto comosus = comoObj->CreateComponent<Comosus>();
    comoObj->transform->SetSortingLayer(100);
    auto comsusSpr = comoObj->CreateComponent<SpriteAnimation>();
    Texture* t = nullptr;
    ResourceManager::GetInstance().CreateTextureFromFile(L"../Resource/30722_tentacle_animation.png", &t);
    comsusSpr->m_pTexture = t;
    comsusSpr->LoadAnimationAsset(L"Comosus");
    comsusSpr->SetAnimation(0, false);
    pineApple->comosus = comsusSpr;

    GameManager->pineApple = pineApple;
    // 파인애플 타일들
    {
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -3.f, 190.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -85.f, 120.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 80.f, 120.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -3.f, 53.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -85.f, -16.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 80.f, -16.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -3.f, -84.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -85.f, -154.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 80.f, -154.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -3.f, -220.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -165.f, 53.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 158.f, 53.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -165.f, -84.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 158.f, -84.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -155.f, 190.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 150.f, 190.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -155.f, -220.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 150.f, -220.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
    }


    // 사운드 초기화 및 로드
    SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/hello.mp3");
    SoundManager::GetInstance().SetVolume(L"backgroundMusic", 0.5f);
    SoundManager::GetInstance().PlaySoundW(L"backgroundMusic", true);

    // 배경 이미지
    auto bgObj = CreateGameObject<GameObject>();
    bgObj->transform->SetSortingLayer(-10);
    auto bgSpr = bgObj->CreateComponent<SpriteRenderer>();
    bgSpr->LoadTexture(L"../Resource/morningBG.png");

    // 메뉴바
    auto uiObj = CreateGameObject<GameObject>();
    auto uiImage = uiObj->CreateComponent<ImageUIRenderer>();
    uiObj->transform->type = Type::Ui;
    uiObj->transform->pos.rectposition = { {180,0} ,{1560 + 180,200} };
    uiImage->LoadTexture(L"../Resource/30401.png");

    // 웨이브 시스템
    auto waveObj = CreateGameObject<GameObject>();
    waveSystem = waveObj->CreateComponent<WaveSystem>();
    waveSystem->scene = this;
    waveSystem->bulletFactory = bulletFactory;
    waveSystem->mainPineApple = GameManager->pineApple;
    waveSystem->Init();


    // DayNightCycleComponent 생성 및 게임 오브젝트에 추가
    auto nightObj = CreateGameObject<GameObject>();
    nightSystem = nightObj->CreateComponent<DayNightCycle>();
    waveSystem->dayNightCycle = nightSystem;

    // 해 이미지
    auto sunObj = CreateGameObject<GameObject>();
    sunObj->transform->SetSortingLayer(-9);
    auto sunSpr = sunObj->CreateComponent<SpriteRenderer>();
    sunSpr->LoadTexture(L"../Resource/BGSun.png");
    sunObj->transform->pos.worldPosition = { 800.f, 400.f };
    nightSystem->m_Sun = sunObj;

    // 달 이미지
    auto moonObj = CreateGameObject<GameObject>();
    moonObj->transform->SetSortingLayer(-9);
    auto moonSpr = moonObj->CreateComponent<SpriteRenderer>();
    moonSpr->LoadTexture(L"../Resource/BGMoon.png");
    moonObj->transform->pos.worldPosition = { 800.f, -300.f };
    nightSystem->m_Moon = moonObj;


    // 내부 컴포넌트 포인터 주소 연결
    //nightSystem->waveSystem = waveSystem;


    // 터렛 UI
    float spacing = 20.0f;
    float startX = 0.f;
    float width = 120.f;

    //std::vector<Button*> btn;
    // 이미지 파일 경로 배열
    std::wstring turretImages[] = {
        L"../Resource/30201.png",
        L"../Resource/30202.png",
        L"../Resource/30203.png",
        L"../Resource/30204.png",
        L"../Resource/30205.png",
        L"../Resource/30206.png"
    };

    // UI 생성 및 이미지 설정 코드
    std::vector<Button*> btn;

    for (size_t i = 0; i < 6; i++) {
        auto turretUI = CreateGameObject<GameObject>();
        float startX = i * (spacing + width);
        turretUI->transform->SetParent(uiObj->transform);
        turretUI->transform->type = Type::Ui;
        turretUI->transform->pos.rectposition = { {startX + spacing, 60.f} ,{120.f + startX + spacing, 180.f} };

        //auto backImage = turretUI->CreateComponent<ImageUIRenderer>();
        //backImage->ignoreEventSystem = true; 

        // 각 터렛 UI에 대해 다른 이미지 로드
        //backImage->LoadTexture(turretImages[i]);

        // 변경사항 터렛UI
        auto turretUIChild = CreateGameObject<GameObject>();
        turretUIChild->transform->SetParent(turretUI->transform);
        turretUIChild->transform->type = Type::Ui;
        turretUIChild->transform->pos.rectposition = { {0.f, 0.f} ,{120.f, 120.f} };


        auto turretButton = turretUIChild->CreateComponent<Button>();
        turretButton->LoadTexture(turretImages[i]);
        //turretButton->LoadTexture(L"../Resource/turret.png");  // 버튼의 이미지는 고정
        auto turretUIComp = turretUIChild->CreateComponent<TurretUI>();
        turretUIComp->SetIndex(30501 + (10*i));
        turretUIComp->pApple = pineApple;
        turretUIComp->SetTurret((TurretType)(30501 + (10 * i)));

        btn.push_back(turretButton);
        // 터렛 버튼 클릭 시 동작 정의
        //turretButton->AddListener([GameManager, turretUIComp]() {GameManager->StartBatch(turretUIComp->GetIndex()); });

        auto blackGround = turretUIChild->CreateComponent<ImageUIRenderer>();
        turretUIComp->blockImage = blackGround;
        blackGround->ignoreEventSystem = true;
        blackGround->LoadTexture(L"../Resource/blackGround.png");
        blackGround->alpha = 0.5f;
    }
    auto t1 = btn[0]->gameObject->GetComponent<TurretUI>();
    btn[0]->AddListener([GameManager, t1]() {GameManager->StartBatch(t1->GetIndex()); });
    auto t2 = btn[1]->gameObject->GetComponent<TurretUI>();
    btn[1]->AddListener([GameManager, t2]() {GameManager->StartBatch(t2->GetIndex()); });
    auto t3 = btn[2]->gameObject->GetComponent<TurretUI>();
    btn[2]->AddListener([GameManager, t3]() {GameManager->StartBatch(t3->GetIndex()); });
    auto t4 = btn[3]->gameObject->GetComponent<TurretUI>();
    btn[3]->AddListener([GameManager, t4]() {GameManager->StartBatch(t4->GetIndex()); });
    auto t5 = btn[4]->gameObject->GetComponent<TurretUI>();
    btn[4]->AddListener([GameManager, t5]() {GameManager->StartBatch(t5->GetIndex()); });
    auto t6 = btn[5]->gameObject->GetComponent<TurretUI>();
    btn[5]->AddListener([GameManager, t6]() {GameManager->StartBatch(t6->GetIndex()); });
    // HP 및 MP 바 UI
    
    // hpbar
    auto hpBarObj = CreateGameObject<GameObject>();
    auto hpBarImage = hpBarObj->CreateComponent<ImageUIRenderer>();
    hpBarObj->transform->SetParent(uiObj->transform);
    hpBarObj->transform->type = Type::Ui;
    hpBarObj->transform->pos.rectposition = { {20.f,0.f} ,{20.f + 820.f,20.f} };
    hpBarUi = hpBarObj->CreateComponent<Hpbar>();
    pineApple->hpbar = hpBarUi;
    hpBarUi->ImageRender = hpBarImage;
    hpBarImage->LoadTexture(L"../Resource/30403_02.png");


    // expbar
    auto mpBarObj = CreateGameObject<GameObject>();
    auto mpBarImage = mpBarObj->CreateComponent<ImageUIRenderer>();
    mpBarObj->transform->SetParent(uiObj->transform);
    mpBarObj->transform->type = Type::Ui;
    mpBarObj->transform->pos.rectposition = { {20.f,20.f} ,{20.f + 820.f,40.f} };
    auto mpBar = mpBarObj->CreateComponent<Mpbar>();
    pineApple->expbar = mpBar;
    mpBar->ImageRender = mpBarImage;
    mpBarImage->LoadTexture(L"../Resource/30402_02.png");

    // 골드 Ui
    auto GoldObj = CreateGameObject<GameObject>();
    auto GoldImage = GoldObj->CreateComponent<Button>();
    GoldObj->transform->SetParent(uiObj->transform);
    GoldObj->transform->type = Type::Ui;
    GoldObj->transform->pos.rectposition = { {20.f + 820.f + spacing ,113.f} ,{20.f + 820.f + spacing + 270.f, 196.f} };
    GoldImage->LoadTexture(L"../Resource/30404.png");
    // wstring str;


    // 레벨 버튼 
    auto UpgradeObj = CreateGameObject<GameObject>();
    auto UpgradeImage = UpgradeObj->CreateComponent<Button>();
    UpgradeObj->transform->SetParent(uiObj->transform);
    UpgradeObj->transform->type = Type::Ui;
    UpgradeObj->transform->pos.rectposition = { {20.f + 820.f + spacing ,0.f} ,{20.f + 820.f + spacing + 270.f, 98.f} };
    UpgradeImage->LoadTexture(L"../Resource/30406.png");


    // 업그레이드 버튼 -> 이거 완성 500 * 500
    auto Upgradeobj = CreateGameObject<GameObject>();
    auto UpgradebtnImage = Upgradeobj->CreateComponent<Button>();
    Upgradeobj->transform->SetParent(uiObj->transform);
    Upgradeobj->transform->type = Type::Ui;
    Upgradeobj->transform->pos.rectposition = { {20.f + 820.f + spacing + 270.f + spacing,10.f} ,{20.f + 820.f + spacing + 270.f + spacing + 180.f, 200.f - spacing} };

    UpgradebtnImage->LoadTexture(L"../Resource/harvest.png");

    pineApple->harvestbtn = UpgradebtnImage;

    // 수확 버튼 -> 이거 완성 500 * 500
    auto Harvestobj = CreateGameObject<GameObject>();
    auto HarvestbtnImage = Harvestobj->CreateComponent<Button>();
    Harvestobj->transform->SetParent(uiObj->transform);
    Harvestobj->transform->type = Type::Ui;
    Harvestobj->transform->pos.rectposition = { {20.f + 820.f + spacing + 270.f + spacing + 180.f + spacing,10.f} ,{20.f + 820.f + spacing + 270.f + spacing + 180.f + spacing + 180.f, 200.f - spacing} };
    /*harvestUi = Harvestobj->CreateComponent<HarvestButton>();
    harvestUi->ImageRender = HarvestbtnImage;*/

    HarvestbtnImage->LoadTexture(L"../Resource/30208_Harvest1btn.png");
    
    pineApple->harvestbtn = HarvestbtnImage;

    // 검은색 배경과 버튼 그룹 생성
    auto uiGroup = CreateGameObject<GameObject>();
    uiGroup->transform->type = Type::Ui;
    uiGroup->SetActive(false); // 초기에는 비활성화

    // 반투명 검은색 배경 추가
    auto blackObj = CreateGameObject<GameObject>();
    blackObj->transform->SetParent(uiGroup->transform);
    blackObj->transform->SetSortingLayer(-10); // 다른 UI나 오브젝트보다 뒤에 있도록 설정
    SpriteRenderer* blackSpr = blackObj->CreateComponent<SpriteRenderer>();
    //bgSpr->SetColor(D2D1::ColorF(0, 0, 0, 0.5f)); // 검은색 배경 (반투명)
    //bgSpr->transform->pos.rectposition = { {0.f, 0.f} ,{1920.f, 1080.f} };

    // 버튼 5개 생성 및 초기 비활성화
    ramdomReward* rand = new ramdomReward();
    pineApple->randomReward = rand;

    // 버튼의 위치와 크기를 수동으로 지정
    D2D1_RECT_F buttonPositions[] = {
        {500.f, 600.f, 800.f, 700.f},  // 첫 번째 버튼의 위치 (x1, y1, x2, y2)
        {900.f, 600.f, 1200.f, 700.f}, // 두 번째 버튼의 위치
        {500.f, 800.f, 800.f, 900.f},  // 세 번째 버튼의 위치
        {900.f, 800.f, 1200.f, 900.f}, // 네 번째 버튼의 위치
        {700.f, 400.f, 1000.f, 500.f}  // 다섯 번째 버튼의 위치 (중앙 하단)
    };

    // 1. 랜덤하게 데이터를 섞습니다.
 /*   std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(DataManager.harvestPopupStruct.begin(), DataManager.harvestPopupStruct.end(), g);*/

    for (size_t i = 0; i < 5; i++) {
        auto buttonObj = CreateGameObject<GameObject>(); 
        buttonObj->transform->SetParent(uiGroup->transform);
        buttonObj->transform->type = Type::Ui;

        // 버튼의 위치와 크기를 설정
        buttonObj->transform->pos.rectposition.leftBottom = { buttonPositions[i].left, buttonPositions[i].top };
        buttonObj->transform->pos.rectposition.rightTop = { buttonPositions[i].right, buttonPositions[i].bottom };

        // 버튼 이미지 설정
        auto buttonImage = buttonObj->CreateComponent<Button>();
        buttonImage->ignoreEventSystem = false;
        buttonImage->LoadTexture(L"../Resource/button.png"); // 버튼의 기본 배경 이미지
        rand->btns.push_back(buttonImage);

        // 이미지 오브젝트 추가 (자식 오브젝트)
        auto imageObj = CreateGameObject<GameObject>();
        imageObj->transform->SetParent(buttonObj->transform);
        imageObj->transform->type = Type::Ui;
        imageObj->transform->pos.rectposition = {/* 이미지 위치와 크기 설정 */ };
        imageObj->transform->pos.rectposition.leftBottom = { 0,0 };
        imageObj->transform->pos.rectposition.rightTop = { 100, 100 };
        auto spriteRenderer = imageObj->CreateComponent<ImageUIRenderer>();
        spriteRenderer->LoadTexture(DataManager.harvestPopupStruct[i].Imagepath.c_str()); // 이미지 설정
     
        rand->Uis.push_back(spriteRenderer);
        // 이름 텍스트 오브젝트 추가 (자식 오브젝트)
        auto nameTextObj = CreateGameObject<GameObject>();
        nameTextObj->transform->SetParent(buttonObj->transform);
        nameTextObj->transform->type = Type::Ui;
        nameTextObj->transform->pos.rectposition = {/* 이름 텍스트 위치와 크기 설정 */ };
        auto nameText = nameTextObj->CreateComponent<TextUIRenderer>();
        nameText->SetFontSize(25.f);
        nameText->text = DataManager.harvestPopupStruct[i].reward;
        //nameText->SetText(L"이름"); // 이름 텍스트 설정
        //nameText->SetColor(D2D1::ColorF(D2D1::ColorF::White)); // 텍스트 색상 설정

        nameTextObj->transform->pos.rectposition.leftBottom = { 100, 50};
        nameTextObj->transform->pos.rectposition.rightTop  = { 300, 100 };

        rand->TextNameUis.push_back(nameText);
        // 내용 텍스트 오브젝트 추가 (자식 오브젝트)
        auto descTextObj = CreateGameObject<GameObject>();
        descTextObj->transform->SetParent(buttonObj->transform);
        descTextObj->transform->type = Type::Ui;
        descTextObj->transform->pos.rectposition = {/* 내용 텍스트 위치와 크기 설정 */ };
        auto descText = descTextObj->CreateComponent<TextUIRenderer>();
        descText->SetFontSize(25.f);
        descText->text = DataManager.harvestPopupStruct[i].rewarOption;
        //descText->SetText(L"내용"); // 내용 텍스트 설정   
        //descText->SetColor(D2D1::ColorF(D2D1::ColorF::White)); // 텍스트 색상 설정

        descTextObj->transform->pos.rectposition.leftBottom = { 100, 0};
        descTextObj->transform->pos.rectposition.rightTop = { 300, 50 };

        rand->TextStatUis.push_back(descText);

        pineApple->Popup = buttonImage;
    }


    // 2. 버튼에 랜덤하게 할당된 데이터를 설정합니다.
    //for (size_t i = 0; i < 5; i++) {
    //    auto& popupStruct = DataManager.harvestPopupStruct[i];
    //    buttons[i]->SetText(popupStruct.text);  // 버튼의 텍스트 설정
    //    buttons[i]->SetImage(popupStruct.imagePath);  // 버튼의 이미지 설정

    //    // 3. 버튼 클릭 시 실행할 함수 할당
    //    buttons[i]->AddListener([popupStruct]() {
    //        std::wcout << L"Button clicked: " << popupStruct.description << std::endl;
    //        popupStruct.action();  // 선택된 보상 적용
    //        });
    //}

    // 수확 버튼 클릭 시 -> harvest 안에서 sectactive 
    rand->UIoff();
    // 그룹 전체 활성화
    HarvestbtnImage->AddListener([pineApple]() {
        //uiGroup->SetActive(true); // 수확 버튼을 눌렀을 때 그룹 전체를 활성화
        pineApple->Harvest();
    });

       
    // 수확 버튼 클릭시

    //HarvestbtnImage->AddListener([pineApple]() {pineApple->Harvest(); });//[지역변수](매개변수){기능}

    // 수확이 버튼 눌렀을 때 코모서스 애니메이션 A재생
    //
    // 현재 hp -> maxHP
}

void GameScene::Clear() {
    __super::Clear();
    std::cout << "Exiting GameScene" << std::endl;
    // 정리 작업
    SoundManager::GetInstance().ReleaseSound(L"backgroundMusic");
}

void GameScene::Update(float deltaTime) {
    __super::Update(deltaTime);

    if (InputManager::GetInstance().IsKeyDown('1')) {
        hpBarUi->takeDamage(10.f);
        hpBarUi->ImageRender->slideBar = hpBarUi->getBarWidth();
        std::cout << hpBarUi->ImageRender->m_DstRect.right << std::endl;
        std::cout << hpBarUi->getBarWidth() << std::endl;
    }

    /*if (InputManager::GetInstance().IsKeyDown('2')) {
        mpBarUi->takeMp(10.f);
        mpBarUi->ImageRender->slideBar = mpBarUi->getBarWidth();
        std::cout << mpBarUi->ImageRender->m_DstRect.right << std::endl;
        std::cout << mpBarUi->getBarWidth() << std::endl;
    }*/
    if (InputManager::GetInstance().IsKeyDown('4')) {
        testPineApple->acquireGold(100);
    }
    // 메인 씬 전환 테스트
    if (InputManager::GetInstance().IsKeyDown('3')) {
        SceneManager::GetInstance().ChangeScene("StartScene");
    }

    // 동시 사운드 테스트 
    if (InputManager::GetInstance().IsKeyDown('5')) {
        // 5번을 클릭할 때 마다 SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/hello.mp3"); 사운드가 
        // 기존의 사운드는 그대로 출력되고 새 사운드가 중복으로 출력되게 하려고 하는데, 어떻게 하면 좋을까?
         // 새로운 고유 이름으로 사운드 로드
        std::wstring soundName = L"gimicSuccess";
        SoundManager::GetInstance().LoadSound(soundName, L"../Media/gimicSuccess.mp3");

        // 로드된 사운드를 재생
        SoundManager::GetInstance().PlaySoundW(soundName, true);
    }
    //마우스 스크롤 기능
    if (InputManager::GetInstance().GetMousePosition().x>0.f && InputManager::GetInstance().GetMousePosition().x < 100.f && camera->gameObject->transform->pos.worldPosition.x>-1560.f) {
		camera->gameObject->transform->pos.worldPosition.x -= 1000.f * deltaTime;
    }

    if (InputManager::GetInstance().GetMousePosition().x < 1920.f && InputManager::GetInstance().GetMousePosition().x > 1820.f && camera->gameObject->transform->pos.worldPosition.x < 1560.f) {
        camera->gameObject->transform->pos.worldPosition.x += 1000.f * deltaTime;
    }

    if (InputManager::GetInstance().IsKeyUp(VK_SPACE)) {
        camera->gameObject->transform->pos.worldPosition.x = 0.f;
    }

    SoundManager::GetInstance().Update();
}

void GameScene::Render(D2DRenderer* _render) {
    __super::Render(_render);

    auto pd = testPineApple;
    int gold = pd->GetPineAppleGold();
    //std::cout << gold << std::endl;
    std::wstring pineAppleGold = std::to_wstring(gold);
    D2DRenderer::getIncetance().DrawStringTextw(pineAppleGold.c_str(), m_GameObjects[0]->transform->m_WorldTransform, D2D1::ColorF::Red);
    //std::cout << cam->transform->m_WorldTransform.dx << std::endl;
    //std::cout << cam->transform->m_WorldTransform.dy << std::endl;

    /*int pineappleLV = pd->GetPineAppleLV();
    std::wstring pineAppleLV = std::to_wstring(pineappleLV);
    D2DRenderer::getIncetance().DrawStringTextw(pineAppleLV.c_str(), m_GameObjects[0]->transform->m_WorldTransform, D2D1::ColorF::Blue);*/


}
