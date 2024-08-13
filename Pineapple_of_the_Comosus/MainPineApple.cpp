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
	currentEXP = exp * killMultiply;
}

void MainPineApple::solarAcquireEXP(float deltaTime)
{
	currentEXP += solarGain * deltaTime;


	//expbar->takeMp(10.f);
	//expbar->ImageRender->slideBar = expbar->getBarWidth();
	//std::cout << expbar->ImageRender->m_DstRect.right << std::endl;
	//std::cout << expbar->getBarWidth() << std::endl;

}

void MainPineApple::throwUiEXP(int currentEXP)
{
	// maxEXP�� 100�̰� currentEXP�� 0���� 100 ������ ��쿡�� ����
	if (maxEXP <= 100 && currentEXP >= 0 && currentEXP <= 100)
	{
		expbar->takeMp(currentEXP);
		expbar->ImageRender->slideBar = expbar->getBarWidth();
	}
}


void MainPineApple::Harvest()
{
	// harvest UI ȣ��
}

void MainPineApple::Update(float deltaTime)
{
	// �ʴ� ��Ȯ��
	solarAcquireEXP(deltaTime);
	std::cout << GetCurrentExp() << std::endl;
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
