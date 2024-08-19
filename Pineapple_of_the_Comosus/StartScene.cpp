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
    bgSpr->LoadTexture(L"../Resource/main/titleBg.png");

    auto startButton = CreateGameObject<GameObject>();
    auto strtSpr = startButton->CreateComponent<Button>();
    startButton->transform->type = Type::Ui;
    startButton->transform->pos.rectposition = { {1100,180} ,{1440,470} };
    strtSpr->LoadTexture(L"../Resource/main/StartButton.png");
    //auto& curS = SceneManager::GetInstance();
    strtSpr->AddListener([&]() {SceneManager::GetInstance().SetChangeSceneFlag("GameScene"); });

    auto ruleButton = CreateGameObject<GameObject>();
    auto ruleSpr = ruleButton->CreateComponent<Button>();
    ruleButton->transform->type = Type::Ui;
    ruleButton->transform->pos.rectposition = { {1320,100} ,{1690,330} };
    ruleSpr->LoadTexture(L"../Resource/main/HowToPlay.png");
    //auto& curS = SceneManager::GetInstance();
    
    auto wireButton = CreateGameObject<GameObject>();
    auto wireSpr = wireButton->CreateComponent<Button>();
    wireButton->transform->type = Type::Ui;
    wireButton->transform->pos.rectposition = { {1040,500} ,{1780,1080} };
    wireSpr->LoadTexture(L"../Resource//main/Titilewire.png");
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
