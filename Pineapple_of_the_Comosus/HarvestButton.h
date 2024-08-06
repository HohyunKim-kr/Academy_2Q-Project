#pragma once
#include "../D2DEngine/Component.h"

class Mpbar; // ����
class HarvestButton : public Component
{
private:
    float HarvestMp; // ��Ȯ�� �ʿ��� ����ġ
    float maxExperience; // �ִ� ����ġ
    bool isHarvestable; // ��Ȯ ���� ����

    // ��Ȯ ���ɱ��� ����
    void UpdateButtonOpacity(); // ��ư�� ���� ������Ʈ
public:
    HarvestButton();

    Mpbar* mp; // Mpbar ��ü�� ���� ������

    // ��Ȯ�ϱ� - ��ư Ŭ���� ����
    void Harvest();

    // ��ư ���� ������Ʈ
    void Update(float deltaTime);
};
