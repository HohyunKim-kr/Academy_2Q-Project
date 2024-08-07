#include "pch.h"
#include "SoundManager.h"

bool SoundManager::LoadSound(const std::wstring& baseName, const std::wstring& filePath) {
    // ������ �̸��� �����Ͽ� ������ ����� ���� �� �ε��� �� �ֵ��� ��
    static int soundCounter = 0;
    std::wstring uniqueName = baseName + std::to_wstring(soundCounter++);

    // ���� �ε�
    FMOD::Sound* sound = nullptr;
    FMOD_RESULT result = m_System->createSound(std::string(filePath.begin(), filePath.end()).c_str(), FMOD_DEFAULT, 0, &sound);
    if (result != FMOD_OK) {
        return false; // ���� �ε� ����
    }

    m_SoundMap[uniqueName] = sound;
    return true;
}

void SoundManager::PlaySoundW(const std::wstring& baseName, bool loop) {
    // baseName���� �����ϴ� ���带 ã��
    for (const auto& pair : m_SoundMap) {
        const std::wstring& name = pair.first;
        FMOD::Sound* sound = pair.second;

        // baseName���� �����ϴ� ���带 ã��
        if (name.find(baseName) == 0) {
            FMOD::Channel* channel = nullptr;
            m_System->playSound(sound, nullptr, false, &channel);
            if (loop) {
                channel->setMode(FMOD_LOOP_NORMAL);
            }
            m_ChannelMap[name] = channel;

            // ���� baseName�� ���� ù ��° ��ġ �׸� ����ϵ��� ����
            break;
        }
    }
}

void SoundManager::StopSound(const std::wstring& name) {
    auto it = m_ChannelMap.find(name);
    if (it != m_ChannelMap.end()) {
        it->second->stop();
    }
}

void SoundManager::SetVolume(const std::wstring& name, float volume) {
    auto it = m_ChannelMap.find(name);
    if (it != m_ChannelMap.end()) {
        it->second->setVolume(volume);
    }
}

void SoundManager::Update() {
    m_System->update();
}

void SoundManager::ReleaseSound(const std::wstring& name) {
    auto it = m_SoundMap.find(name);
    if (it != m_SoundMap.end()) {
        it->second->release();
        m_SoundMap.erase(it);
    }
}
