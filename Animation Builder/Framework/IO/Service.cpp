#include "Service.h"

NullAudio::NullAudio() {};
void NullAudio::PlaySFX(std::string id) {};
void NullAudio::StopSFX(std::string id) {};
void NullAudio::PlayStream(std::string id) {};
void NullAudio::PauseStream(std::string id) {};
void NullAudio::StopStream(std::string id) {};
bool NullAudio::StreamPlaying(std::string id) { return false; };
bool NullAudio::StoreSFX(std::string id, std::string filename) { return false; };
bool NullAudio::StoreStream(std::string id, std::string filename) { return false;  };

/////////////////////////////////////////

AudioService* Service::_AudioService = 0;

void Service::Init(AudioService* audio)
{
	_AudioService = audio;
};

AudioService& Service::GetAudio()
{
	if (_AudioService == 0)
		_AudioService = new NullAudio();
	return *_AudioService;
};

