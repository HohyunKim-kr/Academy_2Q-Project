#pragma once
#include "../D2DEngine/Component.h"
class BulletFactory;
class MainPineApple : public Component
{
	int PineAppleGold = 300; 
	int HP = 0;					// ���� ���ξ��� ü��. HP�� 0�̵Ǹ� ���ӿ���
	int maxHP = 100;			// ���ξ��� �ִ�ü�� 
	int currentEXP = 0;			// ���� ���ξ����� ����ġ
	int maxEXP = 100;			// ���ξ��� �ִ� ����ġ ��
	int solarGain = 1;			// ���� ���ξ����� �ʴ� ��Ȯ����ġ��
	int morningValue = 1;		// �� �ð��� ���� ��
	int nightValue = 0;			// �� �ð��� ���� ��
	float killMultiply = 1.0;	// ���� óġ�� ����ġ ����. currentExp = currentExp + ���� óġ exp * killMultiply��
	float offeringMultiply = 0.75; // �⺻ 0.75 ����,  75�� ä���� �� ��밡�� 
	int offeringValue = maxEXP * offeringValue;
public:
	MainPineApple() { };
	virtual ~MainPineApple() { };

	void PrintIndex(int index);
	void acquireGold(int cost);		// ���� ����� ȹ���� ���
	void spendGold(int cost);		// �ͷ� ��ġ�� ����� ���
	void monAcquireEXP(int exp);	// ���� ����� ȹ���� ����ġ 
	void solarAcquireEXP(int exp);
	void Harvest(int exp);			// ����ġ�� �Һ��ؼ� ���ξ��� ��Ȯ, ���ξ��� �ִ� ����ġ ����
	int GetPineAppleGold() { return PineAppleGold; }	// ���� ���ξ��� ��差
	int GetCurrentExp() { return currentEXP; }			// ���� ���ξ��� ����ġ -> ���ξ��� ��Ȯ Ƚ��									

	float elapsedTime = 0.f;
	virtual void Update(float deltaTime);

	BulletFactory* bulletFactory;
};

