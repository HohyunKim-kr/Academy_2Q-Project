#include "Hpbar.h"

// �⺻ ������
Hpbar::Hpbar()
    : maxHp(100.0f), currentHp(100.0f) {}

// ������: ü�� ���� �ִ� ü�°� �ʺ� �ʱ�ȭ
Hpbar::Hpbar(float initialHp, float width)
    : maxHp(initialHp), currentHp(initialHp) {}

// ü�� ������Ʈ: ������ ���ݿ� ���� ü�� ����
void Hpbar::takeDamage(float damage)
{
    currentHp -= damage;
    if (currentHp < 0)
        currentHp = 0; // ü���� 0���� ���� �� ����.
}

// ü�� ���� ���� ���¸� ��ȯ
float Hpbar::getCurrentHp() const
{
    return currentHp;
}

// ü�� ���� ���� �ʺ� ���
float Hpbar::getBarWidth() const
{
    return (currentHp / maxHp);
}
