#include "Enemy.h"

#include "WaveSystem.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/GameTime.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "EnemyFactory.h"
#include "BulletFactory.h"
#include "MainPineApple.h"
#include "DynamicData.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include "../D2DEngine/SoundManager.h"
#include "gamePopup.h"

WaveSystem::WaveSystem()
{
    // 사운드 초기화 및 로드
    SoundManager::GetInstance().LoadSound(L"WaveStart_Se", L"../Media/6_Sound/scene3/Se/WaveStart_Se.wav");
    SoundManager::GetInstance().SetVolume(L"WaveStart_Se", 0.5f);
}

WaveSystem::~WaveSystem()
{
    delete enemyFactory; // EnemyFactory 객체 삭제
    //m_Enemies.clear();
}

//void WaveSystem::SpawnWave()
//{
//    int numEnemiesToSpawn = 1; // 일단은 웨이브 1개씩 설정
//
//    //m_Enemies.clear();  // 이전 웨이브에서 생성된 적을 삭제 (필요한 경우)
//
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<float> distY(-240.0f, -100.f);
//    std::uniform_real_distribution<float> flyDistY(300.f,400.0f);
//    std::bernoulli_distribution distSide(0.5); // 50% 확률로 true 또는 false 생성
//
//    for (int i = 0; i < numEnemiesToSpawn; ++i)
//    {
//        Enemy* newEnemy = enemyFactory->GetEnemyFromPool(30601);
//     
//        bool spawnOnLeft = distSide(gen); // 50% 확률로 왼쪽 또는 오른쪽에서 스폰
//
//        float spawnY = distY(gen);
//        float skySpanY = flyDistY(gen);
//
//        Vector2 spawnPosition;
//        Vector2 moveDirection;
//
//        auto type = enemyFactory->enemyType;
//        if (type == 2)
//        {
//            if (spawnOnLeft)
//            {
//                spawnPosition = Vector2(-800.0f, skySpanY);
//                moveDirection = Vector2(1.0f, 0.0f);
//
//                newEnemy->gameObject->GetComponent<SpriteRenderer>()->SetFilp(true, false);
//            }
//            else
//            {
//                spawnPosition = Vector2(900.0f, skySpanY);
//                moveDirection = Vector2(-1.0f, 0.0f);
//
//            }
//        }
//        else
//        {
//            if (spawnOnLeft)
//            {
//                spawnPosition = Vector2(-800.0f, spawnY);
//                moveDirection = Vector2(1.0f, 0.0f);
//            }
//            else
//            {
//                spawnPosition = Vector2(900.0f, spawnY);
//                moveDirection = Vector2(-1.0f, 0.0f);
//                newEnemy->gameObject->GetComponent<SpriteRenderer>()->SetFilp(true, false);
//            }
//        }
//
//        
//
//        newEnemy->gameObject->transform->pos.worldPosition = spawnPosition;
//        newEnemy->move->SetDirection(moveDirection);
//        //newEnemy->move->SetSpeed(50.0f);
//        newEnemy->tmpY = spawnPosition.y;
//        newEnemy->move->SetSpeed(newEnemy->enemyData.moveSpeed);
//        newEnemy->gameObject->SetActive(true);
//        //m_Enemies.push_back(newEnemy);
//        std::cout << "적이 생성되었습니다" << std::endl;
//    }
//}

bool WaveSystem::islastWave()
{
    return (currentWave > DataManager::GetInstance().GetMaxWaveCount());
}

void WaveSystem::LoadWaveData()
{
    if (currentWave > DataManager::GetInstance().GetMaxWaveCount()) return;
    leftEnemyDatas.clear();
    leftEnemyDatas.assign(DataManager::GetInstance().GetWaveData(currentWave)->leftWaveData.begin(), 
            DataManager::GetInstance().GetWaveData(currentWave)->leftWaveData.end());
    rightEnemyDatas.clear();
    rightEnemyDatas.assign(DataManager::GetInstance().GetWaveData(currentWave)->rightWaveData.begin(),
            DataManager::GetInstance().GetWaveData(currentWave)->rightWaveData.end());

}

