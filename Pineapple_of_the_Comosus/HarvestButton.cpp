#include "HarvestButton.h"
#include "Mpbar.h"

HarvestButton::HarvestButton()
    : HarvestMp(0.0f), maxExperience(100.0f), isHarvestable(false)
{
}

void HarvestButton::Harvest()
{
    if (isHarvestable)
    {
        // ��Ȯ ���� ����
    }
}

void HarvestButton::UpdateButtonOpacity()
{
    // ��ư�� Opacity�� �����ϴ� ����
    // opacity ���� ������ 0 (������ ����)���� 1 (������ ������)����
    float opacity = isHarvestable ? 1.0f : 0.0f; // ��Ȯ ���� ���ο� ���� opacity ����

    // ��ư�� UI ������Ʈ���� opacity ���� �����ϴ� �޼��� ȣ��
    // ��: buttonUI->SetOpacity(opacity); �Ǵ� buttonUI->opacity = opacity;
    // ��ư UI ������Ʈ�� ������ ���� �ٸ� �� �ֽ��ϴ�.
}

void HarvestButton::Update(float deltaTime)
{
    // ����ġ�� Ȯ���ϰ� ��Ȯ ���� ���θ� ����
    if (mp)
    {
        float currentExperience = mp->getCurrMp(); // Mpbar�� ���� ����ġ�� �������� �Լ�
        isHarvestable = (currentExperience >= maxExperience * 0.75f);

        // ��ư�� ���� ������Ʈ
        UpdateButtonOpacity();
    }
}
