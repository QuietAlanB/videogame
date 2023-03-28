#include "core/iface/audio_iface.hh"

namespace core {

audio_iface::audio_iface(std::shared_ptr<core::audio> &audio) {
	this->audio = audio;
}

sound_id audio_iface::load_sound(std::filesystem::path const &path) {
	return audio->snd_pool.load_sound(path);
}

void audio_iface::play_sound(sound_id id) {
	audio->snd_pool.play_sound(id);
}

}
