#pragma once
#include"../D2DEngine/Component.h"
#include <vector>

class Monster;

class WaveSystem : public Component
{
private:
    float waveTimer = 1.0f;   // Wave Ÿ�̸�
    int currentWave = 1;       // ���� ���� ���� wave
    static const int maxWave = 56; // �ִ� wave ��

public:
    virtual void Update(float deltaTime); // �� ������ ȣ��, wave Ÿ�̸� ������Ʈ
    void SpawnWave();              // ���ο� wave ����
    bool IsMapEmpty();             // �ʿ� ���Ͱ� �ϳ��� ������ Ȯ�� (���� �ʿ��� ��� ���)

private:
    void StartNextWave();          // ���� wave�� �Ѿ��
};

