#include "GriffinAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"
void GriffinAttack::Enter()
{	
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void GriffinAttack::Update(float deltaTime)
{
	enemy->mainPineApple->pineAppleDamageHP(enemy->enemyData.attack);
	//std::cout << "�׸��� ������ : " << enemy->enemyData.attack << std::endl;
}

void GriffinAttack::Exit()
{
}
