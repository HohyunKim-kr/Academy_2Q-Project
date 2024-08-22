#include "BossAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"
#include"../D2DEngine/SoundManager.h"

void BossAttack::Enter()
{
	__super::Enter();
}

void BossAttack::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void BossAttack::Exit()
{
}

void BossAttack::Attack()
{
	__super::Attack();
	// ���� ����� �ٲٱ�
	SoundManager::GetInstance().PlaySoundW(L"Boss1Attack_Se", false);
}
