#include "BomberAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"
#include"../D2DEngine/SoundManager.h"
void BomberAttack::Enter()
{
	__super::Enter();
}

void BomberAttack::Update(float deltaTime)
{
	
	__super::Update(deltaTime);
}

void BomberAttack::Exit()
{
}

void BomberAttack::Attack()
{
	__super::Attack();
	// ���� �ʱ�ȭ �� �ε�
	SoundManager::GetInstance().PlaySoundW(L"BombCartExplosion_Se", false);
}
