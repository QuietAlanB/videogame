#ifndef AUDIO_HH__
#define AUDIO_HH__

#include <filesystem>
#include <vector>
#include <memory>
#include <cstdint>

#include <SDL2/SDL.h>

namespace core {

typedef size_t sound_id;

class sound {
private:
	SDL_AudioSpec wav_spec;
	uint32_t wav_len;
	uint8_t *wav_buff;
public:
	sound(std::filesystem::path const &path);
	~sound();
	
	void play() const;
};

class sound_pool {
private:
	std::vector<std::shared_ptr<sound>> pool;
public:
	sound_id load_sound(std::filesystem::path const &path);
	std::shared_ptr<sound> get_sound(sound_id id);
	void play_sound(sound_id id) const;
};

class audio {
public:
	sound_pool snd_pool;
};

}

#endif
