#pragma once
#include "../D2DEngine/Scene.h"

class Cutton;
class StartScene : public Scene {
    Cutton* cuttons;
public:
    StartScene();
    ~StartScene() override;

    // ���� Ȱ��ȭ�� �� ȣ��
    void Start() override;

    // ���� ��Ȱ��ȭ�� �� ȣ��
    void Clear() override;

    // ���� ������Ʈ ����
    void Update(float deltaTime) override;

    // ���� ������ ����
    void Render(D2DRenderer* _render) override;
};
