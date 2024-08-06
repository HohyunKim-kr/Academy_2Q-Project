#pragma once
#include "../D2DEngine/WinGameApp.h"
#include "WaveSystem.h"
class Scene;
class WinApp2 : public WinGameApp
{
private:
	WaveSystem waveSystem; // WaveSystem �ν��Ͻ� �߰�
public:
	Scene* scene;
	float soundVolume;  // ���� ���� ������ ���� �߰�
	//  virtual �� ����ص� ������
	// override�� keyword�� ����ϹǷν� �����Լ� "������" ��°��� Ȯ�����Ѵ�.
	// �θ� Ŭ������ �Լ��� virtual �� �ƴϸ� ������ ����.
	virtual void Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y);

	//virtual void Run();

	virtual void Update(float deltaTime);

	virtual void Render(D2DRenderer* _render);

	virtual void Uninitialize();
};

