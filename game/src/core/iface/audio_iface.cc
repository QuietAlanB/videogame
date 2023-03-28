#include "core/iface/audio_iface.hh"

namespace core {

audio_iface::audio_iface(std::shared_ptr<core::audio> &audio) {
	this->audio = audio;
}

sound_id audio_iface::load_sound(std::filesystem::path const &path) {
	sound_id id = this->audio->snd_pool.load_sound(path);
	return id;
}

void audio_iface::play_sound(sound_id id) {
	this->audio->snd_pool.play_sound(id);
}

}