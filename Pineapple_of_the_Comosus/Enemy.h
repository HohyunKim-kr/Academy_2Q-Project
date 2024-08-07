#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
enum class EliteType
{
	Normal,
	Hard,
	Fast,
	Hero
};
class SpriteRenderer;
class Enemy : public Component
{
protected:
	int resistArrow;
	int resistBullet;
	int resistBurst;
	int resistComosus;

	int hp;
	int moveSpeed;
	int attack;
	int attackRate;
	int range;
	
	EliteType eliteType;
	int reward;
	int expReward;

	//Vector2 position; // ������ ��ġ
	float speed; // ������ �̵� �ӵ�
	Vector2 minBounds; // �̵� ���� �ּҰ�
	Vector2 maxBounds; // �̵� ���� �ִ밪

	//SpriteRenderer* spriteRenderer;  // �߰�: SpriteRenderer ������

public:
	Enemy() = default;
	virtual ~Enemy() = default;

	void Init() override;
	void Update(float delta) override;
	void Render(D2D1_MATRIX_3X2_F cameraMat) override;

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

	void SetStat(int Hp, int MoveSpeed, int Attack, int AttackRate, int Range) {
		hp = Hp;
		moveSpeed = MoveSpeed;
		attack = Attack;
		attackRate = AttackRate;
		range = Range;
	}

	Enemy& GetEnemy() { return *this; }
};

