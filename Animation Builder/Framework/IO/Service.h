#ifndef SERVICE_H
#define SERVICE_H

#include <string>

class AudioService
{
public:

	virtual void PlaySFX(std::string id) = 0;
	virtual void StopSFX(std::string id) = 0;
	virtual void PlayStream(std::string id) = 0;
	virtual void PauseStream(std::string id) = 0;
	virtual void StopStream(std::string id) = 0;
	virtual bool StreamPlaying(std::string id) = 0;

	virtual bool StoreSFX(std::string id, std::string filename) = 0;
	virtual bool StoreStream(std::string id, std::string filename) = 0;
};

class NullAudio : public AudioService
{
public:

	NullAudio();

	void PlaySFX(std::string id);
	void StopSFX(std::string id);
	void PlayStream(std::string id);
	void PauseStream(std::string id);
	void StopStream(std::string id);
	bool StreamPlaying(std::string id);

	bool StoreSFX(std::string id, std::string filename);
	bool StoreStream(std::string id, std::string filename);
};

class Service
{
public:

	static void Init(AudioService* audio);

	static AudioService& GetAudio();
	
private:

	static AudioService* _AudioService;

};



#endif