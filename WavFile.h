#pragma once
#include "stdafx.h"
#include "AudioTools.h"

class WavFile {
public:

	WavFile();
	~WavFile();

	const XAUDIO2_BUFFER*	GetBuffer() const { return &m_buffer; }
	WAVEFORMATEX*		GetWaveFormat()  { return &m_waveFormat; }
	void Create();
	void Load(TCHAR* fileName);


private:
	WAVEFORMATEXTENSIBLE m_wfx;
	WAVEFORMATEX m_waveFormat;
	XAUDIO2_BUFFER m_buffer;
	BYTE* m_wavData;

	XAUDIO2_VOICE_DETAILS m_voiceDetails;
	XAUDIO2_VOICE_STATE m_voiceState;
};