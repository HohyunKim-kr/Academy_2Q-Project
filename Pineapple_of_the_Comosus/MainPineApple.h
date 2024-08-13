#pragma once
#include "../D2DEngine/Component.h"
#include <vector>
#include "Mpbar.h"
#include "HarvestButton.h"

class BulletFactory;
class MainPineApple : public Component
{
	int gold = 300;
	int LV = 1;
	int HP = 0;					// ���� ���ξ��� ü��. HP�� 0�̵Ǹ� ���ӿ���
	int maxHP = 100;			// ���ξ��� �ִ�ü�� 
	float currentEXP = 0;			// ���� ���ξ����� ����ġ
	float maxEXP = 100;			// ���ξ��� �ִ� ����ġ ��
	float solarGain = 50;			// ���� ���ξ����� �ʴ� ��Ȯ����ġ��
	int morningValue = 1;		// �� �ð��� ���� ��
	int nightValue = 0;			// �� �ð��� ���� ��
	float killMultiply = 1.0;	// ���� óġ�� ����ġ ����. currentExp = currentExp + ���� óġ exp * killMultiply��
	float offeringMultiply = 0.75; // �⺻ 0.75 ����,  75�� ä���� �� ��밡�� 
	float offeringValue = maxEXP * offeringMultiply;

	// ������ �ִ� ����ġ ���̺�
	std::vector<float> EXP_TABLE = {
		100, 200, 300, 400, 500,
		700, 900, 1100, 1300, 1500,
		1900, 2100, 2300, 2500, 2700,
		3100, 3500, 3900, 4300, 4700,
		5200, 5700, 6200, 6700, 7200,
		7200 // ���� 26 �̻��� ��� �ִ� ����ġ
	};

public:
	Mpbar* expbar;
	HarvestButton* harvest;
	MainPineApple() { };
	virtual ~MainPineApple() { };

	void PrintIndex(int index);
	void acquireGold(int cost);		// ���� ����� ȹ���� ���
	void spendGold(int cost);		// �ͷ� ��ġ�� ����� ���
	void monAcquireEXP(float exp);	// ���� ����� ȹ���� ����ġ 
	void solarAcquireEXP(float deltaTime);
	void throwUiEXP(int currentEXP);
	void UpdateMaxEXP();
	void Harvest();					// ����ġ�� �Һ��ؼ� ���ξ��� ��Ȯ, ���ξ��� �ִ� ����ġ ����
	int GetPineAppleGold() { return gold; }	// ���� ���ξ��� ��差
	int GetCurrentExp() { return currentEXP; }			// ���� ���ξ��� ����ġ -> ���ξ��� ��Ȯ Ƚ��									
	int GetPineAppleLV() { return LV; }
	float elapsedTime = 0.f;
	virtual void Update(float deltaTime);

	BulletFactory* bulletFactory;
};

