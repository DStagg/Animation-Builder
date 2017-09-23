#ifndef AUDIOSERVICE_H
#define AUDIOSERVICE_H

#include "Service.h"
#include <map>
#include "SFML\Audio.hpp"

class SFMLAudio : public AudioService
{
public:

	SFMLAudio();

	void PlaySFX(std::string id);
	void PlayStream(std::string id);
	void StopSFX(std::string id);
	void StopStream(std::string id);
	void PauseStream(std::string id);
	bool StreamPlaying(std::string id);

	bool StoreSFX(std::string id, std::string filename);
	bool StoreStream(std::string id, std::string filename);

protected:

	std::vector<sf::Sound> _PlayingSFXs;
	std::map<std::string, sf::SoundBuffer> _SFXs;
	std::map<std::string, sf::Music> _Streams;
};

#endif