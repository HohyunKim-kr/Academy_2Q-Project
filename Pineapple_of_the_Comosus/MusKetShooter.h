#pragma once
#include "Enemy.h"

class BulletFactory;
class Scene;
class MusKetShooter : public Enemy
{
public:
    MusKetShooter() {};
	MusKetShooter(Scene* scene);

    virtual void Init() override;
    virtual void Update(float delta) override;
    virtual void Render(D2D1_MATRIX_3X2_F cameraMat) override;
    void Shoot();  // �Ѿ� �߻� �Լ�

    BulletFactory* bulletFactory;  // BulletFactory ������
private:
    float shootCooldown =1.f;           // �Ѿ� �߻� ������ ���� ��ٿ� Ÿ�̸�
    float timeSinceLastShot;       // ���������� �Ѿ��� �߻��� ������ �ð�
};

