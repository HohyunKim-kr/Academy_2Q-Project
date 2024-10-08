﻿#include "GameScene.h"
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
#include "../D2DEngine/SpriteUIAnimation.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameTime.h"
#include "../D2DEngine/LineRenderer.h"
#include "FSMHarvest.h"
#include <functional>
#include <algorithm>
#include "ramdomReward.h"
#include "CameraShake.h"
#include "ComosusFSM.h"
#include "ComosusLightSelector.h"
#include "Cutton.h"
#include "gamePopup.h"
#include <random> // 랜덤시드

MainPineApple* testPineApple = nullptr;
gamePopup* gameover = nullptr;
WaveSystem* testWave = nullptr;

GameScene::GameScene() {
    std::cout << "GameScene Constructor" << std::endl;
}

GameScene::~GameScene() {
    std::cout << "GameScene Destructor" << std::endl;
}

void GameScene::Start() {
    std::cout << "Entering GameScene" << std::endl;

    GameTime::GetInstance().SetTimeScale(1.f);

    // 커튼 애니메이션 
    auto cutttonObj = CreateGameObject<GameObject>();
    auto cutton = cutttonObj->CreateComponent<Cutton>();
    cuttons = cutton;
    cutttonObj->transform->type = Type::Ui;
    cutttonObj->transform->pos.rectposition = { {960,0},{1920,1080} };
    auto cuttonSpr = cutttonObj->CreateComponent<SpriteUIAnimation>();
    cuttonSpr->useUnScaleTime = true;
    cuttonSpr->LoadTexture(L"../Resource/10301.png");
    cuttonSpr->LoadAnimationAsset(L"cutton_10301");
    cuttonSpr->SetAnimation(0, false);
    cutton->UiCutton = cuttonSpr;
    cutton->check = false;

    auto cutttonObj2 = CreateGameObject<GameObject>();
    auto cutton2 = cutttonObj2->CreateComponent<Cutton>();
    cuttons = cutton2;
    cutttonObj2->transform->type = Type::Ui;
    cutttonObj2->transform->pos.rectposition = { {0,0},{960,1080} };
    auto cuttonSpr2 = cutttonObj2->CreateComponent<SpriteUIAnimation>();
    cuttonSpr2->useUnScaleTime = true;
    cuttonSpr2->LoadTexture(L"../Resource/10302.png");
    cuttonSpr2->LoadAnimationAsset(L"cutton_10302");
    cuttonSpr2->SetAnimation(0, false);
    cutton2->UiCutton = cuttonSpr2;
    cutton2->check = false;

    //[](){}

    auto camera = CreateGameObject<GameObject>();
    auto pCam = camera->CreateComponent<Camera>();
    SetMainCamera(pCam);

    auto shake = camera->CreateComponent<CameraShake>();
    shake->ShakeOnCamera(false);

    auto comosusSystem = CreateGameObject<GameObject>();
    comosusSystem->transform->SetSortingLayer(120);
    auto comosusFsm = comosusSystem->CreateComponent<FiniteStateMachine>();
    auto comosusDefault = comosusFsm->CreateState<ComosusPhaseDefault>("Default");
    auto comosusPhase1 = comosusFsm->CreateState<ComosusPhase1>("Phase1");
    auto comosusPhase2 = comosusFsm->CreateState<ComosusPhase2>("Phase2");
    comosusFsm->SetState("Default");
    auto comosusLight = comosusSystem->CreateComponent<ComosusLightSelector>();
    auto comosusColl = comosusSystem->CreateComponent<BoxCollider>();
    comosusPhase1->lightBox = comosusColl;
    comosusColl->SetExtent({ 280.f, 540.f });
    comosusColl->ignoreEventSystem = true;
    comosusColl->SetCollisionType(CollisionType::Overlap);
    comosusPhase1->lightSeletor = comosusLight;
    comosusPhase2->lightSeletor = comosusLight;
    comosusPhase1->cameraShaker = shake;
    auto comosusLightAnimation = comosusSystem->CreateComponent<SpriteAnimation>();
    comosusLightAnimation->LoadTexture(L"../Resource/ComosusLight.png");
    comosusLightAnimation->LoadAnimationAsset(L"ComosusLight");
    comosusLightAnimation->SetAnimation(0, false);
    comosusPhase1->comosusLightAnim = comosusLightAnimation;
    comosusPhase2->comosusLightAnim = comosusLightAnimation;


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
    comosusPhase1->dynamicData = dynamicData;
    comosusPhase2->dynamicData = dynamicData;
    dynamicData->Init();

    // pineapple random reward
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34101_단단한껍질.png",L"단단한 껍질",L"최대체력 +50",[dynamicData]() {dynamicData->rewardPineAppleStat.maxHp += 50; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34102_광기어린광합성.png",L"광기어린 광합성",L"광합성 +1",[dynamicData]() {dynamicData->rewardPineAppleStat.solarGain += 1; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34103_성장의 햇빛.png",L"성장의 햇빛",L"햇빛 +1", [dynamicData]() {dynamicData->rewardPineAppleStat.morningValue += 1; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34104_성장의 달빛.png",L"성장의 달빛",L"달빛 +2",[dynamicData]() {dynamicData->rewardPineAppleStat.nightValue += 2; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34104_질 좋은 양분들.png",L"질 좋은 양분들",L"경험치량 +1",[dynamicData]() {dynamicData->rewardPineAppleStat.killMultiply += 0.1f; } });

    // comosus light reward
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34201_강력해진 신호.png",L"강력해진 신호",L"코모서스 애니메이션x*10.f +2",[dynamicData]() {dynamicData->rewardPineAppleStat.comosusLight += 10.f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34202_잦아지는 응답.png",L"잦아지는 응답",L"offeringmultiply -=0.5",[dynamicData]() {dynamicData->rewardPineAppleStat.offeringMultiply -= 0.05f; } });

    // Crossbow tower reward
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34301_석궁 피해량.png",L"석궁피해량",L"공격력 +2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow].damage += 2.f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34302_석궁 공격속도.png",L"석궁 공격속도+",L"공격속도 +0.2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow].fireRate += 0.2f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34303_석궁 관통력.png",L"석궁 관통력+",L"관통력 +1",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow].penetration += 1; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34304_무거운 화살촉.png",L"무거운 화살촉",L"공격력 +5, 투사체 속도 -3.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow].damage += 5.f; dynamicData->rewardTurretStat[TurretType::Crossbow].bulletSpeed -= 3.f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34305_독이 발린 화살촉.png",L"독이 발린 화살촉",L"이동속도 감소량 +8%, 이동속도 감소 지속시간 3.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Crossbow].slowRate += 8.f; dynamicData->rewardTurretStat[TurretType::Crossbow].slowDuration += 3.f; } });

    // musket tower reward
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34401_머스킷 피해량.png",L"머스킷 피해량+",L"머스킷타워 공격력 +2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Musket].damage += 2.f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34402_머스킷 공격속도.png",L"머스킷 공격속도+",L"머스킷타워 공격속도 +0.15",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Musket].fireRate += 0.15f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34403_머스킷 관통력.png",L"머스킷 관통력+",L"머스킷타워 관통력 +2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Musket].penetration += 2.f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34404_대구경 탄환.png",L"대구경 탄환",L"머스킷타워 공격속도 -0.3, 머스킷타워 관통력 +5",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Musket].fireRate -= 0.3f; dynamicData->rewardTurretStat[TurretType::Musket].penetration += 5; } });

    // Cannon tower reward
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34501_박격포 피해량.png",L"박격포 피해량+",L"박격포타워 공격력 +2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].damage += 2; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34502_박격포 공격속도.png",L"박격포 공격속도+",L"박격포타워 공격속도 +0.1",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].fireRate += 0.1f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34503_박격포 관통력.png",L"박격포 관통력+",L"박격포타워 관통력 +1",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].penetration += 1; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34504_더많은 작약.png",L"더많은 작약",L"폭밤범위 +15",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].burstRange += 15; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34505_포탄 경량화.png",L"포탄 경량화",L"폭발범위 -10, 투사체속도 +100",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].burstRange -= 10; dynamicData->rewardTurretStat[TurretType::Cannon].bulletSpeed += 100.f;  } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34506_포탄 중량화.png",L"포탄 중량화",L"폭발범위 +35, 공격속도 -0.1",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].burstRange += 35; dynamicData->rewardTurretStat[TurretType::Cannon].fireRate -= 0.1f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34507_제압탄.png",L"제압탄",L"이동속도 감소 +15%, 이동속도 지속시간 +2.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::Cannon].slowRate += 15.f; dynamicData->rewardTurretStat[TurretType::Cannon].slowDuration += 2.f; } });

    // superarrow tower reward
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34601_대형화살.png",L"대형화살",L"공격력+=5,공격속도 -1.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::SuperCrossbow].damage += 5; dynamicData->rewardTurretStat[TurretType::SuperCrossbow].fireRate -= 1.f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34602_슈퍼석궁 피해량.png",L"슈퍼석궁피해량+",L"공격력+=2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::SuperCrossbow].damage += 2.f; } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34603_슈퍼석궁 공격속도.png",L"슈퍼석궁 공격속도+",L"공격속도+=0.2",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::SuperCrossbow].fireRate += 0.2f;  } });
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/35604_슈퍼석궁 관통력.png",L"슈퍼석궁 관통력+",L"관통력+=1",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::SuperCrossbow].penetration += 1;  } });

    //slow wand
    DataManager.harvestPopupStruct.push_back({ L"../Resource/수확보상팝업/34701_슬로우 완드 지속시간.png",L"슬로우완드 타워",L"이동속도 감소 지속시간 +2.0",[dynamicData]() {dynamicData->rewardTurretStat[TurretType::SlowWand].slowDuration += 2.f; } });

    // 생장에너지 투약 이미지 없음
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
    boxColl->debugLine = true;


    // 드래그 시 이미지 보여줄 오브젝트
    auto testDragObj = CreateGameObject<GameObject>();
    testDragObj->SetActive(false);
    auto sproper = testDragObj->CreateComponent<SpriteAnimation>();
    sproper->alpha = 0.7f;
    GameManager->dragObj = testDragObj;
    testDragObj->transform->SetSortingLayer(2);

    auto dragHighlight = CreateGameObject<GameObject>();
    dragHighlight->transform->SetParent(testDragObj->transform);
    dragHighlight->SetActive(false);
    auto highlightSpr = dragHighlight->CreateComponent<SpriteRenderer>();
    dragHighlight->transform->SetSortingLayer(1);
    GameManager->dragHighlightSpr = highlightSpr;

    // 코모서스 파인애플 (겁나 큼)
    auto paObj = CreateGameObject<GameObject>();
    paObj->transform->SetSortingLayer(-1);
    paObj->transform->pos.worldPosition = { 0.f, 0.f };
    auto pineApple = paObj->CreateComponent<MainPineApple>();
    comosusPhase1->pineApple = pineApple;
    comosusPhase2->pineApple = pineApple;
    pineApple->comosusFsm = comosusFsm;
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
    pineappleSpr->LoadTexture(L"../Resource/30301_01.png");
    auto pineColl = paObj->CreateComponent<BoxCollider>();
    pineColl->ignoreEventSystem = true;
    pineColl->isKinemetic = true;
    pineColl->SetCenter({ 300.f, 100.f });
    pineColl->SetExtent({ 0.f, 1000.f });
    pineColl = paObj->CreateComponent<BoxCollider>();
    pineColl->ignoreEventSystem = true;
    pineColl->isKinemetic = true;
    pineColl->SetCenter({ -300.f, 100.f });
    pineColl->SetExtent({ 0.f, 1000.f });

    // 코모서스 강림
    auto comoObj = CreateGameObject<GameObject>();
    comoObj->transform->m_RelativeScale.x = 1.3f;
    comoObj->transform->pos.worldPosition = { 0.f,540.f };
    auto comosus = comoObj->CreateComponent<Comosus>();
    comoObj->transform->SetSortingLayer(100);
    auto comsusSpr = comoObj->CreateComponent<SpriteAnimation>();
    comosusPhase1->comosusSpriteAnim = comsusSpr;
    comosusPhase2->comosusSpriteAnim = comsusSpr;
    Texture* t = nullptr;
    ResourceManager::GetInstance().CreateTextureFromFile(L"../Resource/30722_tentacle_animation.png", &t);
    comsusSpr->m_pTexture = t;
    comsusSpr->LoadAnimationAsset(L"Comosus");
    comsusSpr->SetAnimation(0, false);
    pineApple->comosus = comsusSpr;

    GameManager->pineApple = pineApple;

    // 파인애플 타일들
    std::vector<GameObject*> turretTiles;
    for (int i = 0; i < 18; i++) {
        // 파인애플 타일들
        auto paTileObj = CreateGameObject<GameObject>();
        turretTiles.push_back(paTileObj);

        paTileObj->transform->SetParent(paObj->transform);
        //paTileObj->transform->pos.worldPosition = { -3.f, 190.f };

        auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
        pineTile->pApple = pineApple;
        //pineTile->index = 1;

        auto coll = paTileObj->CreateComponent<CircleCollider>();
        coll->SetCollisionType(CollisionType::Overlap);
        coll->isKinemetic = true;
        coll->SetRadius(50.f);

        auto childObj = CreateGameObject<GameObject>();
        childObj->transform->SetSortingLayer(1);
        childObj->isActive = false;
        auto tur = childObj->CreateComponent<Turret>();
        pineApple->turrets.push_back(tur);
        tur->dynamicData = dynamicData;
        tur->parentPineApple = pineApple;
        auto circleColl = childObj->CreateComponent<CircleCollider>();
        circleColl->SetCollisionType(CollisionType::Overlap);
        childObj->transform->SetParent(paTileObj->transform);
        auto spr = childObj->CreateComponent<SpriteAnimation>();
        tur->anim = spr;
        pineTile->turret = childObj;

        auto highlightObj = CreateGameObject<GameObject>();
        highlightObj->transform->SetParent(childObj->transform);
        auto highlightSpr = highlightObj->CreateComponent<SpriteRenderer>();
        tur->selectOutline = highlightSpr;

        auto fireTr = CreateGameObject<GameObject>();
        fireTr->transform->SetParent(childObj->transform);
        fireTr->transform->pos.worldPosition = { 50.f, 0.f };
        tur->fireTr = fireTr;
    }
    turretTiles[0]->transform->pos.worldPosition = { -3.f, 190.f };
    turretTiles[1]->transform->pos.worldPosition = { -85.f, 120.f };
    turretTiles[2]->transform->pos.worldPosition = { 80.f, 120.f };
    turretTiles[3]->transform->pos.worldPosition = { -3.f, 53.f };
    turretTiles[4]->transform->pos.worldPosition = { -85.f, -16.f };
    turretTiles[5]->transform->pos.worldPosition = { 80.f, -16.f };
    turretTiles[6]->transform->pos.worldPosition = { -3.f, -84.f };
    turretTiles[7]->transform->pos.worldPosition = { -85.f, -154.f };
    turretTiles[8]->transform->pos.worldPosition = { 80.f, -154.f };
    turretTiles[9]->transform->pos.worldPosition = { -3.f, -220.f };

    turretTiles[10]->transform->pos.worldPosition = { -165.f, 53.f };
    turretTiles[11]->transform->pos.worldPosition = { 158.f, 53.f };
    turretTiles[12]->transform->pos.worldPosition = { -165.f, -84.f };
    turretTiles[13]->transform->pos.worldPosition = { 158.f, -84.f };

    turretTiles[14]->transform->pos.worldPosition = { -155.f, 190.f };
    turretTiles[15]->transform->pos.worldPosition = { 150.f, 190.f };
    turretTiles[16]->transform->pos.worldPosition = { -155.f, -220.f };
    turretTiles[17]->transform->pos.worldPosition = { 150.f, -220.f };

    for (int i = 0; i < 10; i++) {
        turretTiles[i]->GetComponent<PineAppleTile>()->index = 1;
    }
    for (int i = 10; i < 14; i++) {
        turretTiles[i]->GetComponent<PineAppleTile>()->index = 2;
    }
    for (int i = 14; i < 18; i++) {
        turretTiles[i]->GetComponent<PineAppleTile>()->index = 3;
    }


    // 사운드 초기화 및 로드
    SoundManager::GetInstance().LoadSound(L"Morning_Bgm", L"../Media/6_Sound/scene3/Bgm/Morning_Bgm.wav");
    SoundManager::GetInstance().SetVolume(L"Morning_Bgm", 0.5f);
    SoundManager::GetInstance().PlaySoundW(L"Morning_Bgm", true);

    // 사운드 초기화 및 로드

    // boss
    SoundManager::GetInstance().LoadSound(L"Boss1Attack_Se", L"../Media/6_Sound/scene3/Se/Boss1Attack_Se.wav");
    SoundManager::GetInstance().SetVolume(L"Boss1Attack_Se", 0.1f);

    // swordman 
    SoundManager::GetInstance().LoadSound(L"KnightDeath_Se", L"../Media/6_Sound/scene3/Se/KnightDeath_Se.wav");
    SoundManager::GetInstance().SetVolume(L"KnightDeath_Se", 0.5f);

    // swordman 
    SoundManager::GetInstance().LoadSound(L"KnightAttack_Se", L"../Media/6_Sound/scene3/Se/KnightAttack_Se.wav");
    SoundManager::GetInstance().SetVolume(L"KnightAttack_Se", 0.5f);
    SoundManager::GetInstance().LoadSound(L"KnightDeath_Se", L"../Media/6_Sound/scene3/Se/KnightDeath_Se.wav");
    SoundManager::GetInstance().SetVolume(L"KnightDeath_Se", 0.5f);

    // heaykingight 
    SoundManager::GetInstance().LoadSound(L"HeavySoldierAttack_Se", L"../Media/6_Sound/scene3/Se/HeavySoldierAttack_Se.wav");
    SoundManager::GetInstance().SetVolume(L"HeavySoldierAttack_Se", 0.5f);
    SoundManager::GetInstance().LoadSound(L"HeavySoldierDeath_Se", L"../Media/6_Sound/scene3/Se/HeavySoldierDeath_Se.wav");
    SoundManager::GetInstance().SetVolume(L"HeavySoldierDeath_Se", 0.5f);

    // Bombcart 
    SoundManager::GetInstance().LoadSound(L"BombCartMovement_Se", L"../Media/6_Sound/scene3/Se/BombCartMovement_Se.wav");
    SoundManager::GetInstance().SetVolume(L"BombCartMovement_Se", 0.5f);
    SoundManager::GetInstance().LoadSound(L"BombCartExplosion_Se", L"../Media/6_Sound/scene3/Se/BombCartExplosion_Se.wav");
    SoundManager::GetInstance().SetVolume(L"BombCartExplosion_Se", 0.5f);

    // musket 
    SoundManager::GetInstance().LoadSound(L"MusketAttack_Se", L"../Media/6_Sound/scene3/Se/MusketAttack_Se.wav");
    SoundManager::GetInstance().SetVolume(L"MusketAttack_Se", 0.5f);
    /*  SoundManager::GetInstance().LoadSound(L"HeavySoldierDeath_Se", L"../Media/6_Sound/scene3/Se/HeavySoldierDeath_Se.wav");
      SoundManager::GetInstance().SetVolume(L"HeavySoldierDeath_Se", 0.5f);*/

      // griffin 
    SoundManager::GetInstance().LoadSound(L"GriffinAttack_Se", L"../Media/6_Sound/scene3/Se/GriffinAttack_Se.wav");
    SoundManager::GetInstance().SetVolume(L"GriffinAttack_Se", 0.5f);
    SoundManager::GetInstance().LoadSound(L"GriffinDeath_Se", L"../Media/6_Sound/scene3/Se/GriffinDeath_Se.wav");
    SoundManager::GetInstance().SetVolume(L"GriffinDeath_Se", 0.5f);

    // morning
    SoundManager::GetInstance().LoadSound(L"Morning_Bgm", L"../Media/6_Sound/scene3/Bgm/Morning_Bgm.wav");
    SoundManager::GetInstance().SetVolume(L"Morning_Bgm", 0.5f);

    // night
    SoundManager::GetInstance().LoadSound(L"Night_Bgm", L"../Media/6_Sound/scene3/Bgm/Night_Bgm.wav");
    SoundManager::GetInstance().SetVolume(L"Night_Bgm", 0.5f);


    // CrossbowFire_Se
    SoundManager::GetInstance().LoadSound(L"CrossbowFire_Se", L"../Media/6_Sound/scene3/Se/CrossbowFire_Se.wav");
    SoundManager::GetInstance().SetVolume(L"CrossbowFire_Se", 0.2f);

    // MusketFire_Se
    SoundManager::GetInstance().LoadSound(L"MusketFire_Se", L"../Media/6_Sound/scene3/Se/MusketFire_Se.wav");
    SoundManager::GetInstance().SetVolume(L"MusketFire_Se", 0.2f);

    // MortarFire_Se
    SoundManager::GetInstance().LoadSound(L"MortarFire_Se", L"../Media/6_Sound/scene3/Se/MortarFire_Se.wav");
    SoundManager::GetInstance().SetVolume(L"MortarFire_Se", 0.2f);

    SoundManager::GetInstance().LoadSound(L"MorterExplosion_Se", L"../Media/6_Sound/scene3/Se/MorterExplosion_Se.wav");
    SoundManager::GetInstance().SetVolume(L"MorterExplosion_Se", 0.2f);

    // SlowWandFire_Se
    SoundManager::GetInstance().LoadSound(L"SlowWandFire_Se", L"../Media/6_Sound/scene3/Se/SlowWandFire_Se.wav");
    SoundManager::GetInstance().SetVolume(L"SlowWandFire_Se", 0.2f);

    // SuperCrossbowFire_Se
    SoundManager::GetInstance().LoadSound(L"SuperCrossbowFire_Se", L"../Media/6_Sound/scene3/Se/SuperCrossbowFire_Se.wav");
    SoundManager::GetInstance().SetVolume(L"SuperCrossbowFire_Se", 0.2f);

    // Win_Bgm
    //SoundManager::GetInstance().LoadSound(L"SlowWandFire_Se", L"../Media/6_Sound/scene3/Se/SlowWandFire_Se.wav");
    //SoundManager::GetInstance().SetVolume(L"SlowWandFire_Se", 0.2f);

    //// GameOver_Bgm
    //SoundManager::GetInstance().LoadSound(L"SlowWandFire_Se", L"../Media/6_Sound/scene3/Se/SlowWandFire_Se.wav");
    //SoundManager::GetInstance().SetVolume(L"SlowWandFire_Se", 0.2f);

    // click btn 사운드
    SoundManager::GetInstance().LoadSound(L"clickbtn", L"../Media/6_Sound/scene1/Se/ClickButton_Se.wav");
    SoundManager::GetInstance().SetVolume(L"clickbtn", 0.5f);

    // comosus reward 30920
    SoundManager::GetInstance().LoadSound(L"HarvestReward_Se", L"../Media/6_Sound/scene3/Se/HarvestReward_Se.wav");
    SoundManager::GetInstance().SetVolume(L"HarvestReward_Se", 0.5f);

    // comosus light sound 30921
    SoundManager::GetInstance().LoadSound(L"LightOfComos'us_Se", L"../Media/6_Sound/scene3/Se/LightOfComos'us_Se.wav");
    SoundManager::GetInstance().SetVolume(L"LightOfComos'us_Se", 0.5f);

    // new pineapple sound 30922
    SoundManager::GetInstance().LoadSound(L"NewPineappleAppears_Se", L"../Media/6_Sound/scene3/Se/NewPineappleAppears_Se.wav");
    SoundManager::GetInstance().SetVolume(L"NewPineappleAppears_Se", 0.5f);

    // turret Activate
    SoundManager::GetInstance().LoadSound(L"NewTurretInstalling_Se", L"../Media/6_Sound/scene3/Se/NewTurretInstalling_Se.wav");
    SoundManager::GetInstance().SetVolume(L"NewTurretInstalling_Se", 0.5f);

    // comosus light 50% sound
    SoundManager::GetInstance().LoadSound(L"SurprisedStands_Se", L"../Media/6_Sound/scene3/Se/SurprisedStands_Se.wav");
    SoundManager::GetInstance().SetVolume(L"SurprisedStands_Se", 0.5f);

    // boss On
    SoundManager::GetInstance().LoadSound(L"ShockedStands_Se", L"../Media/6_Sound/scene3/Se/ShockedStands_Se.wav");
    SoundManager::GetInstance().SetVolume(L"ShockedStands_Se", 0.5f);
    SoundManager::GetInstance().LoadSound(L"Boss1Come_Se", L"../Media/6_Sound/scene3/Se/Boss1Come_Se.wav");
    SoundManager::GetInstance().SetVolume(L"Boss1Come_Se", 0.5f);

    // pineApple Damaged 아직 x
    SoundManager::GetInstance().LoadSound(L"BooingStands_Se", L"../Media/6_Sound/scene3/Se/BooingStands_Se.wav");
    SoundManager::GetInstance().SetVolume(L"BooingStands_Se", 0.5f);

    // killed boss
    SoundManager::GetInstance().LoadSound(L"CheeringStands_Se", L"../Media/6_Sound/scene3/Se/CheeringStands_Se.wav");
    SoundManager::GetInstance().SetVolume(L"CheeringStands_Se", 0.5f);
    SoundManager::GetInstance().LoadSound(L"Boss1Win_Se", L"../Media/6_Sound/scene3/Se/Boss1Win_Se.wav");
    SoundManager::GetInstance().SetVolume(L"Boss1Win_Se", 0.5f);

    // turret sale sound
    SoundManager::GetInstance().LoadSound(L"SaleTurrets_Se", L"../Media/6_Sound/scene3/Se/SaleTurrets_Se.wav");
    SoundManager::GetInstance().SetVolume(L"SaleTurrets_Se", 0.5f);

    // 메뉴바
    auto uiObj = CreateGameObject<GameObject>();
    uiObj->transform->SetSortingLayer(-1);
    auto uiImage = uiObj->CreateComponent<ImageUIRenderer>();
    uiObj->transform->type = Type::Ui;
    uiObj->transform->pos.rectposition = { {180,0} ,{1560 + 180,200} };
    uiImage->LoadTexture(L"../Resource/30401.png");


    // Tutorial 튜토리얼
	auto tutorialObj = CreateGameObject<GameObject>();
    auto tutorialImage = tutorialObj->CreateComponent<SpriteRenderer>();
	//tutorialObj->transform->type = Type::Ui;
    tutorialObj->transform->pos.worldPosition = { -500.f,750.f};
    tutorialObj->transform->SetSortingLayer(-1);
	tutorialImage->LoadTexture(L"../Resource/31011.png");
    

    // Tutorial 튜토리얼2
    auto tutorial2Obj = CreateGameObject<GameObject>();
    auto tutorial2Image = tutorial2Obj->CreateComponent<SpriteRenderer>();
    //tutorial2Obj->transform->type = Type::Ui;
    tutorial2Obj->transform->pos.worldPosition = { -500.f,750.f };
    tutorial2Obj->transform->SetSortingLayer(-1);
    tutorial2Image->LoadTexture(L"../Resource/31012.png");

    // Tutorial 튜토리얼3
    auto tutorial3Obj = CreateGameObject<GameObject>();
    auto tutorial3Image = tutorial3Obj->CreateComponent<SpriteRenderer>();
    //tutorial3Obj->transform->type = Type::Ui;
    tutorial3Obj->transform->pos.worldPosition = { -500.f,750.f };
    tutorial3Obj->transform->SetSortingLayer(-1);
    tutorial3Image->LoadTexture(L"../Resource/31031.png");

    // TutorialBottom 튜토리얼Bottom
    auto tutorialBottomObj = CreateGameObject<GameObject>();
    auto tutorialBottomImage = tutorialBottomObj->CreateComponent<SpriteRenderer>();
    //tutorialBottomObj->transform->type = Type::Ui;
    tutorialBottomObj->transform->pos.worldPosition = { -330.f,1000.f };
    tutorialBottomObj->transform->SetSortingLayer(100);
    tutorialBottomImage->LoadTexture(L"../Resource/31888.png");

    // Tutorial 튜토리얼4
    auto tutorial4Obj = CreateGameObject<GameObject>();
    auto tutorial4Image = tutorial4Obj->CreateComponent<SpriteRenderer>();
    //tutorial4Obj->transform->type = Type::Ui;
    tutorial4Obj->transform->pos.worldPosition = { -500.f,750.f };
    tutorial4Obj->transform->SetSortingLayer(-1);
    tutorial4Image->LoadTexture(L"../Resource/31032.png");

	// Tutorial 튜토리얼 bottom2 (is counterpart of tutorial4)
    auto tutorialBottom2Obj = CreateGameObject<GameObject>();
    tutorialBottom2Obj->transform->SetSortingLayer(-2);
    auto tutorialBottom2Image = tutorialBottom2Obj->CreateComponent<ImageUIRenderer>();
    tutorialBottom2Obj->transform->type = Type::Ui;
	tutorialBottom2Obj->transform->pos.rectposition = { {1482.5f,-200} ,{1482.5f + 170,-(200 + 130)} }; // {1482.5f,200} ,{1482.5f + 170,200+130} is the position of the bottom2
    tutorialBottom2Image->LoadTexture(L"../Resource/31999.png");

    // Tutorial 튜토리얼5
    auto tutorial5Obj = CreateGameObject<GameObject>();
    auto tutorial5Image = tutorial5Obj->CreateComponent<SpriteRenderer>();
    //tutorial4Obj->transform->type = Type::Ui;
    tutorial5Obj->transform->pos.worldPosition = { -500.f,750.f };
    tutorial5Obj->transform->SetSortingLayer(-1);
    tutorial5Image->LoadTexture(L"../Resource/31061.png");

    // Tutorial 튜토리얼6
    auto tutorial6Obj = CreateGameObject<GameObject>();
    auto tutorial6Image = tutorial6Obj->CreateComponent<SpriteRenderer>();
    //tutorial4Obj->transform->type = Type::Ui;
    tutorial6Obj->transform->pos.worldPosition = { -500.f,750.f };
    tutorial6Obj->transform->SetSortingLayer(-1);
    tutorial6Image->LoadTexture(L"../Resource/31071.png");

    // Tutorial 튜토리얼17
    auto tutorial17Obj = CreateGameObject<GameObject>();
    auto tutorial17Image = tutorial17Obj->CreateComponent<SpriteRenderer>();
    //tutorial7Obj->transform->type = Type::Ui;
    tutorial17Obj->transform->pos.worldPosition = { -500.f,750.f };
    tutorial17Obj->transform->SetSortingLayer(-1);
    tutorial17Image->LoadTexture(L"../Resource/31171.png");

    // Tutorial 튜토리얼53
    auto tutorial53Obj = CreateGameObject<GameObject>();
    auto tutorial53Image = tutorial53Obj->CreateComponent<SpriteRenderer>();
    //tutorial7Obj->transform->type = Type::Ui;
    tutorial53Obj->transform->pos.worldPosition = { -500.f,750.f };
    tutorial53Obj->transform->SetSortingLayer(-1);
    tutorial53Image->LoadTexture(L"../Resource/31531.png");

    // Tutorial 튜토리얼54
    auto tutorial54Obj = CreateGameObject<GameObject>();
    auto tutorial54Image = tutorial54Obj->CreateComponent<SpriteRenderer>();
    //tutorial7Obj->transform->type = Type::Ui;
    tutorial54Obj->transform->pos.worldPosition = { -500.f,750.f };
    tutorial54Obj->transform->SetSortingLayer(-1);
    tutorial54Image->LoadTexture(L"../Resource/31541.png");

    // 웨이브 시스템
    auto waveObj = CreateGameObject<GameObject>();
    waveSystem = waveObj->CreateComponent<WaveSystem>();
    testWave = waveSystem;
    waveSystem->scene = this;
    waveSystem->bulletFactory = bulletFactory;
    waveSystem->mainPineApple = GameManager->pineApple;
    waveSystem->Init();
	pineApple->waveSystem = waveSystem; // 낮 밤에 따라 광합성 경험치 습득 때문에 넣음.
	waveSystem->tutorial1 = tutorialObj;
    waveSystem->tutorial2 = tutorial2Obj;
    waveSystem->tutorial3 = tutorial3Obj;
	waveSystem->tutorial4 = tutorial4Obj;
	waveSystem->tutorial5 = tutorial5Obj;
	waveSystem->tutorial6 = tutorial6Obj;
	waveSystem->tutorial17 = tutorial17Obj;
	waveSystem->tutorial53 = tutorial53Obj;
	waveSystem->tutorial54 = tutorial54Obj;

	waveSystem->tutorialBottom = tutorialBottomObj;
	waveSystem->tutorial2Bottom = tutorialBottom2Obj;

    for (int i = 0; i < 13; i++) {
        waveSystem->howManyLeft[i] = CreateGameObject<GameObject>();
		auto howManyLeftImage = waveSystem->howManyLeft[i]->CreateComponent<SpriteRenderer>();
		waveSystem->howManyLeft[i]->transform->SetSortingLayer(-1);
		waveSystem->howManyLeft[i]->transform->pos.worldPosition = { 500.f,750.f };
		int k = 37105 + i * 4;
		howManyLeftImage->LoadTexture(L"../Resource/"+ std::to_wstring(k) + L".png");
    }

    // DayNightCycleComponent 생성 및 게임 오브젝트에 추가
    auto nightObj = CreateGameObject<GameObject>();
    nightSystem = nightObj->CreateComponent<DayNightCycle>();
    waveSystem->dayNightCycle = nightSystem;

    {
        // 배경 이미지
        auto bg30102Obj = CreateGameObject<GameObject>();
        bg30102Obj->transform->SetSortingLayer(-17);
        bg30102Obj->transform->pos.worldPosition = { 0.f, -540.f };
        auto bg30102Spr = bg30102Obj->CreateComponent<SpriteRenderer>();
        bg30102Spr->LoadTexture(L"../Resource/30102.png");
        nightSystem->backGroundDay = bg30102Obj;
		bg30102Spr->SetCenter({ 0.5f, 1.0f });

        // 배경 땅
        auto bg30101Obj = CreateGameObject<GameObject>();
        bg30101Obj->transform->SetSortingLayer(-11);
		bg30101Obj->transform->pos.worldPosition = { 0.f, -540.f };
        auto bg30101Spr = bg30101Obj->CreateComponent<SpriteRenderer>();
        bg30101Spr->LoadTexture(L"../Resource/30101.png");
        bg30101Obj->transform->SetSortingLayer(20);
		nightSystem->Earth = bg30101Obj;
		bg30101Spr->SetCenter({ 0.5f, 1.0f });


        // 배경 산1
        auto bg30321Obj = CreateGameObject<GameObject>();
        bg30321Obj->transform->SetSortingLayer(-12);
		bg30321Obj->transform->pos.worldPosition = { 0.f, -540.f };
        auto bg30321Spr = bg30321Obj->CreateComponent<SpriteRenderer>();
        bg30321Spr->LoadTexture(L"../Resource/30321.png");
		nightSystem->Mountain1Day = bg30321Obj;
		bg30321Spr->SetCenter({ 0.5f, 1.0f });

        // 배경 산2
        auto bg30322Obj = CreateGameObject<GameObject>();
        bg30322Obj->transform->SetSortingLayer(-13);
		bg30322Obj->transform->pos.worldPosition = { 0.f, -540.f };
        auto bg30322Spr = bg30322Obj->CreateComponent<SpriteRenderer>();
        bg30322Spr->LoadTexture(L"../Resource/30322.png");
		nightSystem->Mountain2Day = bg30322Obj;
		bg30322Spr->SetCenter({ 0.5f, 1.0f });

        // 구름 아침
        auto bgCloudObj = CreateGameObject<GameObject>();
        bgCloudObj->transform->SetSortingLayer(-12);
		bgCloudObj->transform->pos.worldPosition = { 0.f, -540.f };
        auto bgCloudSpr = bgCloudObj->CreateComponent<SpriteRenderer>();
        bgCloudSpr->LoadTexture(L"../Resource/30324.png");
		nightSystem->cloudDay = bgCloudObj;
		bgCloudSpr->SetCenter({ 0.5f, 1.0f });

        //Sun and Moon will sorted in layer -14

        // 배경 산3
        auto bg30323Obj = CreateGameObject<GameObject>();
        bg30323Obj->transform->SetSortingLayer(-14);
		bg30323Obj->transform->pos.worldPosition = { 0.f, -540.f };
        auto bg30323Spr = bg30323Obj->CreateComponent<SpriteRenderer>();
        bg30323Spr->LoadTexture(L"../Resource/30323.png");
		nightSystem->Mountain3Day = bg30323Obj;
		bg30323Spr->SetCenter({ 0.5f, 1.0f });
    }

    {
        // 배경 밤이미지
        auto bg30103Obj = CreateGameObject<GameObject>();
        bg30103Obj->transform->SetSortingLayer(-17);
        auto bg30103Spr = bg30103Obj->CreateComponent<SpriteRenderer>();
        bg30103Spr->LoadTexture(L"../Resource/30103.png");
        nightSystem->backGroundNight = bg30103Obj;
        bg30103Obj->transform->pos.worldPosition.y -= 540.f;
		bg30103Obj->transform->m_RelativeRotation = 180.f;
		bg30103Spr->SetCenter({ 0.5f, 1.f });

        // 배경 밤산1
        auto bg30321_1Obj = CreateGameObject<GameObject>();
        bg30321_1Obj->transform->SetSortingLayer(-12);
        auto bg30321_1Spr = bg30321_1Obj->CreateComponent<SpriteRenderer>();
        bg30321_1Spr->LoadTexture(L"../Resource/30321_1.png");
        nightSystem->Mountain1Night = bg30321_1Obj;
		bg30321_1Obj->transform->pos.worldPosition.y -= 540.f;
		bg30321_1Obj->transform->m_RelativeRotation = 180.f;
        bg30321_1Spr->SetCenter({ 0.5f, 1.f });
        

        // 배경 밤산2
        auto bg30322_1Obj = CreateGameObject<GameObject>();
        bg30322_1Obj->transform->SetSortingLayer(-13);
        auto bg30322_1Spr = bg30322_1Obj->CreateComponent<SpriteRenderer>();
        bg30322_1Spr->LoadTexture(L"../Resource/30322_1.png");
        nightSystem->Mountain2Night = bg30322_1Obj;
		bg30322_1Obj->transform->pos.worldPosition.y -= 540.f;
		bg30322_1Obj->transform->m_RelativeRotation = 180.f;
		bg30322_1Spr->SetCenter({ 0.5f, 1.f });

        // 구름 밤
        auto bgCloudNightObj = CreateGameObject<GameObject>();
        bgCloudNightObj->transform->SetSortingLayer(-12);
        auto bgCloudNightSpr = bgCloudNightObj->CreateComponent<SpriteRenderer>();
        bgCloudNightSpr->LoadTexture(L"../Resource/30324_1.png");
        nightSystem->cloudNight = bgCloudNightObj;
		bgCloudNightObj->transform->pos.worldPosition.y -= 540.f;
		bgCloudNightObj->transform->m_RelativeRotation = 180.f;
		bgCloudNightSpr->SetCenter({ 0.5f, 1.f });


        //Sun and Moon will sorted in layer -14

        // 배경 밤산3
        auto bg30323_1Obj = CreateGameObject<GameObject>();
        bg30323_1Obj->transform->SetSortingLayer(-14);
        auto bg30323_1Spr = bg30323_1Obj->CreateComponent<SpriteRenderer>();
        bg30323_1Spr->LoadTexture(L"../Resource/30323_1.png");
        nightSystem->Mountain3Night = bg30323_1Obj;
		bg30323_1Obj->transform->pos.worldPosition.y -= 540.f;
		bg30323_1Obj->transform->m_RelativeRotation = 180.f;
		bg30323_1Spr->SetCenter({ 0.5f, 1.f });
    }


    // 해 이미지
    auto sunObj = CreateGameObject<GameObject>();
    sunObj->transform->SetSortingLayer(-15);
    auto sunSpr = sunObj->CreateComponent<SpriteRenderer>();
    sunSpr->LoadTexture(L"../Resource/BGSun.png");
    sunObj->transform->pos.worldPosition = { 800.f, 400.f };
    nightSystem->m_Sun = sunObj;

    


    // 달 이미지
    auto moonObj = CreateGameObject<GameObject>();
    moonObj->transform->SetSortingLayer(-15);
    auto moonSpr = moonObj->CreateComponent<SpriteRenderer>();
    moonSpr->LoadTexture(L"../Resource/BGMoon.png");
    moonObj->transform->pos.worldPosition = { 800.f, -300.f };
    nightSystem->m_Moon = moonObj;

    // 해/달 막대기 이미지
    auto sunStickObj = CreateGameObject<GameObject>();
    sunStickObj->transform->SetSortingLayer(-16);
    auto sunStickSpr = sunStickObj->CreateComponent<SpriteRenderer>();
    sunStickSpr->LoadTexture(L"../Resource/홈.png");
    sunStickObj->transform->pos.worldPosition = { 800.f, 50.f};


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
    std::wstring turretImages_Upgrade[] = {
        L"../Resource/30201_2.png",
        L"../Resource/30202_2.png",
        L"../Resource/30203_2.png",
        L"../Resource/30204_2.png",
        L"../Resource/30205_2.png",
        L"../Resource/30206_2.png"
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
        turretUIComp->defaultPath = turretImages[i];
        turretUIComp->upgradePath = turretImages_Upgrade[i];
        turretUIComp->button = turretButton;
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
        blackGround->alpha = 0.7f;

        auto costText = CreateGameObject<GameObject>();
        costText->transform->SetParent(turretUIChild->transform);
        costText->transform->type = Type::Ui;
        costText->transform->pos.rectposition = { {0.f, 60.f}, {120.f, 100.f} };
        auto textUI = costText->CreateComponent<TextUIRenderer>();
        turretUIComp->textUI = textUI;
    }
    auto t1 = btn[0]->gameObject->GetComponent<TurretUI>();
    btn[0]->AddListener([GameManager, t1]() {GameManager->StartBatch(t1->GetIndex()); SoundManager::GetInstance().PlaySoundW(L"clickbtn", false); });
    auto t2 = btn[1]->gameObject->GetComponent<TurretUI>();
    btn[1]->AddListener([GameManager, t2]() {GameManager->StartBatch(t2->GetIndex()); SoundManager::GetInstance().PlaySoundW(L"clickbtn", false); });
    auto t3 = btn[2]->gameObject->GetComponent<TurretUI>();
    btn[2]->AddListener([GameManager, t3]() {GameManager->StartBatch(t3->GetIndex()); SoundManager::GetInstance().PlaySoundW(L"clickbtn", false); });
    auto t4 = btn[3]->gameObject->GetComponent<TurretUI>();
    btn[3]->AddListener([GameManager, t4]() {GameManager->StartBatch(t4->GetIndex()); SoundManager::GetInstance().PlaySoundW(L"clickbtn", false); });
    auto t5 = btn[4]->gameObject->GetComponent<TurretUI>();
    btn[4]->AddListener([GameManager, t5]() {GameManager->StartBatch(t5->GetIndex()); SoundManager::GetInstance().PlaySoundW(L"clickbtn", false); });
    auto t6 = btn[5]->gameObject->GetComponent<TurretUI>();
    btn[5]->AddListener([GameManager, t6]() {GameManager->StartBatch(t6->GetIndex()); SoundManager::GetInstance().PlaySoundW(L"clickbtn", false); });
    // HP 및 MP 바 UI
    
    auto hpBarObjBackground = CreateGameObject<GameObject>();
    auto hpBarImagebg = hpBarObjBackground->CreateComponent<ImageUIRenderer>();
    hpBarObjBackground->transform->SetParent(uiObj->transform);
    hpBarObjBackground->transform->type = Type::Ui;
    hpBarObjBackground->transform->pos.rectposition = { {20.f,10.f} ,{20.f + 820.f,30.f} };
    hpBarImagebg->LoadTexture(L"../Resource/30402.png");
    auto expBarObjBackground = CreateGameObject<GameObject>();
    auto expBarImagebg = expBarObjBackground->CreateComponent<ImageUIRenderer>();
    expBarObjBackground->transform->SetParent(uiObj->transform);
    expBarObjBackground->transform->type = Type::Ui;
    expBarObjBackground->transform->pos.rectposition = { {20.f,35.f} ,{20.f + 820.f,55.f} };
    expBarImagebg->LoadTexture(L"../Resource/30402.png");

    // hpbar
    auto hpBarObj = CreateGameObject<GameObject>();
    auto hpBarImage = hpBarObj->CreateComponent<ImageUIRenderer>();
    hpBarObj->transform->SetParent(uiObj->transform);
    hpBarObj->transform->type = Type::Ui;
    hpBarObj->transform->pos.rectposition = { {20.f,10.f} ,{20.f + 820.f,30.f} };
    hpBarUi = hpBarObj->CreateComponent<Hpbar>();
    pineApple->hpbar = hpBarUi;
    hpBarUi->ImageRender = hpBarImage;
    hpBarImage->LoadTexture(L"../Resource/30403_02.png");

    auto hpTextObj = CreateGameObject<GameObject>();
    hpTextObj->transform->SetSortingLayer(1);
    auto hpText = hpTextObj->CreateComponent<TextUIRenderer>();
    hpText->SetFontSize(22.f);
    hpText->SetFont(L"TAEBAEK font TTF");
    hpTextObj->transform->SetParent(uiObj->transform);
    hpTextObj->transform->type = Type::Ui;
    hpTextObj->transform->pos.rectposition = { {20.f,10.f} ,{20.f + 820.f,37.f} };
    hpText->SetAlignCenter(0);
    hpText->SetTextColor(D2D1::ColorF::White);
    pineApple->hpText = hpText;
    //hpText->text = L"100/100";

    // expbar
    auto mpBarObj = CreateGameObject<GameObject>();
    auto mpBarImage = mpBarObj->CreateComponent<ImageUIRenderer>();
    mpBarObj->transform->SetParent(uiObj->transform);
    mpBarObj->transform->type = Type::Ui;
    mpBarObj->transform->pos.rectposition = { {20.f,35.f} ,{20.f + 820.f,55.f} };
    auto mpBar = mpBarObj->CreateComponent<Mpbar>();
    pineApple->expbar = mpBar;
    mpBar->ImageRender = mpBarImage;
    mpBarImage->LoadTexture(L"../Resource/30402_02.png");

    auto expTextObj = CreateGameObject<GameObject>();
    expTextObj->transform->SetSortingLayer(1);
    auto expText = expTextObj->CreateComponent<TextUIRenderer>();
    expText->SetFontSize(22.f);
    expText->SetFont(L"TAEBAEK font TTF");
    expTextObj->transform->SetParent(uiObj->transform);
    expTextObj->transform->type = Type::Ui;
    expTextObj->transform->pos.rectposition = { {20.f,35.f} ,{20.f + 820.f,62.f} };
    expText->SetAlignCenter(0);
    expText->SetTextColor(D2D1::ColorF::Green);
    pineApple->expText = expText;
    //expText->text = L"100/100";

    // harvestAbleBar {385.f,7.f} ,{1200.f,27.f} 0%~100%
    auto harvestBarObj = CreateGameObject<GameObject>();
    auto harvestBarAnim = harvestBarObj->CreateComponent<SpriteUIAnimation>();
    harvestBarObj->transform->SetParent(mpBarObj->transform);
    harvestBarObj->transform->type = Type::Ui;
    harvestBarObj->transform->pos.rectposition = { {385.f,7.f} ,{1200.f,27.f} };
    harvestBarAnim->LoadTexture(L"../Resource/30407.png");
    harvestBarAnim->LoadAnimationAsset(L"HarvestAbleBar");
    harvestBarAnim->SetAnimation(0, false);
    pineApple->harvestableAnim = harvestBarAnim;

    // 골드 Ui
    auto GoldObj = CreateGameObject<GameObject>();
    auto GoldImage = GoldObj->CreateComponent<ImageUIRenderer>();
    GoldObj->transform->SetParent(uiObj->transform);
    GoldObj->transform->type = Type::Ui;
    GoldObj->transform->pos.rectposition = { {20.f + 820.f + spacing ,98.f} ,{20.f + 820.f + spacing + 270.f, 196.f} };
    GoldImage->LoadTexture(L"../Resource/30404.png");
     
    auto Goldchild = CreateGameObject<GameObject>();
    auto GoldUi = Goldchild->CreateComponent<TextUIRenderer>();
    GoldUi->SetFontSize(40.f);
    auto g = GoldUi->SetFont(L"TAEBAEK font TTF");
    Goldchild->transform->SetParent(GoldObj->transform);
    Goldchild->transform->type = Type::Ui;
    Goldchild->transform->pos.rectposition = { {35.f,20.f},{280.f,77.f} };
    GoldUi->SetAlignCenter(0);
    pineApple->goldbar = GoldUi;

    // wstring str;


    // 레벨 버튼 
    auto LVObj = CreateGameObject<GameObject>();
    auto LVImage = LVObj->CreateComponent<ImageUIRenderer>();
    LVObj->transform->SetParent(uiObj->transform);
    LVObj->transform->type = Type::Ui;
    LVObj->transform->pos.rectposition = { {20.f + 820.f + spacing ,0.f} ,{20.f + 820.f + spacing + 270.f, 98.f} };
    LVImage->LoadTexture(L"../Resource/30406.png");

    auto LVchild = CreateGameObject<GameObject>();
    auto LVUi = LVchild->CreateComponent<TextUIRenderer>();
    LVUi->SetFontSize(40.f);
    auto l = LVUi->SetFont(L"TAEBAEK font TTF");
    LVchild->transform->SetParent(LVObj->transform);
    LVchild->transform->type = Type::Ui;
    LVchild->transform->pos.rectposition = { {35.f,20.f},{280.f,77.f} };
    LVUi->SetAlignCenter(0);
    pineApple->LVbar = LVUi;

    // 업그레이드 버튼 -> 이거 완성 500 * 500
    auto Upgradeobj = CreateGameObject<GameObject>();
    auto UpgradebtnImage = Upgradeobj->CreateComponent<Button>();
    Upgradeobj->transform->SetParent(uiObj->transform);
    Upgradeobj->transform->type = Type::Ui;
    Upgradeobj->transform->pos.rectposition = { {20.f + 820.f + spacing + 270.f + spacing,10.f} ,{20.f + 820.f + spacing + 270.f + spacing + 180.f, 200.f - spacing} };
    UpgradebtnImage->AddListener([=]() {
        dynamicData->isUpgrade = !dynamicData->isUpgrade; 
        if (dynamicData->isUpgrade == true) {
            UpgradebtnImage->LoadTexture(L"../Resource/30207_2.png");
        }
        else {
            UpgradebtnImage->LoadTexture(L"../Resource/30207.png");
        }
        SoundManager::GetInstance().PlaySoundW(L"clickbtn", false);
    });
    UpgradebtnImage->LoadTexture(L"../Resource/30207.png");

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

    auto harvestBlackObj = CreateGameObject<GameObject>();
    auto harvestBlackSpr = harvestBlackObj->CreateComponent<ImageUIRenderer>();
    harvestBlackObj->transform->SetParent(uiObj->transform);
    harvestBlackObj->transform->type = Type::Ui;
    harvestBlackObj->transform->pos.rectposition = { {20.f + 820.f + spacing + 270.f + spacing + 180.f + spacing,10.f} ,{20.f + 820.f + spacing + 270.f + spacing + 180.f + spacing + 180.f, 200.f - spacing} };
    harvestBlackSpr->LoadTexture(L"../Resource/39208_2.png");
    harvestBlackSpr->alpha = 0.5f;
    pineApple->harvestAbleBlack = harvestBlackObj;

    //// 검은색 배경과 버튼 그룹 생성
    //auto uiGroup = CreateGameObject<GameObject>();
    //uiGroup->transform->type = Type::Ui;
    //uiGroup->SetActive(false); // 초기에는 비활성화
    //uiGroup->transform->pos.rectposition.leftBottom = { 0.f, 0.f };
    //uiGroup->transform->pos.rectposition.rightTop = { 1920.f, 1080.f };

    // 반투명 검은색 배경 추가
    auto blackObj = CreateGameObject<GameObject>();
    blackObj->transform->type = Type::Ui;
    
    //blackObj->transform->SetSortingLayer(1); // 다른 UI나 오브젝트보다 뒤에 있도록 설정
    auto blackSpr = blackObj->CreateComponent<ImageUIRenderer>();
    blackSpr->alpha = 0.5f;
    blackObj->transform->pos.rectposition.leftBottom = { 0.f, 0.f };
    blackObj->transform->pos.rectposition.rightTop = {1920.f, 1080.f };
    blackSpr->LoadTexture(L"../Resource/opactiyBg.png");
    //bgSpr->SetColor(D2D1::ColorF(0, 0, 0, 0.5f)); // 검은색 배경 (반투명)
    //bgSpr->transform->pos.rectposition = { {0.f, 0.f} ,{1920.f, 1080.f} };

    // 코모서스 최상위 헤더
    auto headTextObj = CreateGameObject<GameObject>();
    headTextObj->transform->SetParent(blackObj->transform);
    headTextObj->transform->type = Type::Ui;
    headTextObj->transform->pos.rectposition.leftBottom = { 530.f, 900.f };
    headTextObj->transform->pos.rectposition.rightTop = { 1500.f, 1000.f };
    auto headText = headTextObj->CreateComponent<TextUIRenderer>();
    headText->text = L"파인애플을 바치자 코모서스가 응답합니다.";
    headText->SetFontSize(50.f);
    headText->SetFont(L"TAEBAEK font TTF");
    headText->SetAlignCenter(0);
    headText->SetTextColor(D2D1::ColorF(D2D1::ColorF::White));
    
    /*gamePopup* end = new gamePopup();
    pineApple->endpopup = end;
    end->Uis.push_back();*/
    gameover = new gamePopup();
    waveSystem->gameover = gameover;
    pineApple->endpopup = gameover;
   
    // game victory popup
    {
        
        auto bgObj = CreateGameObject<GameObject>();
        bgObj->transform->type = Type::Ui;
        auto bgSpr = bgObj->CreateComponent<ImageUIRenderer>();
        bgSpr->alpha = 0.5f;
        bgObj->transform->pos.rectposition.leftBottom = { 0.f, 0.f };
        bgObj->transform->pos.rectposition.rightTop = { 1920.f, 1080.f };
        bgSpr->LoadTexture(L"../Resource/승리패배팝업/40101_승리화면_ 백그라운드.png");
        gameover->victory.push_back(bgObj);

        auto popupObj = CreateGameObject<GameObject>();
        popupObj->transform->SetParent(bgObj->transform);
        popupObj->transform->type = Type::Ui;
        popupObj->transform->pos.rectposition.leftBottom = { 580.f, 459.f };
        popupObj->transform->pos.rectposition.rightTop = { 1340.f, 861.f };
        auto popupImage = popupObj->CreateComponent<ImageUIRenderer>();
        popupImage->LoadTexture(L"../Resource/승리패배팝업/40401_승리로고_x584_y264.png"); // Replace with the actual texture path
        gameover->victory.push_back(popupObj);

        auto titleBtnObj = CreateGameObject<GameObject>();
        titleBtnObj->transform->SetParent(bgObj->transform);
        titleBtnObj->transform->type = Type::Ui;
        titleBtnObj->transform->pos.rectposition.leftBottom = { 808.f, 309.f };
        titleBtnObj->transform->pos.rectposition.rightTop = { 1112.f, 401.f };
        auto titleButton = titleBtnObj->CreateComponent<Button>();
        titleButton->LoadTexture(L"../Resource/승리패배팝업/40201_타이틀로돌아가기_x811_y724 .png"); // Replace with actual texture path
        gameover->victory.push_back(titleBtnObj);

        titleButton->AddListener([]() {
            SoundManager::GetInstance().PlaySoundW(L"clickbtn", false);
            SceneManager::GetInstance().SetChangeSceneFlag("StartScene");
            });
        gameover->victoryUIoff();
       
    }

    // game defeat popup
    {
        auto bgObj = CreateGameObject<GameObject>();
        bgObj->transform->type = Type::Ui;
        auto bgSpr = bgObj->CreateComponent<ImageUIRenderer>();
        bgSpr->alpha = 0.5f;
        bgObj->transform->pos.rectposition.leftBottom = { 0.f, 0.f };
        bgObj->transform->pos.rectposition.rightTop = { 1920.f, 1080.f };
        bgSpr->LoadTexture(L"../Resource/승리패배팝업/50101_패배화면_ 백그라운드.png");
        gameover->defeat.push_back(bgObj);

        auto popupObj = CreateGameObject<GameObject>();
        popupObj->transform->SetParent(bgObj->transform);
        popupObj->transform->type = Type::Ui;
        popupObj->transform->pos.rectposition.leftBottom = { 580.f, 459.f };
        popupObj->transform->pos.rectposition.rightTop = { 1340.f, 861.f };
        auto popupImage = popupObj->CreateComponent<ImageUIRenderer>();
        popupImage->LoadTexture(L"../Resource/승리패배팝업/50401_패배로고_x624_y279.png"); // Replace with the actual texture path
        gameover->defeat.push_back(popupObj);

        auto retryBtnObj = CreateGameObject<GameObject>();
        retryBtnObj->transform->SetParent(bgObj->transform);
        retryBtnObj->transform->type = Type::Ui;
        retryBtnObj->transform->pos.rectposition.leftBottom = { 640.f, 309.f };
        retryBtnObj->transform->pos.rectposition.rightTop = { 944.f, 401.f };
        auto retryButton = retryBtnObj->CreateComponent<Button>();
        retryButton->LoadTexture(L"../Resource/승리패배팝업/50201_다시도전_x637_y724.png"); // Replace with actual texture path
        gameover->defeat.push_back(retryBtnObj);

        retryButton->AddListener([]() {
            SoundManager::GetInstance().PlaySoundW(L"clickbtn", false);
            SceneManager::GetInstance().SetChangeSceneFlag("GameScene");
            });

        auto titleBtnObj = CreateGameObject<GameObject>();
        titleBtnObj->transform->SetParent(bgObj->transform);
        titleBtnObj->transform->type = Type::Ui;
        titleBtnObj->transform->pos.rectposition.leftBottom = { 976.f, 309.f };
        titleBtnObj->transform->pos.rectposition.rightTop = { 1280.f, 401.f };
        auto titleButton = titleBtnObj->CreateComponent<Button>();
        titleButton->LoadTexture(L"../Resource/승리패배팝업/50202_타이틀로돌아가기_x984_y724.png"); // Replace with actual texture path
        gameover->defeat.push_back(titleBtnObj);

        titleButton->AddListener([]() {
            SoundManager::GetInstance().PlaySoundW(L"clickbtn", false);
            SceneManager::GetInstance().SetChangeSceneFlag("StartScene");
            });
        gameover->defeatUIoff();
    }
    

    // 이름 텍스트 오브젝트 추가 (자식 오브젝트)
    auto nameTextObj = CreateGameObject<GameObject>();
    nameTextObj->transform->SetParent(blackObj->transform);
    nameTextObj->transform->type = Type::Ui;
    nameTextObj->transform->pos.rectposition.leftBottom = {550.f, 240.f };
    nameTextObj->transform->pos.rectposition.rightTop = { 1500.f, 900.f };
    auto nameText = nameTextObj->CreateComponent<TextUIRenderer>();
    nameText->SetFontSize(55.f);
    nameText->SetFont(L"210 연필스케치");
    nameText->SetAlignCenter(0);
    nameText->SetTextColor(D2D1::ColorF(D2D1::ColorF::Yellow));

    // 버튼 5개 생성 및 초기 비활성화
    ramdomReward* rand = new ramdomReward();
    pineApple->randomReward = rand;
    rand->bgUi.push_back(blackObj);
    rand->textHeader = nameText;

    // 버튼의 위치와 크기를 수동으로 지정
    D2D1_RECT_F buttonPositions[] = {
        {115.f, 270.f, 845.f, 470.f},  // 첫 번째 버튼의 위치 (x1, y1, x2, y2)
        {115.f, 540.f, 845.f, 740.f}, // 두 번째 버튼의 위치
        {1075.f, 270.f, 1805.f, 470.f},  // 세 번째 버튼의 위치
        {1075.f, 540.f, 1805.f, 740.f}, // 네 번째 버튼의 위치
        {540.f, 100.f, 1440.f, 240.f}  // 다섯 번째 버튼의 위치 (중앙 하단)
    };

    // 1. 랜덤하게 데이터를 섞습니다.
 /*   std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(DataManager.harvestPopupStruct.begin(), DataManager.harvestPopupStruct.end(), g);*/

    for (size_t i = 0; i < 4; i++) {
        auto buttonObj = CreateGameObject<GameObject>(); 
        buttonObj->transform->SetSortingLayer(20);
        //buttonObj->transform->SetParent(uiGroup->transform);
        buttonObj->transform->type = Type::Ui;

        // 버튼의 위치와 크기를 설정
        buttonObj->transform->pos.rectposition.leftBottom = { buttonPositions[i].left, buttonPositions[i].top };
        buttonObj->transform->pos.rectposition.rightTop = { buttonPositions[i].right, buttonPositions[i].bottom };

        // 버튼 이미지 설정
        auto buttonImage = buttonObj->CreateComponent<Button>();
        buttonImage->ignoreEventSystem = false;
        //buttonImage->LoadTexture(L"../Resource/30405_harvestpopup_item.png"); // 버튼의 기본 배경 이미지
        rand->btns.push_back(buttonImage);

        //// 이미지 오브젝트 추가 (자식 오브젝트)
        //auto imageObj = CreateGameObject<GameObject>();
        //imageObj->transform->SetParent(buttonObj->transform);
        //imageObj->transform->type = Type::Ui;
        //imageObj->transform->pos.rectposition = {/* 이미지 위치와 크기 설정 */ };
        //imageObj->transform->pos.rectposition.leftBottom = { 47,47 };
        //imageObj->transform->pos.rectposition.rightTop = { 160, 160 };
        //auto spriteRenderer = imageObj->CreateComponent<ImageUIRenderer>();
        //spriteRenderer->LoadTexture(DataManager.harvestPopupStruct[i].Imagepath.c_str()); // 이미지 설정
     
        //rand->Uis.push_back(spriteRenderer);
        //// 이름 텍스트 오브젝트 추가 (자식 오브젝트)
        //auto nameTextObj = CreateGameObject<GameObject>();
        //nameTextObj->transform->SetParent(buttonObj->transform);
        //nameTextObj->transform->type = Type::Ui;
        //nameTextObj->transform->pos.rectposition = {/* 이름 텍스트 위치와 크기 설정 */ };
        //auto nameText = nameTextObj->CreateComponent<TextUIRenderer>();
        //nameText->SetFontSize(25.f);
        //nameText->text = DataManager.harvestPopupStruct[i].reward;
        //nameText->SetTextColor(D2D1::ColorF(D2D1::ColorF::White));
        ////nameText->SetText(L"이름"); // 이름 텍스트 설정
        ////nameText->SetColor(D2D1::ColorF(D2D1::ColorF::White)); // 텍스트 색상 설정

        //nameTextObj->transform->pos.rectposition.leftBottom = { 175, 100};
        //nameTextObj->transform->pos.rectposition.rightTop  = { 700, 170 };
        //nameText->SetAlignCenter(0);
        //rand->TextNameUis.push_back(nameText);
        //// 내용 텍스트 오브젝트 추가 (자식 오브젝트)
        //auto descTextObj = CreateGameObject<GameObject>();
        //descTextObj->transform->SetParent(buttonObj->transform);
        //descTextObj->transform->type = Type::Ui;
        //descTextObj->transform->pos.rectposition = {/* 내용 텍스트 위치와 크기 설정 */ };
        //auto descText = descTextObj->CreateComponent<TextUIRenderer>();
        //descText->SetFontSize(25.f);
        //descText->text = DataManager.harvestPopupStruct[i].rewarOption;
        //descText->SetTextColor(D2D1::ColorF(D2D1::ColorF::Green));
        //descText->SetFontSize(30.f);
        ////descText->SetText(L"내용"); // 내용 텍스트 설정   
        ////descText->SetColor(D2D1::ColorF(D2D1::ColorF::White)); // 텍스트 색상 설정
        //descText->SetAlignCenter(-1);
        //descTextObj->transform->pos.rectposition.leftBottom = { 210, 50};
        //descTextObj->transform->pos.rectposition.rightTop = { 740, 100 };

        //rand->TextStatUis.push_back(descText);

        //pineApple->Popup = buttonImage;
    }

    // givemeth money
    {
        auto buttonObj = CreateGameObject<GameObject>();
        buttonObj->transform->SetSortingLayer(20);
        //buttonObj->transform->SetParent(uiGroup->transform);
        buttonObj->transform->type = Type::Ui;

        // 버튼의 위치와 크기를 설정
        buttonObj->transform->pos.rectposition.leftBottom = { buttonPositions[4].left, buttonPositions[4].top };
        buttonObj->transform->pos.rectposition.rightTop = { buttonPositions[4].right, buttonPositions[4].bottom };

        // 버튼 이미지 설정
        auto buttonImage = buttonObj->CreateComponent<Button>();
        buttonImage->ignoreEventSystem = false;
        buttonImage->LoadTexture(L"../Resource/수확보상팝업/34100_그냥돈.png"); // 버튼의 기본 배경 이미지
        rand->btns.push_back(buttonImage);
        // 이미지 오브젝트 추가 (자식 오브젝트)
        auto imageObj = CreateGameObject<GameObject>();

        // 이름 텍스트 오브젝트 추가 (자식 오브젝트)
        auto nameTextObj = CreateGameObject<GameObject>();
        nameTextObj->transform->SetSortingLayer(21);
        nameTextObj->transform->SetParent(buttonObj->transform);
        nameTextObj->transform->type = Type::Ui;
  
        auto nameText = nameTextObj->CreateComponent<TextUIRenderer>();
        nameText->SetFontSize(65.f);
        nameText->SetFont(L"210 연필스케치");
        nameText->SetAlignCenter(0);
        nameText->SetTextColor(D2D1::ColorF(D2D1::ColorF::Yellow));

        
        // nameText->text = DataManager.plzmoney.rewarOption.c_str();
        pineApple->randomReward->rewardMoney = nameText;

       
        
        //nameText->SetFontSize(70.f);
        DataManager.plzmoney.fn = [pineApple]() {
            auto rewardMoney = DataManager::GetInstance().getMoneyData(pineApple->GetPineAppleLV() - 2);
            pineApple->acquireGold(rewardMoney);
            std::cout << rewardMoney << std::endl;
            //pineApple->randomReward->rewardMoney->text = std::to_wstring(rewardMoney)        .c_str();
            };

        //nameText->SetText(L"이름"); // 이름 텍스트 설정
        //nameText->SetColor(D2D1::ColorF(D2D1::ColorF::White)); // 텍스트 색상 설정    

        //{ 540.f, 100.f, 1440.f, 240.f }
        // x 900 
        // y 140
        nameTextObj->transform->pos.rectposition.leftBottom = { 600, 10 };
        nameTextObj->transform->pos.rectposition.rightTop = { 900, 100 };
        nameText->SetAlignCenter(0);
        
        rand->TextNameUis.push_back(nameText);

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
        SoundManager::GetInstance().PlaySoundW(L"clickbtn", false);
    });

    auto comosusOn1 = CreateGameObject<GameObject>();
    auto comosusOn2 = CreateGameObject<GameObject>();
    auto comosusOn3 = CreateGameObject<GameObject>();
    auto comosusOn4 = CreateGameObject<GameObject>();
    auto comosusOn5 = CreateGameObject<GameObject>();
    auto comosusOn6 = CreateGameObject<GameObject>();
    auto comosusOn7 = CreateGameObject<GameObject>();

    auto comosusOnSpr1 = comosusOn1->CreateComponent<SpriteRenderer>();
    auto comosusOnSpr2 = comosusOn2->CreateComponent<SpriteRenderer>();
    auto comosusOnSpr3 = comosusOn3->CreateComponent<SpriteRenderer>();
    auto comosusOnSpr4 = comosusOn4->CreateComponent<SpriteRenderer>();
    auto comosusOnSpr5 = comosusOn5->CreateComponent<SpriteRenderer>();
    auto comosusOnSpr6 = comosusOn6->CreateComponent<SpriteRenderer>();
    auto comosusOnSpr7 = comosusOn7->CreateComponent<SpriteRenderer>();

    comosusOnSpr1->LoadTexture(L"../Resource/31301.png");
    comosusOnSpr2->LoadTexture(L"../Resource/31302.png");
    comosusOnSpr3->LoadTexture(L"../Resource/31303.png");
    comosusOnSpr4->LoadTexture(L"../Resource/31304.png");
    comosusOnSpr5->LoadTexture(L"../Resource/31305.png");
    comosusOnSpr6->LoadTexture(L"../Resource/31306.png");
    comosusOnSpr7->LoadTexture(L"../Resource/31308.png");

    comosusOn1->transform->SetSortingLayer(-16);
    comosusOn2->transform->SetSortingLayer(-16);
    comosusOn3->transform->SetSortingLayer(-16);
    comosusOn4->transform->SetSortingLayer(-16);
    comosusOn5->transform->SetSortingLayer(-16);
    comosusOn6->transform->SetSortingLayer(-16);
    comosusOn7->transform->SetSortingLayer(-2);

    comosusOn1->transform->pos.worldPosition = { 462.f, 391.f };
    comosusOn2->transform->pos.worldPosition = { 621, 343 };
    comosusOn3->transform->pos.worldPosition = { 135, 294 };
    comosusOn4->transform->pos.worldPosition = { -743,210 };
    comosusOn5->transform->pos.worldPosition = { -318, 0 };
    comosusOn6->transform->pos.worldPosition = { -541,200 };
    comosusOn7->transform->pos.worldPosition = { 0,-1840 };
    
    waveSystem->comosusOn1 = comosusOn1;
    waveSystem->comosusOn2 = comosusOn2;
    waveSystem->comosusOn3 = comosusOn3;
    waveSystem->comosusOn4 = comosusOn4;
    waveSystem->comosusOn5 = comosusOn5;
    waveSystem->comosusOn6 = comosusOn6;
    waveSystem->comosusOn7 = comosusOn7;

    comosusOn1->isActive = false;
    comosusOn2->isActive = false;
    comosusOn3->isActive = false;
    comosusOn4->isActive = false;
    comosusOn5->isActive = false;
    comosusOn6->isActive = false;
    comosusOn7->isActive = false;

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
    SoundManager::GetInstance().StopSound(L"Morning_Bgm");
    SoundManager::GetInstance().ReleaseSound(L"Morning_Bgm");
    delete gameover;
}

