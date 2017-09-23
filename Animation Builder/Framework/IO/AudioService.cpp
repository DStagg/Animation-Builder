#include "AudioService.h"

SFMLAudio::SFMLAudio()
{

};

void SFMLAudio::PlaySFX(std::string id)
{
	while (((int)_PlayingSFXs.size() > 0) && (_PlayingSFXs[0].getStatus() == sf::Sound::Stopped))
		_PlayingSFXs.erase(_PlayingSFXs.begin());

	_PlayingSFXs.push_back(sf::Sound(_SFXs[id]));
	_PlayingSFXs.back().play();
};

void SFMLAudio::PlayStream(std::string id)
{
	for (std::map<std::string, sf::Music>::iterator it = _Streams.begin(); it != _Streams.end(); it++)
		if (it->first == id)
		{
			it->second.play();
			break;
		}
};

void SFMLAudio::StopSFX(std::string id)
{
	for (std::vector<sf::Sound>::iterator it = _PlayingSFXs.begin(); it != _PlayingSFXs.end(); it++)
		if (it->getBuffer() == &_SFXs[id])
			it->stop();
};

void SFMLAudio::StopStream(std::string id)
{
	for (std::map<std::string, sf::Music>::iterator it = _Streams.begin(); it != _Streams.end(); it++)
		if (it->first == id)
		{
			it->second.stop();
			break;
		}
};

void SFMLAudio::PauseStream(std::string id)
{
	for (std::map<std::string, sf::Music>::iterator it = _Streams.begin(); it != _Streams.end(); it++)
		if (it->first == id)
			it->second.pause();
};

bool SFMLAudio::StreamPlaying(std::string id)
{
	for (std::map<std::string, sf::Music>::iterator it = _Streams.begin(); it != _Streams.end(); it++)
		if (it->first == id)
			return it->second.getStatus() == sf::Sound::Playing;
	return false;
};

bool SFMLAudio::StoreSFX(std::string id, std::string filename)
{
	return _SFXs[id].loadFromFile(filename);
};

bool SFMLAudio::StoreStream(std::string id, std::string filename)
{
	return _Streams[id].openFromFile(filename);
};