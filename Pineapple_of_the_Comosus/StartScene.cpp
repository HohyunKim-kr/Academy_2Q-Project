#include "StartScene.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/SpriteRenderer.h"
#include <iostream>

StartScene::StartScene() {
    std::cout << "StartScene Constructor" << std::endl;
}

StartScene::~StartScene() {
    std::cout << "StartScene Destructor" << std::endl;
}

void StartScene::Start() {
    std::cout << "Entering StartScene" << std::endl;

    auto camera = CreateGameObject<GameObject>();
    auto pCam = camera->CreateComponent<Camera>();
    SetMainCamera(pCam);

    // �ʱ�ȭ �۾� (��: Ÿ��Ʋ ȭ��, ���� ��ư ��)
    // ��� �̹���
    auto bgObj = CreateGameObject<GameObject>();
    auto bgSpr = bgObj->CreateComponent<SpriteRenderer>();
    bgSpr->LoadTexture(L"../Resource/mainPage.png");
    std::cout << "image StartScene" << std::endl;
}

void StartScene::Clear() {
    __super::Clear();
    std::cout << "Exiting StartScene" << std::endl;
    // ���� �۾�
}

void StartScene::Update(float deltaTime) {
    __super::Update(deltaTime);
    // �� ������Ʈ ����
    if (InputManager::GetInstance().IsKeyDown('S')) {
        SceneManager::GetInstance().ChangeScene("GameScene");
    }
}

void StartScene::Render(D2DRenderer* _render) {
    // �� ������ ����
    __super::Render(_render);
    //std::cout << "Rendering StartScene" << std::endl;
}
