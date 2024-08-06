#pragma once
#include "../D2DEngine/Component.h"

class ImageUIRenderer;
class Hpbar : public Component
{
private:
    float maxHp;          // �ִ� ü��
    float currentHp;      // ���� ü��

public:

    ImageUIRenderer* ImageRender;
    // �⺻ ������
    Hpbar();
    // ������: ü�� ���� �ִ� ü�°� �ʺ� �ʱ�ȭ
    Hpbar(float initialHp, float width);

    // ü�� ������Ʈ: ������ ���ݿ� ���� ü�� ����
    void takeDamage(float damage);

    // ü�� ���� ���� ���¸� ��ȯ
    float getCurrentHp() const;

    // ü�� ���� ���� �ʺ� ���
    float getBarWidth() const;

};
