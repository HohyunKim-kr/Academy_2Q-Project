#include "DayNightCycle.h"
#include "../D2DEngine/Scene.h"
#include"../D2DEngine/SpriteRenderer.h"
#include "iostream"

DayNightCycle::DayNightCycle(WaveSystem* waveSystem)
    : isNight(false), waveSystem(waveSystem) {}

void DayNightCycle::Update(float deltaTime) {
    int curWave = waveSystem->getCurrentWave();

    std::cout << curWave;
    // 4�� ��� ���̺꿡�� ���� �ȴ�.
    if (curWave % 4 == 0 && curWave != 0) {
        if (!isNight) {
            isNight = true;
            ApplyNightEffects();
        }
    }
    else {
        if (isNight) {
            isNight = false;
            RemoveNightEffects();
        }
    }
}

bool DayNightCycle::IsNight() const {
    return isNight;
}

void DayNightCycle::ApplyNightEffects() {
    // �߰��ϱ�
    /*waveSystem->IncreaseEnemyAttackPower(0.25f);
    waveSystem->SetHarvestExperience(0.0f);*/
    std::cout << "��" << std::endl;
}

void DayNightCycle::RemoveNightEffects() {
    // �߰��ϱ�
    //waveSystem->IncreaseEnemyAttackPower(-0.25f);
    //waveSystem->SetHarvestExperience(1.0f); // �⺻ ��Ȯ ����ġ�� ������� �ǵ�����
}
