#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Collider.h"
#include "DataManager.h"
#include "Bullet.h"
#include <cmath>

enum class EliteType
{
	Normal,
	Hard,
	Fast,
	Hero
};
class MainPineApple;
class BoxCollider;
class Movement;
class SpriteRenderer;

class Enemy : public Component
{
public:
	Enemy() = default;
	virtual ~Enemy() = default;
	EnemyData enemyData;

	//Vector2 position; // ������ ��ġ
	//float speed; // ������ �̵� �ӵ�
	Vector2 minBounds; // �̵� ���� �ּҰ�
	Vector2 maxBounds; // �̵� ���� �ִ밪

	//SpriteRenderer* spriteRenderer;  // �߰�: SpriteRenderer ������

	
	float elapsedTime = 0.0f;
	float tmpY = 0.0f;

	Movement* move;
	MainPineApple* mainPineApple;
	GameObject* notify;
	SpriteRenderer* AttackSprite;

	virtual void Init() override;
	virtual void Update(float delta) override;
	virtual void Render(D2D1_MATRIX_3X2_F cameraMat) override;

	Enemy& GetEnemy() { return *this; }

	void WaveMove(float delta);

	void Ondamage(int damage, BulletType bulletType);

};

