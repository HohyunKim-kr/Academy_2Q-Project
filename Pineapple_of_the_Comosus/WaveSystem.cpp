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
#include "../D2DEngine/SoundManager.h"
#include "gamePopup.h"

WaveSystem::WaveSystem()
{
    // ���� �ʱ�ȭ �� �ε�
    SoundManager::GetInstance().LoadSound(L"WaveStart_Se", L"../Media/6_Sound/scene3/Se/WaveStart_Se.wav");
    SoundManager::GetInstance().SetVolume(L"WaveStart_Se", 0.5f);
}

WaveSystem::~WaveSystem()
{
    delete enemyFactory; // EnemyFactory ��ü ����
    //m_Enemies.clear();
}

//void WaveSystem::SpawnWave()
//{
//    int numEnemiesToSpawn = 1; // �ϴ��� ���̺� 1���� ����
//
//    //m_Enemies.clear();  // ���� ���̺꿡�� ������ ���� ���� (�ʿ��� ���)
//
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<float> distY(-240.0f, -100.f);
//    std::uniform_real_distribution<float> flyDistY(300.f,400.0f);
//    std::bernoulli_distribution distSide(0.5); // 50% Ȯ���� true �Ǵ� false ����
//
//    for (int i = 0; i < numEnemiesToSpawn; ++i)
//    {
//        Enemy* newEnemy = enemyFactory->GetEnemyFromPool(30601);
//     
//        bool spawnOnLeft = distSide(gen); // 50% Ȯ���� ���� �Ǵ� �����ʿ��� ����
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
//        std::cout << "���� �����Ǿ����ϴ�" << std::endl;
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
                    // ����ȯ
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
                    // ����ȯ
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

void WaveSystem::PushingHowManyDay(int curWave)
{
    if (currentWave == curWave && waveTimer > 0.f) {

        if (elapsedTime > 0.66f)
        {
            elapsedTime = 0.66f;
        }
        float t1 = (0.66f - elapsedTime) / .66f;
        float t2 = (elapsedTime) / .66f;
        //std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
        howManyLeft[(curWave-1)/4]->transform->pos.worldPosition.y = (t1 * 712.f) + (t2 * 420.f);
        if (elapsedTime > 0.66f)
        {   
            isHowManyPushed = true;
            return;
        }
    }
	
}

void WaveSystem::PullingHowManyDay(int curWave)
{
    if (currentWave == curWave && waveTimer > 0.f) {
        if (elapsedTime2 > 0.66f)
        {
            elapsedTime2 = 0.66f;
        }
        float t1 = (0.66f - elapsedTime2) / .66f;
        float t2 = (elapsedTime2) / .66f;
        //std::cout << "t1 : " << t1 << ", t2 : " << t2 << std::endl;
        howManyLeft[(curWave-1)/4]->transform->pos.worldPosition.y = (t1 * 420.f) + (t2 * 712.f);
        if (elapsedTime2 > 0.66f)
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
    if (islastWave() == false)
    {
        // ���̺� ���� ȿ���� 
        SoundManager::GetInstance().PlaySoundW(L"WaveStart_Se", false);
        currentWave++;
        elapsedTime = 0.f;
		elapsedTime2 = 0.f;
		isHowManyPushed = false;
        std::cout << "current wave: " << currentWave << std::endl;
        LoadWaveData();
        waveTimer = maxWaveTimer;  // Ÿ�̸� �ʱ�ȭ //���� 15��
        //SpawnWave();        // ���ο� wave ����
    }
    // maxWave�� �������� ��� �߰����� ó�� �ʿ� (���� ���� �Ǵ� ���� ��)
}

void WaveSystem::Init()
{
    enemyFactory = new EnemyFactory(scene); // EnemyFactory ����
    enemyFactory->bulletFactory = bulletFactory;
    enemyFactory->mainPineApple = mainPineApple;
}

void WaveSystem::Update(float deltaTime)
{   
    if (islastWave())
    {
        GameTime::GetInstance().SetTimeScale(0.f);
        gameover->victoryUIon();
    }
   

    // ���̺� Ÿ�̸� ����
    waveTimer -= deltaTime;
    elapsedTime += deltaTime;
    // ���̺� Ÿ�̸Ӱ� 0 ���ϰ� �Ǿ���, ���� ���� ������
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
    if (!isHowManyPushed) {
        PushingHowManyDay(currentWave);
    }

    if (waveTimer <= 10.f) {
		elapsedTime2 += deltaTime;
        PullingHowManyDay(currentWave);
    } 
    
    Generator();

    // �¾� �̵�
    
    dayNightCycle->SunMove(GameTime::GetInstance().GetDeltaTime(), (currentWave - 1) % 4); //�ϵ��ڵ� �ϱ��ߴµ� +2�� �����Ҷ� �¾��� �߰��� ������ �ȵǼ� �׷�����!
    dayNightCycle->MoonMove(GameTime::GetInstance().GetDeltaTime(), (currentWave) % 4); 
    //dayNightCycle->ApplyNightEffects(currentWave); // ���� �Ǿ��� �� ������ ȿ��
    //dayNightCycle->RemoveNightEffects(currentWave); // ���� �Ǿ��� �� ������ ȿ��
    dayNightCycle->SwitchBackGround(GameTime::GetInstance().GetDeltaTime(), (currentWave) % 4);
    
	
}
