#pragma once
#include "../D2DEngine/Component.h"

class ImageUIRenderer;
class Mpbar : public Component
{
private:
	float maxMp; // �ִ� Mp
	float currentMp; // ���� Mp
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


};

