#pragma once
#include "../D2DEngine/Scene.h"

class Cutton;
class EndScene : public Scene
{
	Cutton* cuttons;
public:
	EndScene();
	~EndScene() override;

	// ���� Ȱ��ȭ �� �� ȣ�� 
	void Start() override;

	// ���� ��Ȱ��ȭ �� �� ȣ�� 
	void Clear() override;

	// ���� ������Ʈ ���� 
	void Update(float deltaTime) override;

	// ���� ������ ����
	void Render(D2DRenderer* _render) override;
};

