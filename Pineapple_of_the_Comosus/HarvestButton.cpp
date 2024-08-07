#include "HarvestButton.h"
#include "Mpbar.h"

HarvestButton::HarvestButton()
    : HarvestMp(0.0f), maxExperience(100.0f)
{
}


// ��Ȯ ���ɿ��� üũ function
bool HarvestButton::HarvestAble()
{
    if (mp->getCurrMp() >= mp->getMaxMp() * harvestMinmumGage)
    {
        return true;
    }
    return false;
}

void HarvestButton::UpdateButtonOpacity()
{
    // ��ư�� Opacity�� �����ϴ� ����
    // opacity ���� ������ 0 (������ ����)���� 1 (������ ������)����
    float opacity = HarvestAble() ? 1.0f : 0.0f; // ��Ȯ ���� ���ο� ���� opacity ����

    // ��ư�� UI ������Ʈ���� opacity ���� �����ϴ� �޼��� ȣ��
    // ��: buttonUI->SetOpacity(opacity); �Ǵ� buttonUI->opacity = opacity;
    // ��ư UI ������Ʈ�� ������ ���� �ٸ� �� �ֽ��ϴ�.
    // ���⼭ ��Ȯ ��ư ���� 
}

void HarvestButton::Update(float deltaTime)
{
    // ����ġ�� Ȯ���ϰ� ��Ȯ ���� ���θ� ����
    if (mp->getCurrMp() >= mp->getMaxMp() * harvestMinmumGage)
    {
        // ��ư�� ���� ������Ʈ -> ��Ȯ ��ư Ȱ��ȭ
        UpdateButtonOpacity();
    }
}
