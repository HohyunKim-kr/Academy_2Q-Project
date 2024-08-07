// SceneManager.cpp
#include "pch.h"
#include "SceneManager.h"
#include <iostream>

// �̱��� �ν��Ͻ��� �������� �Լ�
SceneManager& SceneManager::GetInstance() {
    static SceneManager instance;
    return instance;
}

// ������
SceneManager::SceneManager() : currentScene(nullptr) {}

// �Ҹ���
SceneManager::~SceneManager() {
    for (auto& pair : scenes) {
        delete pair.second;
    }
}

// ���� ����ϴ� �Լ�
void SceneManager::RegisterScene(const std::string& name, Scene* scene) {
    scenes[name] = scene;
}

// Ư�� ������ ��ȯ�ϴ� �Լ�
void SceneManager::ChangeScene(const std::string& name) {
    if (currentScene) {
        currentScene->Clear(); // ���� ������ �ڿ� ����
    }

    auto it = scenes.find(name);
    if (it != scenes.end()) {
        currentScene = it->second;
        // �߰����� �ʱ�ȭ�� �ʿ��ϸ� ���⼭ ó��
        currentScene->Start(); // ���ο� ���� �ʱ�ȭ
    }
    else {
        std::cerr << "Scene " << name << " not found!" << std::endl;
    }
}

// ���� Ȱ��ȭ�� ���� �������� �Լ�
Scene* SceneManager::GetCurrentScene() {
    return currentScene;
}
