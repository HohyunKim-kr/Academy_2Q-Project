#include "StartScene.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/InputManager.h"
#include <iostream>

StartScene::StartScene() {
    std::cout << "StartScene Constructor" << std::endl;
}

StartScene::~StartScene() {
    std::cout << "StartScene Destructor" << std::endl;
}

void StartScene::Start() {
    std::cout << "Entering StartScene" << std::endl;
    // �ʱ�ȭ �۾� (��: Ÿ��Ʋ ȭ��, ���� ��ư ��)
}

void StartScene::Clear() {
    std::cout << "Exiting StartScene" << std::endl;
    // ���� �۾�
}

void StartScene::Update(float deltaTime) {
    // �� ������Ʈ ����
    if (InputManager::GetInstance().IsKeyDown('1')) {
        SceneManager::GetInstance().ChangeScene("GameScene");
    }
}

void StartScene::Render(D2DRenderer* _render) {
    // �� ������ ����
    std::cout << "Rendering StartScene" << std::endl;
}
