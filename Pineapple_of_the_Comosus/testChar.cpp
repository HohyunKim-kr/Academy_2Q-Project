#include "testChar.h"

testChar::testChar() : speed(100.0f), minBounds(Vector2(0.0f, 200.0f)), maxBounds(Vector2(960.0f, 200.0f))
{
}

//void testChar::SetPosition(const Vector2& pos)
//{
//	position = pos;
//}

void testChar::Init()
{
    // SpriteRenderer ������Ʈ ���� �� ����
}

void testChar::Update(float delta)
{
    //// �̵� ���� ���� : �̵� ������ ���� �ʵ��� ����
    //    position.x += speed * delta;
    //if (position.x < minBounds.x)
    //    position.x = minBounds.x;
    //if (position.x > maxBounds.x)
    //    position.x = maxBounds.x;
}

void testChar::Render(D2D1_MATRIX_3X2_F cameraMat)
{
}
