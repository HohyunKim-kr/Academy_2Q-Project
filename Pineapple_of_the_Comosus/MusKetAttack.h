#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class Enemy;
class MainPineApple;
class MusKetAttack : public FSMState
{
public:
	MusKetAttack(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~MusKetAttack() {}

	Enemy* enemy;
	MainPineApple* mainPineApple;

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};