void WaveSystem::Generator()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distY(-240.0f, -100.f);
    std::uniform_real_distribution<float> flyDistY(300.f, 400.0f);

    float delta = GameTime::GetInstance().GetDeltaTime();
    for (auto& left : leftEnemyDatas) {
        if (left.count > 0) {
            left.startTime -= delta;
            if (left.startTime < 0.f) {
                left.interval -= delta;
                if (left.interval < 0.f) {
                    left.count -= 1;
                    left.interval += left.maxInterval;
                    // 몹소환
                    Enemy* enemy = enemyFactory->GetEnemyFromPool(left.id);
                    int eliteType = DataManager::GetInstance().GetEnemyData(left.id)->eliteType;
                    enemy->defaultAnimationNumber = eliteType;
                    float spawnY = IsFly(left.id) ? flyDistY(gen) : distY(gen);
                    Vector2 spawnPosition = Vector2(-1500.0f, left.id == 30621 ? -60.f: spawnY);
                    Vector2 moveDirection = Vector2(1.0f, 0.0f);
                    enemy->gameObject->GetComponent<SpriteAnimation>()->SetAnimation(eliteType, false);
                    enemy->gameObject->transform->pos.worldPosition = spawnPosition;
                    enemy->move->SetDirection(moveDirection);
                    enemy->tmpY = spawnPosition.y;
                    enemy->move->SetSpeed(enemy->enemyData.moveSpeed);
                    enemy->gameObject->SetActive(true);
                    enemy->waveAmplitude = enemy->enemyData.waveAmplitude;
                    enemy->waveFrequency = enemy->enemyData.waveFrequency;

                    enemy->defaultSpeed = enemy->enemyData.moveSpeed;

                    enemy->AttackSprite->SetCenter(Vector2(0.f, 0.5f));
                    enemy->AttackSprite->alpha = 0.f;
                }
            }
        }
    }
    for (auto& right : rightEnemyDatas) {
        if (right.count > 0) {
            right.startTime -= delta;
            if (right.startTime < 0.f) {
                right.interval -= delta;
                if (right.interval < 0.f) {
                    right.count -= 1;
                    right.interval += right.maxInterval;
                    // 몹소환
                    Enemy* enemy = enemyFactory->GetEnemyFromPool(right.id);
                    int eliteType = DataManager::GetInstance().GetEnemyData(right.id)->eliteType;
                    enemy->defaultAnimationNumber = eliteType;
                    float spawnY = IsFly(right.id) ? flyDistY(gen) : distY(gen);
                    Vector2 spawnPosition = Vector2(1500.0f, right.id == 30621 ? -60.f : spawnY);
                    Vector2 moveDirection = Vector2(-1.0f, 0.0f);
                    enemy->gameObject->GetComponent<SpriteAnimation>()->SetAnimation(eliteType, true);

                    enemy->gameObject->transform->pos.worldPosition = spawnPosition;
                    enemy->move->SetDirection(moveDirection);
                    enemy->tmpY = spawnPosition.y;
                    enemy->move->SetSpeed(enemy->enemyData.moveSpeed);
                    enemy->gameObject->SetActive(true);
                    enemy->waveAmplitude = enemy->enemyData.waveAmplitude;
                    enemy->waveFrequency = enemy->enemyData.waveFrequency;

                    enemy->defaultSpeed = enemy->enemyData.moveSpeed;

                    enemy->AttackSprite->SetCenter(Vector2(0.f, 0.5f));
					enemy->AttackSprite->SetFilp(true, false);
                    enemy->AttackSprite->alpha = 0.f;
                }
            }
        }
    }
}

void WaveSystem::PushingTutorial(int curWave, GameObject* Tuto)
{   
    float elapsed = 0.f;
    if (curWave <= 2) {
		elapsed = elapsedTime;
	}
    else if (curWave > 2) {
        elapsed = elapsedTime3;
    }
    if (currentWave == curWave && waveTimer > 0.f) {

        if (elapsed > 0.66f)
        {
            elapsed = 0.66f;
        }
        float t1 = (0.66f - elapsed) / .66f;
        float t2 = (elapsed) / .66f;
        //std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
        Tuto->transform->pos.worldPosition.y = (t1 * 712.f) + (t2 * 370.f);
        
    }
    
    
}

void WaveSystem::PullingTutorial(int curWave, GameObject* Tuto)
{   
    float elapsed = 0.f;
    if (curWave <= 3) {
        elapsed = elapsedTime;
    }
    else if (curWave > 3) {
        elapsed = elapsedTime3;
    }
	if (currentWave == curWave && waveTimer > 0.f) {
		if (elapsed > 0.66f)
		{
			elapsed = 0.66f;
		}
		float t1 = (0.66f - elapsed) / .66f;
		float t2 = (elapsed) / .66f;
		//std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
		Tuto->transform->pos.worldPosition.y = (t1 * 370.f) + (t2 * 712.f);
		
	}
}

