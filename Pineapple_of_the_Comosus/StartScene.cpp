#include "StartScene.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include "../D2DEngine/SoundManager.h"
#include "../D2DEngine/Transform.h"
#include <iostream>
#include "../D2DEngine/Button.h"

StartScene::StartScene() {
    std::cout << "StartScene Constructor" << std::endl;
}

StartScene::~StartScene() {
    std::cout << "StartScene Destructor" << std::endl;
}

void StartScene::Start() {
    std::cout << "Entering StartScene" << std::endl;

    // ���� �ʱ�ȭ �� �ε�
    SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/hello.mp3");
    SoundManager::GetInstance().SetVolume(L"backgroundMusic", 0.5f);
    SoundManager::GetInstance().PlaySoundW(L"backgroundMusic", true);

    auto camera = CreateGameObject<GameObject>();
    auto pCam = camera->CreateComponent<Camera>();
    SetMainCamera(pCam);

    // �ʱ�ȭ �۾� (��: Ÿ��Ʋ ȭ��, ���� ��ư ��)
    // ��� �̹���
    std::cout << "image StartScene" << std::endl;

    auto bgObj = CreateGameObject<GameObject>();
    auto bgSpr = bgObj->CreateComponent<SpriteRenderer>();
    bgObj->transform->type = Type::Ui;
    bgSpr->LoadTexture(L"../Resource/mainPage.png");

    auto startButton = CreateGameObject<GameObject>();
    auto strtSpr = startButton->CreateComponent<Button>();
    startButton->transform->type = Type::Ui;
    startButton->transform->pos.rectposition = { {1490,800} ,{1890,900} };
    strtSpr->LoadTexture(L"../Resource/gameStart.png");
    //auto& curS = SceneManager::GetInstance();
    strtSpr->AddListener([&]() {SceneManager::GetInstance().SetChangeSceneFlag("GameScene"); });

    auto ruleButton = CreateGameObject<GameObject>();
    auto ruleSpr = ruleButton->CreateComponent<Button>();
    ruleButton->transform->type = Type::Ui;
    ruleButton->transform->pos.rectposition = { {1490,650} ,{1890,750} };
    ruleSpr->LoadTexture(L"../Resource/ruleButton.png");
    //auto& curS = SceneManager::GetInstance();
    
    auto exitButton = CreateGameObject<GameObject>();
    auto exitSpr = exitButton->CreateComponent<Button>();
    exitButton->transform->type = Type::Ui;
    exitButton->transform->pos.rectposition = { {1490,500} ,{1890,600} };
    exitSpr->LoadTexture(L"../Resource/exit.png");
    //auto& curS = SceneManager::GetInstance();
    //strtSpr->AddListener([]() {SceneManager::GetInstance().ChangeScene("GameScene"); });



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
