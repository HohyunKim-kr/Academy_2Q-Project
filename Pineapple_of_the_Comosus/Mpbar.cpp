#include "Mpbar.h"

Mpbar::Mpbar()
	: maxMp(100.0f), currentMp(0.0f) {}

Mpbar::Mpbar(float initialHp, float width)
	: maxMp(initialHp), currentMp(initialHp) {}

void Mpbar::takeMp(float manaPoint)
{
	if (manaPoint < 0.0f)
		currentMp = 0.0f;
	else if (manaPoint > maxMp)
		currentMp = maxMp;
	else
		currentMp = manaPoint;
}

float Mpbar::getCurrMp() const
{
	return currentMp;
}

float Mpbar::getBarWidth() const
{
	return (currentMp / maxMp);
}

void Mpbar::Update(float deltaTime)
{
	// ���� ���� (Lerp)
	if (currentMp < targetMp)
		currentMp += lerpSpeed * deltaTime;
	else if (currentMp > targetMp)
		currentMp -= lerpSpeed * deltaTime;

	// ��ǥ ���� ���� �ʵ��� ����
	if (currentMp < 0.0f)
		currentMp = 0.0f;
	else if (currentMp > maxMp)
		currentMp = maxMp;
}
