#pragma once
#include "Audio.h"

class App {

public:

	App();
	void Create();
	void Tick();
	void Play(int num);
	void Stop(int num);

	WAVEFORMATEX* GetWaveFormat(int i);

private:

	void Update();
	void Draw();


	Audio audio;



};