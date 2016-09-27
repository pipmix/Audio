#pragma once
#include "stdafx.h"
// : public CXAPOBase
class AudioEffect  {


public:


private:
	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	XAUDIO2_EFFECT_CHAIN chain;
	XAPO_BUFFER_FLAGS flags;
	WAVEFORMATEX waveFormat;
};