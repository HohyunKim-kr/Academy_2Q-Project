#include "BomberAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"

void BomberAttack::Enter()
{
	__super::Enter();
	Attack();
	fsm->SetState("Dead");
}

void BomberAttack::Update(float deltaTime)
{
	
	//__super::Update(deltaTime);
}

void BomberAttack::Exit()
{
}

void BomberAttack::Attack()
{
	__super::Attack();
	// ���� �ʱ�ȭ �� �ε�
	
}
