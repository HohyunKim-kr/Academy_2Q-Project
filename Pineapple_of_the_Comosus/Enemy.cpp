#include "Enemy.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "MainPineApple.h"


void Enemy::Init()
{
    // SpriteRenderer ������Ʈ ���� �� ����
    
    // move ������Ʈ ���� �� ����
    //move = gameObject->GetComponent<Movement>();
}




void Enemy::Update(float delta)
{
  //  // �̵� ����
  //// sin �ĵ��� �̿��� y ��ǥ ������ ���� ����

  //  elapsedTime += delta;

  //  // ���� ��ġ�� ������
  //  auto& position = gameObject->transform->pos.worldPosition;

  //  // y���� sin �ĵ����� ����
  //  float waveAmplitude = 20.f;  // �ĵ��� ���� (���Ʒ� �������� ũ��)
  //  float waveFrequency = 10.f;   // �ĵ��� �ֱ� (�������� �ӵ�) -> Ƣ��� �ӵ� 
  //  //position.y += std::sin(elapsedTime * waveFrequency) * waveAmplitude * delta ;

  //  float tmp = std::sinf(elapsedTime * waveFrequency) * waveAmplitude;// *delta;
  //  //std::cout << tmp << std::endl;
  //  if (tmp < 0.f)
  //  {
  //      tmp *= -1.f;
  //  }
  //  position.y = tmp + tmpY;


  //  // ���ŵ� ��ġ�� ����
  //  // gameObject->transform->pos.worldPosition = position;  

    //WaveMove(delta);
}

void Enemy::Render(D2D1_MATRIX_3X2_F cameraMat)
{
}

void Enemy::WaveMove(float delta)
{
    // �̵� ����
    // sin �ĵ��� �̿��� y ��ǥ ������ ���� ����

    elapsedTime += delta;

    // ���� ��ġ�� ������
    auto& position = gameObject->transform->pos.worldPosition;

    // y���� sin �ĵ����� ����
    float waveAmplitude = 20.f;  // �ĵ��� ���� (���Ʒ� �������� ũ��)
    float waveFrequency = 10.f;   // �ĵ��� �ֱ� (�������� �ӵ�) -> Ƣ��� �ӵ� 
    //position.y += std::sin(elapsedTime * waveFrequency) * waveAmplitude * delta ;

    float tmp = std::sinf(elapsedTime * waveFrequency) * waveAmplitude;// *delta;
    //std::cout << tmp << std::endl;
    if (tmp < 0.f)
    {
        tmp *= -1.f;
    }
    position.y = tmp + tmpY;


    // ���ŵ� ��ġ�� ����
    // gameObject->transform->pos.worldPosition = position;  
}

void Enemy::Ondamage(int damage, BulletType bulletType)
{   
    int resist = 0;
    switch (bulletType)
    {
    case BulletType::arrow:
        resist = enemyData.resistArrow;
        break;
    case BulletType::bullet:
        resist = enemyData.resistBullet;
        break;
    case BulletType::burst:
        resist = enemyData.resistBurst;
        break;
    }
    float hundred = 0.01f;
    enemyData.hp -= damage * (1 - resist * hundred);
	if (enemyData.hp <= 0)
	{
        gameObject->isActive = false;
        notify->isActive = false;
        //mainPineApple->acquireGold(enemyData.reward);
        //mainPineApple->monAcquireEXP(enemyData.expReward);
	    gameObject->GetComponent<FiniteStateMachine>()->SetState("Dead");
	}
}


