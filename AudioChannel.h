#pragma once
#include "stdafx.h"
#include "Helpers.h"
using Microsoft::WRL::ComPtr;


extern ComPtr<IXAudio2> g_xAudio2;

class AudioChannel {

public:

	AudioChannel();
	~AudioChannel();
	void Create();
	void SetVol(float lc, float rc);
	void SetVol(float c);

	void SetToChannel(IXAudio2SourceVoice* srcVoice);
	IXAudio2SubmixVoice* GetChannel();

private:

	IXAudio2SubmixVoice*		m_submixVoice;
	XAUDIO2_SEND_DESCRIPTOR		m_sendDesc;
	XAUDIO2_VOICE_SENDS			m_voiceSends;
};