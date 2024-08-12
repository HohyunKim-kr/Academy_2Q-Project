#include "Enemy.h"
#include "DataManager.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "Bullet.h"

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

    WaveMove(delta);
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

void Enemy::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Enemy::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
    auto a = pOtherComponent->gameObject->GetComponent<Bullet>();
    if (a != nullptr) {
        gameObject->isActive = false;
    }
}

void Enemy::OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Enemy::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}
