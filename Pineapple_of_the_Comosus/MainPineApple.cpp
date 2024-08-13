#include "MainPineApple.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include <iostream>
void MainPineApple::PrintIndex(int index)
{
	std::cout << index << std::endl;
}

void MainPineApple::acquireGold(int cost)
{
	gold += cost;
}

void MainPineApple::spendGold(int cost)
{
	if (gold >= cost)
	{
		gold -= cost;
		std::cout << "���� ���� ���ξ��� ��� : " << gold << std::endl;
	}
}

// ���Ϳ��� ȣ�� 
void MainPineApple::monAcquireEXP(float exp)
{
	// ���ͷκ��� ����ġ�� ȹ��
	currentEXP += exp * killMultiply;

	// currentEXP�� maxEXP�� �ʰ��ϸ� maxEXP���� ����
	if (currentEXP > maxEXP)
	{
		currentEXP = maxEXP;
	}
}

void MainPineApple::solarAcquireEXP(float deltaTime)
{
	// ���� ����ġ�� ������Ű����, �ִ� maxEXP������ ���
	if (currentEXP <= maxEXP)
	{
		currentEXP += solarGain * deltaTime;

		// currentEXP�� maxEXP�� �ʰ��ϸ� maxEXP���� ����
		if (currentEXP >= maxEXP)
		{
			currentEXP = maxEXP;
		}
	}
}

void MainPineApple::throwUiEXP(int currentEXP)
{
	// maxEXP�� 100�̰� currentEXP�� 0���� 100 ������ ��쿡�� ����
	if (maxEXP <= maxEXP && currentEXP >= 0 && currentEXP <= maxEXP)
	{
		//expbar->takeMp(currentEXP);
		expbar->ImageRender->slideBar = currentEXP / maxEXP;//expbar->getBarWidth();
	}
}

void MainPineApple::UpdateMaxEXP()
{
	maxEXP = EXP_TABLE[LV - 1];
}


void MainPineApple::Harvest()
{
	// LV���ǿ� ���� �ٲ�
	//harvest;
	// �ִ� ����ġ��� �ִ� lv
	// �ִ� ����ġ�� ������ ��� ������
	if (currentEXP == maxEXP)
	{
		UpdateMaxEXP(); // ���ο� �ִ� ����ġ ����
		std::cout << maxEXP << std::endl;
		//offeringValue = maxEXP * offeringMultiply; // ���ο� offeringValue ������Ʈ
		currentEXP = 0;
		LV++;
		// harvest UI ȣ�� -> harvest btn �ִϸ��̼� ȣ��
	}
	else {
		// �ִ� ����ġ�� �ƴմϴ�.
	}
}

void MainPineApple::Update(float deltaTime)
{
	// �ʴ� ��Ȯ��
	solarAcquireEXP(deltaTime);
	//std::cout << GetCurrentExp() << std::endl;
	//std::cout << offeringValue << std::endl;
	// UI HP�� ������Ʈ  

	// UI MP�� ������Ʈ 
	// GetCurrentExp() ���� ����ġ�� mpbar���� �ѱ�� �Լ� ȣ�� 
	throwUiEXP(GetCurrentExp());

	//elapsedTime += deltaTime;
	//float temp = std::sinf(elapsedTime * 10.f) * 30.f;
	////std::cout << temp << std::endl;
	//gameObject->transform->pos.worldPosition.y = temp;
	////gameObject->transform->m_RelativeRotation = elapsedTime * 30.f;
}
