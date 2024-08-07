#pragma once
#include "../D2DEngine/Component.h"

class Mpbar; // ����
class ImageUIRenderer;
class HarvestButton : public Component
{
private:
    float HarvestMp; // ��Ȯ�� �ʿ��� ����ġ
    float maxExperience; // �ִ� ����ġ
    float harvestMinmumGage = 0.75f;

    // ��Ȯ ���ɱ��� ����
    void UpdateButtonOpacity(); // ��ư�� ���� ������Ʈ
public:

    ImageUIRenderer* ImageRender;
    HarvestButton();

    Mpbar* mp; // Mpbar ��ü�� ���� ������

    // ��Ȯ���� ���� üũ 
    bool HarvestAble();

    // ��ư ���� ������Ʈ
    void Update(float deltaTime);
};
