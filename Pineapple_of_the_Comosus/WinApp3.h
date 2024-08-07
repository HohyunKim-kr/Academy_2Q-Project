#pragma once

#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/D2DRenderer.h"

class WinApp3 : public WinGameApp {
public:
    // ������
    WinApp3() {};

    // �Ҹ���
    virtual ~WinApp3() {};

    // ���ø����̼� �ʱ�ȭ
    void Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y) override;

    // ���ø����̼� ������Ʈ
    void Update(float deltaTime) override;

    // ���ø����̼� ������
    void Render(D2DRenderer* _render) override;

    // ���ø����̼� ���� ó��
    void Uninitialize() override;

private:
    // ���� ���� ����Ű�� ������
    Scene* currentScene;
};
