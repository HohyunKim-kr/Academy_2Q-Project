#pragma once
#include "WinApp3.h"
#include "StartScene.h"
#include "GameScene.h"
#include"../D2DEngine/SceneManager.h"

void WinApp3::Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y) {
    __super::Initialize(hInstance, nCmdShow, x, y);

    // �� �Ŵ����� ����Ͽ� �� ���
    SceneManager& sceneManager = SceneManager::GetInstance();

    auto startScene = new StartScene();
    auto gameScene = new GameScene();

    sceneManager.RegisterScene("StartScene", startScene);
    sceneManager.RegisterScene("GameScene", gameScene);

    // ���� ������ ��ȯ
    sceneManager.ChangeScene("StartScene");
}

void WinApp3::Update(float deltaTime) {
    __super::Update(deltaTime);

    // �� ������Ʈ ȣ�� (�� �Ŵ��� ���)
    SceneManager::GetInstance().GetCurrentScene()->Update(deltaTime);
}

void WinApp3::Render(D2DRenderer* _render) {
    __super::Render(_render);

    // �� ������ ȣ�� (�� �Ŵ��� ���)
    SceneManager::GetInstance().GetCurrentScene()->Render(_render);
}

void WinApp3::Uninitialize() {
    __super::Uninitialize();
    SceneManager::GetInstance().Release();
}

