#pragma once
#include "../D2DEngine/Scene.h"
#include "Hpbar.h"
#include "Mpbar.h"
#include "WaveSystem.h"
#include "DayNightCycle.h"

class GameScene : public Scene {
private:
    WaveSystem* waveSystem; // WaveSystem ������
    DayNightCycle* nightSystem; // DayNightCycle ������
    //Mpbar* mpBarUi; // ����
    Hpbar* hpBarUi;
public:
    GameScene();
    ~GameScene() override;

    // ���� Ȱ��ȭ�� �� ȣ��
    void Start() override;

    // ���� ��Ȱ��ȭ�� �� ȣ��
    void Clear() override;

    // ���� ������Ʈ ����
    void Update(float deltaTime) override;

    // ���� ������ ����
    void Render(D2DRenderer* _render) override;
};
