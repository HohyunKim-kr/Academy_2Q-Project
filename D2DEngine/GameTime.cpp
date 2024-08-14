#include "pch.h"
#include "GameTime.h"
#include "cmath"
#include <iostream>
void GameTime::InitTime()
{
	QueryPerformanceFrequency(&frequency);	// ���� Ÿ�̸Ӱ� 1�� ���� ������ų�� �ִ� TickCount ��
	QueryPerformanceCounter(&prevCounter);  // �ʱ� TickCount ��
}

void GameTime::UpdateTime()
{
	QueryPerformanceCounter(&currentCounter); // ���� TickCount ��
	deltaTime = static_cast<float>(currentCounter.QuadPart - prevCounter.QuadPart) /
		static_cast<float>(frequency.QuadPart);  // ī�������̸� �ð� �ʴ����� ��ȯ

	prevCounter = currentCounter;
}

float GameTime::GetDeltaTime()
{
	return deltaTime;
}

float GameTime::GetFPS()
{
	return 1.0f / deltaTime;
}
