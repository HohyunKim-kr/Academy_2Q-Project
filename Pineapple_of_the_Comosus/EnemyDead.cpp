#include "EnemyDead.h"
#include "Enemy.h"
#include "MainPineApple.h"
#include "GamePlayManager.h"
#include "../D2DEngine/GameObject.h"

void EnemyDead::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void EnemyDead::Update(float deltaTime)
{
	//�״� �ִϸ��̼� ���� ��
}

void EnemyDead::Exit()
{
}
