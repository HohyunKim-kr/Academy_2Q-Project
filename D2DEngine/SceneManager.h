// SceneManager.h
#pragma once
#include <unordered_map>
#include <string>
#include "Scene.h"

class SceneManager {
public:
    // �̱��� �ν��Ͻ��� �������� �Լ�
    static SceneManager& GetInstance();

    // ���� ����ϴ� �Լ�
    void RegisterScene(const std::string& name, Scene* scene);

    // Ư�� ������ ��ȯ�ϴ� �Լ�
    void ChangeScene(const std::string& name);

    void Release();

    // ���� Ȱ��ȭ�� ���� �������� �Լ�
    Scene* GetCurrentScene();

private:
    // ������ �� �Ҹ���
    SceneManager();
    ~SceneManager();

    // ���� �����ڿ� ���� ������ ����
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    std::unordered_map<std::string, Scene*> scenes;
    Scene* currentScene;
};
