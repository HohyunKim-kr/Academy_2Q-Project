#pragma once

// FMOD ��� ���� ����
#pragma comment (lib, "fmod_vc.lib")
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
        for (auto& sound : m_SoundMap) {
            sound.second->release();
        }
        m_System->close();
        m_System->release();
    }

public:
    static SoundManager& GetInstance() {
        static SoundManager instance;
        return instance;
    }
    
    bool LoadSound(const std::wstring& name, const std::wstring& filePath);
    void PlaySoundW(const std::wstring& name, bool loop = false);
    void StopSound(const std::wstring& name);
    void SetVolume(const std::wstring& name, float volume);
    void Update();
    void ReleaseSound(const std::wstring& name);
};