void GameScene::Update(float deltaTime) {
    __super::Update(deltaTime);

    //if (testPineApple->GetPineAppleHP() <= 0)
    //{
    //   /* GameTime::GetInstance().SetTimeScale(0.f);
    //    gameover->defeatUIon();*/
    //}

    if (InputManager::GetInstance().IsKeyDown('1')) {
        /*hpBarUi->takeDamage(10.f);
        hpBarUi->ImageRender->slideBar = hpBarUi->getBarWidth();
        std::cout << hpBarUi->ImageRender->m_DstRect.right << std::endl;
        std::cout << hpBarUi->getBarWidth() << std::endl;*/
        GameTime::GetInstance().SetTimeScale(1.f);
    }
    if (InputManager::GetInstance().IsKeyDown('2')) {
        //SceneManager::GetInstance().ChangeScene("StartScene");
        GameTime::GetInstance().SetTimeScale(5.f);
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
        cuttons->check = true;
        cuttons->ctfn = [=]() { SceneManager::GetInstance().SetChangeSceneFlag("StartScene"); };
    }

    // 동시 사운드 테스트 
    if (InputManager::GetInstance().IsKeyDown('5')) {
        // 5번을 클릭할 때 마다 SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/hello.mp3"); 사운드가 
        // 기존의 사운드는 그대로 출력되고 새 사운드가 중복으로 출력되게 하려고 하는데, 어떻게 하면 좋을까?
         // 새로운 고유 이름으로 사운드 로드
        //std::wstring soundName = L"gimicSuccess";
        //SoundManager::GetInstance().LoadSound(soundName, L"../Media/gimicSuccess.mp3");

        //// 로드된 사운드를 재생
        //SoundManager::GetInstance().PlaySoundW(soundName, true);
    }

    if (InputManager::GetInstance().IsKeyDown('6')) {
        testPineApple->AddExp(50.f);
    }
    if (InputManager::GetInstance().IsKeyDown('7')) {
        testWave->StartNextWave();
    }

    SoundManager::GetInstance().Update();
}

