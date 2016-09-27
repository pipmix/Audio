#pragma once
#include "stdafx.h"
#include "Audio.h"
extern Audio gAudio;

class AudioChannel {

public:

	AudioChannel();
	void Create();
	void SetVol();

	void SetToChannel(IXAudio2SourceVoice* srcVoice);
	IXAudio2SubmixVoice* GetChannel();

private:

	IXAudio2SubmixVoice*		m_submixVoice;
	XAUDIO2_SEND_DESCRIPTOR m_sendDesc;
	XAUDIO2_VOICE_SENDS m_voiceSends;
};