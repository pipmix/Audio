#pragma once

#include "stdafx.h"
#include "Helpers.h"

using Microsoft::WRL::ComPtr;

static const int BASE_FREQ = 441;
static const int BUFFER_LENGTH = (44100 / BASE_FREQ);


extern ComPtr<IXAudio2> g_xAudio2;

class Osc {

public:

	Osc();
	void Create();


	void SetPitch(float pitch);
	void SetVolume(float vol);

private:

	WAVEFORMATEX m_waveFormat;
	XAUDIO2_BUFFER m_buffer;
	IXAudio2SourceVoice*		m_SourceVoice;
	BYTE* m_wavData;

	float m_pitch;
	float m_vol;

	short waveformBuffer[BUFFER_LENGTH];
};