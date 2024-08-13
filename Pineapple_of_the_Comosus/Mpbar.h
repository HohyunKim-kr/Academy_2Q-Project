#pragma once
#include "../D2DEngine/Component.h"

class ImageUIRenderer;
class Mpbar : public Component
{
private:
	float maxMp;    // �ִ� MP
	float currentMp; // ���� MP
	float targetMp; // ��ǥ MP
	float lerpSpeed; // ���� ���� �ӵ�
public:
	ImageUIRenderer* ImageRender;
	// �⺻ ������ 
	Mpbar();

	// ������: ü�� ���� �ִ� ü�°� �ʺ� �ʱ�ȭ
	Mpbar(float initialHp, float width);

	// Mp ������Ʈ: ������ mp�� ���� ���ξ��� mp ���� 
	void takeMp(float manaPoint);

	// Mp ���� ���� ���¸� ��ȯ 
	float getCurrMp() const;

	// Mp ���� ���� �ʺ� ���
	float getBarWidth() const;

	// �ִ� Mp ��ȯ 
	float getMaxMp() { return maxMp; }

	void Update(float deltaTime);


};

