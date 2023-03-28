#ifndef AUDIO_IFACE_HH__
#define AUDIO_IFACE_HH__

#include <memory>

#include "core/audio.hh"

namespace core {

class audio_iface {
private:
	std::shared_ptr<core::audio> audio;
public:
	audio_iface(std::shared_ptr<core::audio> &audio);

	sound_id load_sound(std::filesystem::path const &path);
	void play_sound(sound_id id);
};

}

#endif
