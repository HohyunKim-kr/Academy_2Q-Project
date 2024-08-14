#pragma once
#include "../D2DEngine/Component.h"
//#include "Popup.h"
#include <vector>

class Comosus : public Component
{
public:
    Comosus();

    void OnHarvest();  // ��Ȯ ��ư�� ������ �� ����Ǵ� �Լ�

private:
    void virtual Init() override;
    void virtual Update(float delta) override;
    //void PlayComosusAnimation();  // �ڸ𼭽� �ִϸ��̼� ���
    //void ShakeCamera(float duration);  // ī�޶� ��鸲
    //void RefundTurrets();  // ��� �ͷ� ȯ��
    //void ShowRewardPopup();  // ���� �˾�â ǥ��

    //SpriteAnimation comosusAnimation;  // �߰��� ��� ����
    //Animation comosusAnimation;
    //Camera* camera;
    //std::vector<Turret*> turrets;
    //MainPineApple* pineapple;
    bool comosusReward = false;
    int hp, maxHp;
    int currentExp, maxExp;
    int level;
    int gold;
    float pineappleYPosition;
};
