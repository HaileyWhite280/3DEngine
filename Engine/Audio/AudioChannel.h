#pragma once
#include <fmod.hpp>

namespace nc
{
	class AudioChannel
	{ public:
		AudioChannel() {}
		AudioChannel(FMOD::Channel* channel) : channel{ channel } {}

		bool isPlaying();
		void Stop();

		void SetPitch(float pitch);
		float getPitch();

		void SetVolume(float volume);
		float getVolume();

	private:
		FMOD::Channel* channel{ nullptr };
	};
}
