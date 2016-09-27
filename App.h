#pragma once
#include "Audio.h"

class App {

public:

	App();
	void Create();
	void Tick();


private:

	void Update();
	void Draw();


	Audio audio;

};