#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include <cmath>

enum class EliteType
{
	Normal,
	Hard,
	Fast,
	Hero
};

class BoxCollider;
class Movement;
class SpriteRenderer;
class Enemy : public Component
{
public:
	int resistArrow;
	int resistBullet;
	int resistBurst;
	int resistComosus;

	int hp;
	float moveSpeed; // ������ �̵� �ӵ�
	int attack;
	float attackRate;
	int range;

	EliteType eliteType;
	int reward;
	int expReward;

	//Vector2 position; // ������ ��ġ
	//float speed; // ������ �̵� �ӵ�
	Vector2 minBounds; // �̵� ���� �ּҰ�
	Vector2 maxBounds; // �̵� ���� �ִ밪

	//SpriteRenderer* spriteRenderer;  // �߰�: SpriteRenderer ������

	
	float elapsedTime = 0.0f;
	float tmpY = 0.0f;

	Enemy() = default;
	virtual ~Enemy() = default;

	Movement* move;
	BoxCollider* pBoxcollider;

	virtual void Init() override;
	virtual void Update(float delta) override;
	virtual void Render(D2D1_MATRIX_3X2_F cameraMat) override;

	void SetReward(int Reward, int ExpReward) {
		reward = Reward;
		expReward = ExpReward;
	}

	void SetResist(int ResistArrow, int ResistBullet, int ResistBurst, int ResistComosus) {
		resistArrow = ResistArrow;
		resistBullet = ResistBullet;
		resistBurst = ResistBurst;
		resistComosus = ResistComosus;
	}

	void SetStat(int Hp, float MoveSpeed, int Attack, float AttackRate, int Range) {
		hp = Hp;
		moveSpeed = MoveSpeed;
		attack = Attack;
		attackRate = AttackRate;
		range = Range;
	}

	Enemy& GetEnemy() { return *this; }

	void WaveMove(float delta);
};

