#pragma once
#include "stdafx.h"
#include "Helpers.h"
#include "AudioTools.h"
#include "WavFile.h"

using Microsoft::WRL::ComPtr;

extern ComPtr<IXAudio2> g_xAudio2;
extern HWND ghWnd;



class Audio {

public:

							Audio();
							~Audio();
	void					Create();

	IXAudio2SourceVoice*	CreateSourceVoice();
	IXAudio2SubmixVoice*	CreateSubmixVoice();

	void Play(int num);
	void Stop(int num);


	void SetVolume(float v, int chan);
	void SetVolumeLR(float lc, float rc, int chan);
	void SetPitch(float freq, int chan);

	WAVEFORMATEX* GetWaveFormat(int i);



private:

	WavFile wf1;
	WavFile wf2;

	IXAudio2MasteringVoice*		m_masterVoice;
	IXAudio2SourceVoice*		m_SourceVoice;
	IXAudio2SubmixVoice*		m_submixVoice;

	XAUDIO2_SEND_DESCRIPTOR m_sendDesc;
	XAUDIO2_VOICE_SENDS m_voiceSends;

	IUnknown * m_XAPO1;

};