void WaveSystem::PushingBottomTutorial(int curWave)
{
    if (currentWave == curWave && waveTimer > 0.f) {

        if (elapsedTime > 0.66f)
        {
            elapsedTime = 0.66f;
        }
        float t1 = (0.66f - elapsedTime) / .66f;
        float t2 = (elapsedTime) / .66f;
        //std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
        tutorialBottom->transform->pos.worldPosition.y = (t1 * -720.f) + (t2 * -100.f);
        
    }
}

void WaveSystem::PullingBottomTutorial(int curWave)
{
    if (currentWave == curWave && waveTimer > 0.f) {

        if (elapsedTime > 0.66f)
        {
            elapsedTime = 0.66f;
        }
        float t1 = (0.66f - elapsedTime) / .66f;
        float t2 = (elapsedTime) / .66f;
        //std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
        tutorialBottom->transform->pos.worldPosition.y = (t1 * -100.f) + (t2 * -720.f);
        
    }
}

void WaveSystem::PushingBottom2Tutorial(int curWave)
{   
    if (currentWave == curWave && waveTimer > 0.f) {

        if (elapsedTime3 > 0.66f)
        {
            elapsedTime3 = 0.66f;
        }
        float t1 = (0.66f - elapsedTime3) / .66f;
        float t2 = (elapsedTime3) / .66f;
        //std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
        tutorial2Bottom->transform->pos.rectposition.leftBottom = { 1482.5f, (200 + 130) * t2 + -250 * t1 };
        tutorial2Bottom->transform->pos.rectposition.rightTop = { 1482.5f + 170, (200 + 260) * t2 + ( -250 + 130)* t1};
    }
}

void WaveSystem::PullingBottom2Tutorial(int curWave)
{
    if (currentWave == curWave && waveTimer > 0.f) {

        if (elapsedTime3 > 0.66f)
        {
            elapsedTime3 = 0.66f;
        }
        float t1 = (0.66f - elapsedTime3) / .66f;
        float t2 = (elapsedTime3) / .66f;
        //std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
        tutorial2Bottom->transform->pos.rectposition.leftBottom = { 1482.5f, (200 + 130) * t1 + -250 * t2 };
        tutorial2Bottom->transform->pos.rectposition.rightTop = { 1482.5f + 170, (200 + 260) * t1 + (-250 + 130) * t2 };
        
    }
}

void WaveSystem::PushingHowManyDay(int curWave)
{
    if (currentWave == curWave && waveTimer > 0.f && currentWave % 4 == 1) {

        if (elapsedTime > 0.66f)
        {
            elapsedTime = 0.66f;
        }
        float t1 = (0.66f - elapsedTime) / .66f;
        float t2 = (elapsedTime) / .66f;
        //std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
        howManyLeft[(curWave - 5) / 4]->transform->pos.worldPosition.y = (t1 * 712.f) + (t2 * 420.f);
        
    }
	
}

void WaveSystem::PullingHowManyDay(int curWave)
{
    if (currentWave == curWave && waveTimer > 0.f && currentWave % 4 == 1) {
        if (elapsedTime2 > 0.66f)
        {
            elapsedTime2 = 0.66f;
        }
        float t1 = (0.66f - elapsedTime2) / .66f;
        float t2 = (elapsedTime2) / .66f;
        //std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
        howManyLeft[(curWave - 5)/4]->transform->pos.worldPosition.y = (t1 * 420.f) + (t2 * 712.f);
        
    }
}

bool WaveSystem::IsFly(int id)
{
    if(id >= 30613 && id <= 30616)
        return true;
    return false;
}

void WaveSystem::StartNextWave()
{   
    if (islastWave() == false)
    {
        // 웨이브 시작 효과음 
		std::cout << "Wave Start!" << std::endl;
        SoundManager::GetInstance().PlaySoundW(L"WaveStart_Se", false);
        currentWave++;
        elapsedTime = 0.f;
		elapsedTime2 = 0.f;
		elapsedTime3 = 0.f;
		isHowManyPushed = false;
        LoadWaveData();
        waveTimer = maxWaveTimer;  // 타이머 초기화 //현재 15초
        //SpawnWave();        // 새로운 wave 스폰

        if (currentWave == 1) {
            comosusOn1->isActive = true;
        }
        if (currentWave == 9) {
            comosusOn1->isActive = false;
            comosusOn2->isActive = true;
        }
        if (currentWave == 17) {
            comosusOn2->isActive = false;
            comosusOn3->isActive = true;
        }
        if (currentWave == 25) {
            comosusOn3->isActive = false;
            comosusOn4->isActive = true;
        }
        if (currentWave == 33) {
            comosusOn4->isActive = false;
            comosusOn5->isActive = true;
        }
        if (currentWave == 41) {
            comosusOn5->isActive = false;
            comosusOn6->isActive = true;
        }
        if (currentWave == 49) {
            comosusOn6->isActive = false;
        }
        if (currentWave == 53) {
            comosusOn7->isActive = true;
            comosus7posY = comosusOn7->transform->m_WorldTransform.dy;
        }
    }
    else {

    }
    // maxWave에 도달했을 경우 추가적인 처리 필요 (게임 종료 또는 루프 등)
}

