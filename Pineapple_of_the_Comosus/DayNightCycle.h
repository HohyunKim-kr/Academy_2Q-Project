#pragma once
#include "../D2DEngine/Component.h"
#include "WaveSystem.h"

class Scene;
class DayNightCycle : public Component {
private:
    bool isNight;          // ��/�� ���¸� ��Ÿ���� ����

public:
    WaveSystem* waveSystem; // ���̺� �ý��ۿ� ���� ������
    Scene* scene;
    DayNightCycle() {};
    DayNightCycle(WaveSystem* waveSystem);

    void Update(float deltaTime) override; // Update �Լ� �������̵�
    bool IsNight() const; // ���� ������ ������ ���θ� ��ȯ
    void ApplyNightEffects(); // ���� �Ǿ��� �� ������ ȿ��
    void RemoveNightEffects(); // ���� �Ǿ��� �� ������ ȿ��
};
