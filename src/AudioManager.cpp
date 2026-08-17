#include "AudioManager.h"

#include <iostream>

AudioManager::~AudioManager()
{
    Destroy();
}

bool AudioManager::Init()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    Mix_AllocateChannels(32);

    std::cout << "AudioManager Initialized!" << std::endl;

    return true;
}

void AudioManager::Destroy()
{
    for (auto& sound : sounds)
    {
        Mix_FreeChunk(sound.second);
    }

    sounds.clear();

    for (auto& song : music)
    {
        Mix_FreeMusic(song.second);
    }

    music.clear();

    Mix_CloseAudio();
}

bool AudioManager::LoadSound(const std::string& name, const std::string& path)
{
    if (sounds.count(name))
        return true;

    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());

    if (!chunk)
    {
        std::cout << "Failed to load sound: "
                  << path
                  << "\n"
                  << Mix_GetError()
                  << std::endl;

        return false;
    }

    sounds[name] = chunk;

    std::cout << "Loaded Sound: " << name << std::endl;

    return true;
}

bool AudioManager::LoadMusic(const std::string& name, const std::string& path)
{
    if (music.count(name))
        return true;

    Mix_Music* song = Mix_LoadMUS(path.c_str());

    if (!song)
    {
        std::cout << "Failed to load music: "
                  << path
                  << "\n"
                  << Mix_GetError()
                  << std::endl;

        return false;
    }

    music[name] = song;

    std::cout << "Loaded Music: " << name << std::endl;

    return true;
}

void AudioManager::PlaySound(const std::string& name, int loops)
{
    auto it = sounds.find(name);

    if (it == sounds.end())
        return;

    Mix_PlayChannel(-1, it->second, loops);
}

void AudioManager::PlayMusic(const std::string& name, int loops)
{
    auto it = music.find(name);

    if (it == music.end())
        return;

    Mix_PlayMusic(it->second, loops);
}

void AudioManager::StopMusic()
{
    Mix_HaltMusic();
}

void AudioManager::PauseMusic()
{
    Mix_PauseMusic();
}

void AudioManager::ResumeMusic()
{
    Mix_ResumeMusic();
}

void AudioManager::SetSoundVolume(int volume)
{
    Mix_Volume(-1, volume);
}

void AudioManager::SetMusicVolume(int volume)
{
    Mix_VolumeMusic(volume);
}
