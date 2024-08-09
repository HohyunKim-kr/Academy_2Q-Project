#include "EnemyMove.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/Movement.h"
void EnemyMove::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
	enemy->move->m_speed = enemy->moveSpeed;
}

void EnemyMove::Update(float deltaTime)
{	
	enemy->WaveMove(deltaTime);
	if (abs(fsm->gameObject->transform->pos.worldPosition.x) <
		0/*���ξ��� ��ǥ*/ + 300/*���ξ��� �ʺ��� ��*/ + enemy->range)
	{
		fsm->SetState("Attack");
	}
	else if(enemy->hp<0)
	{
		fsm->SetState("Dead");
	}
}

void EnemyMove::Exit()
{
	enemy->move->m_speed = 0.f;
}
