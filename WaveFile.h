#pragma once
#include "stdafx.h"

class WaveFile {
public:

	WaveFile();
	~WaveFile();

	const XAUDIO2_BUFFER* GetBuffer() const { return &m_buffer; }
	void Create();
	void Load(char* fileName);


private:
	WAVEFORMATEX m_waveFormat;
	XAUDIO2_BUFFER m_buffer;
	BYTE* m_wavData;



};