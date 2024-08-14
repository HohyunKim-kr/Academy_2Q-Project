#pragma once
#include "../D2DEngine/Component.h"

class Scene;
class GameObject;
class DayNightCycle : public Component {
private:
    bool isNight;          // ��/�� ���¸� ��Ÿ���� ����

public:
    float sphereLocation[4] = {750.0f,400.0f,50.f,-300.f};
    //WaveSystem* waveSystem; // ���̺� �ý��ۿ� ���� ������
    Scene* scene;
    GameObject* m_Sun;
    GameObject* m_Moon;
    DayNightCycle() {};
    //DayNightCycle(WaveSystem* waveSystem);

    void Update(float deltaTime) override; // Update �Լ� �������̵�
    bool IsNight() const; // ���� ������ ������ ���θ� ��ȯ
    void ApplyNightEffects(int wave); // ���� �Ǿ��� �� ������ ȿ��
    void RemoveNightEffects(int wave); // ���� �Ǿ��� �� ������ ȿ��

    void SunMove(float deltaTime,int period);

    void SunReset();
    
};