void GameScene::Render(D2DRenderer* _render) {
    __super::Render(_render);

    //auto pd = testPineApple;
    //int gold = pd->GetPineAppleGold();
    ////std::cout << gold << std::endl;
    //std::wstring pineAppleGold = std::to_wstring(gold);
    //D2DRenderer::getIncetance().DrawStringTextw(pineAppleGold.c_str(), m_GameObjects[0]->transform->m_WorldTransform, D2D1::ColorF::Red);
    /*float currentHP = pd->GetPineAppleHP();
    std::wstring currentHp = std::to_wstring(currentHP);
    D2DRenderer::getIncetance().DrawStringTextw(pineAppleGold.c_str(), m_GameObjects[0]->transform->m_WorldTransform, D2D1::ColorF::Red);
    float currentEXP = pd->GetCurrentExp();
    std::wstring curtHp = std::to_wstring(currentEXP);
    D2DRenderer::getIncetance().DrawStringTextw(pineAppleGold.c_str(), m_GameObjects[0]->transform->m_WorldTransform, D2D1::ColorF::Red);*/


    
    /*std::cout << cam->transform->m_WorldTransform.dx << std::endl;
    std::cout << cam->transform->m_WorldTransform.dy << std::endl;*/

    /*int pineappleLV = pd->GetPineAppleLV();   
    std::wstring pineAppleLV = std::to_wstring(pineappleLV);
    D2DRenderer::getIncetance().DrawStringTextw(pineAppleLV.c_str(), m_GameObjects[0]->transform->m_WorldTransform, D2D1::ColorF::Blue);*/


}
