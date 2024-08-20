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
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ImageUIRenderer.h"

WaveSystem::WaveSystem()
{
    
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
                    Vector2 spawnPosition = Vector2(-1500.0f, spawnY);
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
                    Vector2 spawnPosition = Vector2(1500.0f, spawnY);
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
    if (currentWave == curWave && waveTimer > 0.f) {

        if (elapsedTime > 0.66f)
        {
            elapsedTime = 0.66f;
        }
        float t1 = (0.66f - elapsedTime) / .66f;
        float t2 = (elapsedTime) / .66f;
        //std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
        Tuto->transform->pos.worldPosition.y = (t1 * 712.f) + (t2 * 370.f);
        if (elapsedTime > 0.66f)
        {
            return;
        }
    }
    
}

void WaveSystem::PullingTutorial(int curWave, GameObject* Tuto)
{
	if (currentWave == curWave && waveTimer > 0.f) {
		if (elapsedTime > 0.66f)
		{
			elapsedTime = 0.66f;
		}
		float t1 = (0.66f - elapsedTime) / .66f;
		float t2 = (elapsedTime) / .66f;
		//std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
		Tuto->transform->pos.worldPosition.y = (t1 * 370.f) + (t2 * 712.f);
		if (elapsedTime > 0.66f)
		{
			return;
		}
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
    if (currentWave < maxWave)
    {
        currentWave++;
        elapsedTime = 0.f;
        std::cout << "current wave: " << currentWave << std::endl;
        LoadWaveData();
        waveTimer = maxWaveTimer;  // 타이머 초기화 //현재 15초
        //SpawnWave();        // 새로운 wave 스폰
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
    // 웨이브 타이머 감소
    waveTimer -= deltaTime;
    elapsedTime += deltaTime;
    // 웨이브 타이머가 0 이하가 되었고, 적이 남아 있으면
    if (waveTimer <= 0.0f)
    {
        waveTimer += maxWaveTimer;
        StartNextWave();
    }
	
    PushingTutorial(1, tutorial1);
    PushingTutorial(2, tutorial2);
    PushingTutorial(3, tutorial3);
	PullingTutorial(2, tutorial1);
    PullingTutorial(3, tutorial2);
    PullingTutorial(4, tutorial3);
    Generator();

    // 태양 이동
    
    dayNightCycle->SunMove(GameTime::GetInstance().GetDeltaTime(), (currentWave - 1) % 4); //하드코딩 하긴했는데 +2는 시작할때 태양이 중간에 있으면 안되서 그런거임!
    dayNightCycle->MoonMove(GameTime::GetInstance().GetDeltaTime(), (currentWave) % 4); 
    //dayNightCycle->ApplyNightEffects(currentWave); // 밤이 되었을 때 적용할 효과
    //dayNightCycle->RemoveNightEffects(currentWave); // 낮이 되었을 때 제거할 효과
    dayNightCycle->SwitchBackGround(GameTime::GetInstance().GetDeltaTime(), (currentWave) % 4);
    
	
}
