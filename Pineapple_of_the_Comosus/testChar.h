#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"

class SpriteRenderer;
class testChar : public Component
{
private:
	//Vector2 position; // ������ ��ġ
	float speed; // ������ �̵� �ӵ�
	Vector2 minBounds; // �̵� ���� �ּҰ�
	Vector2 maxBounds; // �̵� ���� �ִ밪

	//SpriteRenderer* spriteRenderer;  // �߰�: SpriteRenderer ������
public:

	testChar();  // �⺻ ������
	//void SetPosition(const Vector2& pos); // ��ġ ���� �޼���
	void virtual Init();
	void virtual Update(float delta);
	void virtual Render(D2D1_MATRIX_3X2_F cameraMat);

};

