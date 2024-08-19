#pragma once
#include "../D2DEngine/Component.h"
#include <iostream>
class Scene;
class GameObject;
class SpriteRenderer;
class DayNightCycle : public Component {
private:
    bool isNight;          // ��/�� ���¸� ��Ÿ���� ����
    bool isMorningBgmLoaded = false;   // ��ħ ���尡 �ε�Ǿ����� ����
    bool isNightBgmLoaded = false;  // �� ���尡 �ε�Ǿ����� ����
    std::wstring currentPlayingBgm = L""; // ���� ��� ���� BGM�� ����

    float elapsedTime = 0.f;
    int prevPeriod = 0;
public:
    float sunLocation[4] = {750.0f,400.0f,50.f,-300.f};
    float moonLocation[4] = { 750.0f,400.0f,-750.f,-750.0f };
    //WaveSystem* waveSystem; // ���̺� �ý��ۿ� ���� ������
    Scene* scene;
    GameObject* m_Sun;
    GameObject* m_Moon;
    DayNightCycle() {};
    //DayNightCycle(WaveSystem* waveSystem);
    //backGround
    
    GameObject* cloudDay;
    GameObject* cloudNight;

    GameObject* backGroundDay;
    GameObject* backGroundNight;
    
    GameObject* Earth;
    
    GameObject* Mountain1Day;
    GameObject* Mountain2Day;
    GameObject* Mountain3Day;

    GameObject* Mountain1Night;
    GameObject* Mountain2Night;
    GameObject* Mountain3Night;



    void Update(float deltaTime) override; // Update �Լ� �������̵�
    bool IsNight() const; // ���� ������ ������ ���θ� ��ȯ
    void ApplyNightEffects(int wave); // ���� �Ǿ��� �� ������ ȿ��
    void RemoveNightEffects(int wave); // ���� �Ǿ��� �� ������ ȿ��

    void SunMove(float deltaTime,int period);

    void SunReset();

    void MoonMove(float deltaTime, int period);

    void MoonReset();
    
    void SwitchBackGround(float deltaTime, int period);

};
