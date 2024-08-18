#include "HeavyAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"
#include"../D2DEngine/SoundManager.h"
void HeavyAttack::Enter()
{
	__super::Enter();
}

void HeavyAttack::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void HeavyAttack::Exit()
{
}

void HeavyAttack::Attack()
{
	__super::Attack();
	// ���� �ʱ�ȭ �� �ε�
	SoundManager::GetInstance().PlaySoundW(L"HeavySoldierAttack_Se", false);
}
