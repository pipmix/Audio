#pragma once
#include "stdafx.h"
#include "WAVFileReader.h"
#include "Helpers.h"
#include "AudioTools.h"
#include "WavFile.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;

extern HWND ghWnd;

#define SAMPLERATE 44100
#define CHANNELS 2


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

	WAVEFORMATEX* GetWaveFormat(int i);

private:

	int m_sampleRate = 44100;
	int m_channels = 2;
	WavFile wf1;
	WavFile wf2;

	ComPtr<IXAudio2> m_xAudio2;
	IXAudio2MasteringVoice*		m_masterVoice;
	IXAudio2SourceVoice*		m_SourceVoice;
	IXAudio2SubmixVoice*		m_submixVoice;

	XAUDIO2_SEND_DESCRIPTOR m_sendDesc;
	XAUDIO2_VOICE_SENDS m_voiceSends;




	XAUDIO2_BUFFER*				m_audioBuffer;

	//ComPtr<IXAudio2SourceVoice> m_sourceVoice;
	IXAudio2SubmixVoice* subMix01;
	IXAudio2SubmixVoice* subMix02;

	XAUDIO2_BUFFER buffer1;
	IXAudio2SourceVoice* pSourceVoice;
	std::unique_ptr<uint8_t[]> waveFile;
	DirectX::WAVData waveData;



	XAUDIO2_BUFFER buffer2;
	IXAudio2SourceVoice* pSourceVoice2;
	std::unique_ptr<uint8_t[]> waveFile2;
	WAVData waveData2;

	XAUDIO2_SEND_DESCRIPTOR SFXSend;
	XAUDIO2_VOICE_SENDS SFXSendList;

	XAUDIO2_SEND_DESCRIPTOR SFXSend2;
	XAUDIO2_VOICE_SENDS SFXSendList2;

	float frequencyRatio;

};