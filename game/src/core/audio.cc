#include "core/audio.hh"

#include <iostream>
#include <thread>
#include <string>

#include "util/log.hh"

// tirimid: thread wrapper for `sound.play()` member function.
static void sound_play_thread(std::shared_ptr<core::sound> const &snd) {
	snd->play();
}

// tirimid: mathematically, we can determine the length of an audio buffer in
// milliseconds (l) given the sample rate (r), bytes per sample (b), and number
// of bytes in the audio buffer (n).
//
// see:
// |=> r = (n/b)/(l/1000)
// |=> r = n * 1/b * 1/(l/1000)
// |=> r = n * 1/b * 1000/l
// |=> r = 1000n/(bl)
// |=> 1/r = bl/(1000n)
// |=> 1000n/r = bl
// |=> 1000n/(rb) = l
static uint32_t wav_buf_len_ms(int r, SDL_AudioFormat fmt, uint32_t n) {
	// tirimid: first, determine the number of bytes per sample; then we can
	// simply return the value given by the above formula.
	uint32_t b;
	
	switch (fmt) {
	case AUDIO_S8:
	case AUDIO_U8:
		b = 1;
		break;
	case AUDIO_S16LSB:
	case AUDIO_S16MSB:
	case AUDIO_U16LSB:
	case AUDIO_U16MSB:
		b = 2;
		break;
	case AUDIO_S32LSB:
	case AUDIO_S32MSB:
	case AUDIO_F32LSB:
	case AUDIO_F32MSB:
		b = 4;
		break;
	default:
		// tirimid: improve this error message later.
		ERROR("unsupported SDL_AudioFormat");
	};

	return 1000 * n / (r * b);
}

namespace core {

sound::sound(std::filesystem::path const &path) {
	SDL_LoadWAV(path.string().c_str(), &wav_spec, &wav_buff, &wav_len);
}

sound::~sound() {
	SDL_FreeWAV(wav_buff);
}

void sound::play() const {
	SDL_AudioDeviceID dev_id = SDL_OpenAudioDevice(nullptr, 0, &wav_spec,
	                                               nullptr, 0);
	
	SDL_QueueAudio(dev_id, wav_buff, wav_len);
	SDL_PauseAudioDevice(dev_id, 0);
	SDL_Delay(wav_buf_len_ms(wav_spec.freq, wav_spec.format, wav_len));
	
	SDL_CloseAudioDevice(dev_id);
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
	std::thread(sound_play_thread, snd).detach();
}

}
