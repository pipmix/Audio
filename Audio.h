#pragma once
#include "stdafx.h"
#include "WAVFileReader.h"
#include "Helpers.h"
#include "AudioTools.h"
#include "WavFile.h"

using Microsoft::WRL::ComPtr;

extern ComPtr<IXAudio2> g_xAudio2;
extern HWND ghWnd;

#define SAMPLERATE 44100
#define CHANNELS 2

const std::wstring gAudioDir = L"C:/Box/Box Sync/Data/Audio/";

class Audio {

public:

							Audio();
	void					Create();
	XAUDIO2_BUFFER*			CreateBuffer();
	IXAudio2SourceVoice*	CreateSourceVoice();
	IXAudio2SubmixVoice*	CreateSubmixVoice();
	IXAudio2MasteringVoice* CreateMasterVoice();

	void tempwork();

	void Play(int num);
	void Stop(int num);
	void Exit();

	void SetVolume(float v, int chan);

	WAVEFORMATEX* GetWaveFormat(int i);

private:

	int m_sampleRate = 44100;
	int m_channels = 2;
	WavFile wf1;
	WavFile wf2;

	
	IXAudio2MasteringVoice*		m_masterVoice;
	IXAudio2SourceVoice*		m_SourceVoice;
	IXAudio2SubmixVoice*		m_submixVoice;

	XAUDIO2_SEND_DESCRIPTOR m_sendDesc;
	XAUDIO2_VOICE_SENDS m_voiceSends;






	float frequencyRatio;

};