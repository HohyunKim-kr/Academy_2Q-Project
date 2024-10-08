#include "Enemy.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "MainPineApple.h"


void Enemy::Init()
{
    // SpriteRenderer 컴포넌트 생성 및 설정
    
    // move 컴포넌트 생성 및 설정
    //move = gameObject->GetComponent<Movement>();
	defaultSpeed = enemyData.moveSpeed;
}




void Enemy::Update(float delta)
{
    if (hitTime > 0.f) {
        hitTime -= delta;
        if (hitTime < 0.f) {
            enemyAnim->SetAnimation(defaultAnimationNumber);
        }
    }
}

void Enemy::Render(D2D1_MATRIX_3X2_F cameraMat)
{
}

void Enemy::WaveMove(float delta)
{
    // 이동 로직
    // sin 파동을 이용한 y 좌표 변동을 위한 변수

    elapsedTime += delta;

    // 현재 위치를 가져옴
    auto& position = gameObject->transform->pos.worldPosition;

    // y축을 sin 파동으로 변동
    
    //position.y += std::sin(elapsedTime * waveFrequency) * waveAmplitude * delta ;

    float tmp = std::sinf(elapsedTime * waveFrequency) * waveAmplitude;// *delta;
    //std::cout << tmp << std::endl;
    if (tmp < 0.f)
    {
        tmp *= -1.f;
    }
    position.y = tmp + tmpY;


    // 갱신된 위치를 적용
    // gameObject->transform->pos.worldPosition = position;  
}

void Enemy::Ondamage(int damage, BulletType bulletType, bool notReward)
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
    case BulletType::Comosus:
        resist = enemyData.resistComosus;
    }
    float hundred = 0.01f;
    enemyData.hp -= damage * (1 - resist * hundred);
    hitTime = 0.2f;
    enemyAnim->SetAnimation(4);
	if (enemyData.hp <= 0)
	{
        //gameObject->isActive = false;
        notify->isActive = false;
        //mainPineApple->acquireGold(enemyData.reward);
        //mainPineApple->monAcquireEXP(enemyData.expReward);

        if (notReward == false) {
            mainPineApple->acquireGold(enemyData.reward);
            mainPineApple->monAcquireEXP(enemyData.expReward);
        }
	    gameObject->GetComponent<FiniteStateMachine>()->SetState("Dead");
	}
}

void Enemy::OnSlow(float _slowRate, float _slowTime)
{   

	
	if (!isSlowed)
	{   
        enemyAnim->alpha = 0.7f;
		move->m_speed = defaultSpeed * (100 - _slowRate) * 0.01f;
        slowedRate = _slowRate;
		isSlowed = true;
		slowTimer = _slowTime;
    }
    else if (isSlowed && slowedRate >= _slowRate) {
        move->m_speed = defaultSpeed * (100 - _slowRate) * 0.01f;
		slowedRate = _slowRate;
		isSlowed = true;
        slowTimer = _slowTime;
    }

}


