#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/Movement.h"
#include "DayNightCycle.h"
#include "DataManager.h"
#include <vector>

class Scene;
class Enemy;
class EnemyFactory;
class BulletFactory;
class MainPineApple;
class gamePopup;
class WaveSystem : public Component
{
private:
    const float maxWaveTimer = 15.f;
    float waveTimer = 3.f;   // Wave Ÿ�̸�
    int currentWave = 0;       // ���� ���� ���� wave
    //static const int maxWave = 56; // �ִ� wave ��
    
    float elapsedTime = 0.f;
	float elapsedTime2 = 0.f;
	float elapsedTime3 = 0.f;
    bool isHowManyPushed = false;
	bool isTutorial1Pushed = false;
	bool isElaspedTimeReset = false;


    std::vector<WaveEnemyData> leftEnemyDatas;
    std::vector<WaveEnemyData> rightEnemyDatas;
    
public:
    EnemyFactory* enemyFactory;  
    BulletFactory* bulletFactory;
    MainPineApple* mainPineApple;
    DayNightCycle* dayNightCycle;
    Vector2 rightPos; 
    Vector2 leftPos;
    GameObject* tutorial1;
    GameObject* tutorial2;
    GameObject* tutorial3;
    GameObject* tutorial4;
	GameObject* tutorial5;
	GameObject* tutorial6;
    GameObject* tutorial17;
    GameObject* tutorial53;
    GameObject* tutorial54;

	GameObject* tutorialBottom;
    GameObject* tutorial2Bottom;

	GameObject* howManyLeft[13];
	
    GameObject* comosusOn1;
    GameObject* comosusOn2;
    GameObject* comosusOn3;
    GameObject* comosusOn4;
    GameObject* comosusOn5;
    GameObject* comosusOn6;
    GameObject* comosusOn7;

    Scene* scene = nullptr;
    gamePopup* gameover;
    // Ǯ���� ���͸� �������� �޼���
    //Enemy* GetEnemyFromPool(); // SwordMan -> Enemy�� ����
    //void ReturnEnemyToPool(Enemy* enemy); // SwordMan -> Enemy�� ����
    //void InitializePool();         // Ǯ �ʱ�ȭ
    int getCurrentWave() { return currentWave; }
    virtual void Init();
    virtual void Update(float deltaTime); // �� ������ ȣ��, wave Ÿ�̸� ������Ʈ
    //void SpawnWave();              // ���ο� wave ����

    bool islastWave();
    void LoadWaveData();
    void Generator();
	void PushingTutorial(int curWave, GameObject* Tuto);
	void PullingTutorial(int curWave, GameObject* Tuto);

    void PushingBottomTutorial(int curWave);
    void PullingBottomTutorial(int curWave);

    void PushingBottom2Tutorial(int curWave);
    void PullingBottom2Tutorial(int curWave);

    void PushingHowManyDay(int curWave);
    void PullingHowManyDay(int curWave);

    bool IsFly(int id);

    //bool IsMapEmpty();             // �ʿ� ���Ͱ� �ϳ��� ������ Ȯ�� (���� �ʿ��� ��� ���)

    WaveSystem();
    virtual ~WaveSystem(); // �Ҹ��� ����
    void StartNextWave();          // ���� wave�� �Ѿ��

    float comosus7Timer = 0.f;
    float comosus7posY = 0.f;

private:

};

