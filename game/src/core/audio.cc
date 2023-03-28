#include "core/audio.hh"

#include <iostream>
#include <future>

namespace core {

// tirimid: async wrapper for `sound.play()` member function.
static void sound_play_async(std::shared_ptr<sound> const &snd) {
    snd->play();
}

sound::sound(std::filesystem::path const &path) {
    SDL_LoadWAV(path.string().c_str(), &wav_spec, &wav_buff, &wav_len);
    dev_id = SDL_OpenAudioDevice(nullptr, 0, &wav_spec, nullptr, 0);
}

sound::~sound() {
    //SDL_CloseAudioDevice(dev_id);
    //SDL_FreeWAV(wav_buff);
}

void sound::play() const {
    SDL_QueueAudio(dev_id, wav_buff, wav_len);
    SDL_PauseAudioDevice(dev_id, 0);

    // QuietAlanB: change the "3000" to the length of the sound
    SDL_Delay(3000);

    SDL_CloseAudioDevice(dev_id);
    SDL_FreeWAV(wav_buff);
}

sound_id sound_pool::load_sound(std::filesystem::path const &path) {
    std::shared_ptr<sound> snd = std::make_shared<sound>(path);
    pool.push_back(snd);
    return pool.size() - 1;
}

std::shared_ptr<sound> sound_pool::get_sound(sound_id id) {
    return pool[id];
}

void sound_pool::play_sound(sound_id id) const {
    std::shared_ptr<sound> const &snd = pool[id];

    auto handle = std::async(std::launch::async, sound_play_async, snd);
    handle.get();
}

}