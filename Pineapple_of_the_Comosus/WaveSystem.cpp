#include "WaveSystem.h"
#include <iostream> 

void WaveSystem::Update(float deltaTime)
{
    // ���Ͱ� �ʿ� �����ִ��� Ȯ���ϴ� �κ��� RemoveMonster�� �ƴ� �ٸ� �ý��ۿ��� ó��
    waveTimer -= deltaTime;  // deltaTime ��ŭ waveTimer ����
    if (waveTimer <= 0.0f)
    {
        StartNextWave();
    }
}

// SpawnWave �Լ�: ���� wave�� �ش��ϴ� ���͸� ����.
void WaveSystem::SpawnWave()
{
    int numMonstersToSpawn = currentWave; // ���� ���̺� ��ȣ�� ���� ���� �� ����

    for (int i = 0; i < numMonstersToSpawn; ++i)
    {
        // ���� ���� ����
        std::cout << "���Ͱ� �����Ǿ����ϴ�" << std::endl;
        // ���� ���� ���� �ڵ� ���߿� �ϱ�
    }
}

// StartNextWave �Լ�: wave�� �����Ű�� Ÿ�̸Ӹ� �ʱ�ȭ
void WaveSystem::StartNextWave()
{
    if (currentWave < maxWave)
    {
        currentWave++;
        waveTimer = 1.0f;  // Ÿ�̸� �ʱ�ȭ
        SpawnWave();        // ���ο� wave ����
    }
    // maxWave�� �������� ��� �߰����� ó�� �ʿ� (���� ���� �Ǵ� ���� ��)
}

// IsMapEmpty �Լ�: �ʿ� ���Ͱ� �ϳ��� ������ Ȯ��
bool WaveSystem::IsMapEmpty()
{
    // �ʿ��� ���Ͱ� �����ִ��� Ȯ���ϴ� ���� (�ʿ� �� ���)
    return false;  // �⺻������ false ��ȯ
}
