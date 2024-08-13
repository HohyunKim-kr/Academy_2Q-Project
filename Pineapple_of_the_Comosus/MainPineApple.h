#pragma once
#include "../D2DEngine/Component.h"
#include "Mpbar.h"

class BulletFactory;
class DataManager;
class MainPineApple : public Component
{
	int gold = 300; 
	int HP = 0;					// ���� ���ξ��� ü��. HP�� 0�̵Ǹ� ���ӿ���
	int maxHP = 100;			// ���ξ��� �ִ�ü�� 
	float currentEXP = 0;			// ���� ���ξ����� ����ġ
	float maxEXP = 100;			// ���ξ��� �ִ� ����ġ ��
	float solarGain = 1;			// ���� ���ξ����� �ʴ� ��Ȯ����ġ��
	int morningValue = 1;		// �� �ð��� ���� ��
	int nightValue = 0;			// �� �ð��� ���� ��
	float killMultiply = 1.0;	// ���� óġ�� ����ġ ����. currentExp = currentExp + ���� óġ exp * killMultiply��
	float offeringMultiply = 0.75; // �⺻ 0.75 ����,  75�� ä���� �� ��밡�� 
	float offeringValue = maxEXP * offeringMultiply;
	 
public:
	Mpbar* expbar;
	MainPineApple() { };
	virtual ~MainPineApple() { };

	void PrintIndex(int index);
	void acquireGold(int cost);		// ���� ����� ȹ���� ���
	void spendGold(int cost);		// �ͷ� ��ġ�� ����� ���
	void monAcquireEXP(float exp);	// ���� ����� ȹ���� ����ġ 
	void solarAcquireEXP(float deltaTime);
	void throwUiEXP(int currentEXP);
	void Harvest();					// ����ġ�� �Һ��ؼ� ���ξ��� ��Ȯ, ���ξ��� �ִ� ����ġ ����
	int GetPineAppleGold() { return gold; }	// ���� ���ξ��� ��差
	int GetCurrentExp() { return currentEXP; }			// ���� ���ξ��� ����ġ -> ���ξ��� ��Ȯ Ƚ��									

	float elapsedTime = 0.f;
	virtual void Update(float deltaTime);

	BulletFactory* bulletFactory;
};