void WaveSystem::Init()
{
    enemyFactory = new EnemyFactory(scene); // EnemyFactory 생성
    enemyFactory->bulletFactory = bulletFactory;
    enemyFactory->mainPineApple = mainPineApple;
}

void WaveSystem::Update(float deltaTime)
{   
   /* if (islastWave())
    {
        GameTime::GetInstance().SetTimeScale(0.f);
        gameover->victoryUIon();
    }*/
   
    if (comosusOn7->isActive == true) {
        comosus7Timer += deltaTime;
        if (comosus7Timer > 1.f) comosus7Timer = 1.f;

        comosusOn7->transform->pos.worldPosition.y = (1.f - comosus7Timer) * comosus7posY;
    }


    // 웨이브 타이머 감소
    waveTimer -= deltaTime;
	//std::cout << "waveTimer: " << waveTimer << std::endl;
    elapsedTime += deltaTime;
    // 웨이브 타이머가 0 이하가 되었고, 적이 남아 있으면
    if (waveTimer <= 0.0f)
    {
        waveTimer += maxWaveTimer;
        StartNextWave();
    }
	
    PushingTutorial(1, tutorial1);
    PushingTutorial(2, tutorial2);
    PullingTutorial(3, tutorial2);
    if (waveTimer<7.f) {
		elapsedTime3 += deltaTime;
        
        PushingTutorial(3, tutorial3);
		PushingTutorial(4, tutorial4);
        PushingTutorial(5, tutorial5);
		PushingTutorial(6, tutorial6);
		PushingTutorial(17, tutorial17);
        PushingTutorial(53, tutorial53);
        PushingTutorial(54, tutorial54);
        PushingBottom2Tutorial(4);
        
        
        PullingTutorial(4, tutorial3);
		PullingTutorial(5, tutorial4);
        PullingTutorial(6, tutorial5);
		PullingTutorial(7, tutorial6);
		PullingTutorial(18, tutorial17);
        PullingTutorial(54, tutorial53);
        PullingTutorial(55, tutorial54);
        PullingBottom2Tutorial(5);

    }
    
    
    PushingBottomTutorial(1);

    if (currentWave >= 5 && !isHowManyPushed && currentWave <= 53) {
        PushingHowManyDay(currentWave);
    }

    if (currentWave >= 5 && waveTimer <= 10.f && currentWave <= 53) {
		elapsedTime2 += deltaTime;
        PullingHowManyDay(currentWave);
        
        
    } 
    
    if (currentWave == 1 && waveTimer < 14.f)
    {   
		isTutorial1Pushed = true;
    }

    if (currentWave == 1 && isTutorial1Pushed && mainPineApple->rewardData->isTutorialSkipped == false)
    {   
        GameTime::GetInstance().SetTimeScale(0.f);
    }

	if(currentWave == 1 && isTutorial1Pushed && waveTimer < 14.f && mainPineApple->rewardData->isTutorialSkipped == true)
	{   
		if (!isElaspedTimeReset)
		{
            elapsedTime = 0.f;
		}
		GameTime::GetInstance().SetTimeScale(1.f);
        PullingBottomTutorial(1);
        PullingTutorial(1, tutorial1);
        isElaspedTimeReset = true;
	}
    
    Generator();

    // 태양 이동
    
    dayNightCycle->SunMove(GameTime::GetInstance().GetDeltaTime(), (currentWave - 1) % 4); //하드코딩 하긴했는데 +2는 시작할때 태양이 중간에 있으면 안되서 그런거임!
    dayNightCycle->MoonMove(GameTime::GetInstance().GetDeltaTime(), (currentWave) % 4); 
    //dayNightCycle->ApplyNightEffects(currentWave); // 밤이 되었을 때 적용할 효과
    //dayNightCycle->RemoveNightEffects(currentWave); // 낮이 되었을 때 제거할 효과
    dayNightCycle->SwitchBackGround(GameTime::GetInstance().GetDeltaTime(), (currentWave) % 4);
    
	
}
