#include "Comosus.h"
#include "../D2DEngine/GameTime.h"
Comosus::Comosus()
{
    // �ʱ�ȭ
    //comosusAnimation = GetComponent<Animation>();
    //camera = GetComponent<Camera>();
    //turrets = GetComponents<Turret>();
    //pineapple = GetComponent<Pineapple>();
    //hp = 100;  // ���� �ʱⰪ
    //maxHp = 100;  // ���� �ʱⰪ
    //currentExp = 50;  // ���� �ʱⰪ
    //maxExp = 100;  // ���� �ʱⰪ
    //level = 1;  // ���� �ʱⰪ
    //gold = 1000;  // ���� �ʱⰪ
    //pineappleYPosition = pineapple->GetYPosition();
    // 
    // 
    // �ִϸ��̼� ���� �ε�
    //comosusAnimation.LoadAnimationAsset(L"../Resource/tentacle_animation.csv");  // ���� ��η� ����
    //comosusAnimation.SetAnimation(0, false, false);  // ù �ִϸ��̼� ����
}

void Comosus::Init()
{
    // ���⼭ �ڸ𼭽� �ִϸ��̼� �ʱ�ȭ
}

void Comosus::Update(float delta)
{
}


//void Comosus::OnHarvest()
//{
//    PlayComosusAnimation();
//    ShakeCamera(4.0f);
//
//    hp = maxHp;
//
//    if (currentExp == maxExp)
//    {
//        comosusReward = true;
//    }
//
//    // Exp ���� ó��
//    for (float elapsedTime = 0.0f; elapsedTime < 4.0f; elapsedTime += GetDeltaTime())
//    {
//        currentExp -= currentExp / 3 * GetDeltaTime();
//        if (currentExp <= 0)
//        {
//            currentExp = 0;
//            break;
//        }
//    }
//
//    level++;
//
//    // �ڸ𼭽� �ִϸ��̼� ���� �ͷ� ��ġ ��Ȱ��ȭ
//    for (auto turret : turrets)
//    {
//        turret->SetActive(false);
//    }
//
//    // ���ξ��� ���� �̵� �� ȭ�� ������ ����� �� ��������Ʈ ����
//    while (pineapple->GetYPosition() < ScreenHeight)
//    {
//        pineappleYPosition += 5.0f * GetDeltaTime();  // ���� �ӵ�
//        pineapple->SetYPosition(pineappleYPosition);
//    }
//
//    if (pineappleYPosition >= ScreenHeight)
//    {
//        pineapple->DeleteSprite();
//    }
//
//    // ��� �ͷ� ȯ�� �� ��� ����
//    RefundTurrets();
//
//    // ���� �˾�â ����
//    if (comosusReward)
//    {
//        ShowRewardPopup();
//    }
//}
//
//void Comosus::PlayComosusAnimation()
//{
//    comosusAnimation.Play();
//}
//
//void Comosus::ShakeCamera(float duration)
//{
//    camera->Shake(duration);
//}
//
//void Comosus::RefundTurrets()
//{
//    int refundAmount = 0;
//    for (auto turret : turrets)
//    {
//        refundAmount += turret->GetRefundAmount();
//        turret->Destroy();
//    }
//    gold += refundAmount;
//}
//
//void Comosus::ShowRewardPopup()
//{
//    auto popup = new Popup("RewardPopup");
//    popup->Show();
//    // �ΰ��� �ð� ����
//    GetGame()->Pause();
//}
