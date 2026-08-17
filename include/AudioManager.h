#pragma once


#include <string>
#include <unordered_map>
#include <SDL_mixer.h>


class AudioManager{

public:


    AudioManager() = default;
    ~AudioManager();

    bool Init();
    void Destroy();

    bool LoadSound(const std::string& name, const std::string& path);

    bool LoadMusic(const std::string& name, const std::string& path);

    void PlaySound(const std::string& name, int loops = 0);
    void PlayMusic(const std::string& name, int loops = -1);

    void StopMusic();
    void PauseMusic();
    void ResumeMusic();


    void SetSoundVolume(int volume);
    void SetMusicVolume(int volume);

private:


    std::unordered_map<std::string, Mix_Chunk*> sounds;
    std::unordered_map<std::string, Mix_Music*> music;


};
