#pragma once

// FMOD ��� ���� ����
#pragma comment(lib, "fmod_vc.lib")
#include "fmod.hpp"
#include <map>
#include <string>

class SoundManager
{
private:
    FMOD::System* m_System = nullptr;

    std::map<std::wstring, FMOD::Sound*> m_SoundMap;   // ���� �̸��� FMOD::Sound ��ü�� �����ϴ� ��
    std::map<std::wstring, FMOD::Channel*> m_ChannelMap; // ���� �̸��� FMOD::Channel ��ü�� �����ϴ� ��

    SoundManager() {
        // FMOD �ý��� ��ü ����
        FMOD::System_Create(&m_System);
        m_System->init(512, FMOD_INIT_NORMAL, nullptr);
    }

    ~SoundManager() {
        // ���� ��ü ����
        for (auto& sound : m_SoundMap) {
            sound.second->release();
        }
        // FMOD �ý��� ����
        m_System->close();
        m_System->release();
    }

public:
    // �̱��� �ν��Ͻ� ��������
    static SoundManager& GetInstance() {
        static SoundManager instance;
        return instance;
    }

    // ���� �� �̵� ����
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
    SoundManager(SoundManager&&) = delete;
    SoundManager& operator=(SoundManager&&) = delete;

    // ���� �ε�
    bool LoadSound(const std::wstring& baseName, const std::wstring& filePath);

    // ���� ���
    void PlaySoundW(const std::wstring& baseName, bool loop = false);

    // ���� ����
    void StopSound(const std::wstring& name);

    // ���� ����
    void SetVolume(const std::wstring& name, float volume);

    // �ý��� ������Ʈ
    void Update();

    // ���� ����
    void ReleaseSound(const std::wstring& name);
};
