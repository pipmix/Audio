#include "Audio.h"


Audio::Audio()
{
}

void Audio::Create() {


	HRESULT hr;


	if (FAILED(hr = XAudio2Create(&m_xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))	Error(L"Audio Error", L"xaudio2 device creation");
	if (FAILED(hr = m_xAudio2->CreateMasteringVoice(&m_masterVoice, m_sampleRate, m_channels)))			Error(L"Audio Error", L"mastering voice creation");


}



void Audio::tempwork() {



	//HRESULT hr;
	//if (FAILED(hr = m_xAudio2->CreateSourceVoice(&m_sourceVoice, (WAVEFORMATEX*)&wfx))) return hr;


	//SUBMIX

	XAUDIO2_VOICE_DETAILS voiceDetails01 = { 0 };
	XAUDIO2_VOICE_DETAILS voiceDetails02 = { 0 };
	m_xAudio2->CreateSubmixVoice(&subMix01, m_channels, m_sampleRate);//, 0, 0, 0, 0);
	m_xAudio2->CreateSubmixVoice(&subMix02, m_channels, m_sampleRate);//, 0, 0, 0, 0);


	SFXSend = { 0, subMix01 }; // This determines where audio will be sent
	SFXSendList = { 1, &SFXSend };

	SFXSend2 = { 0, subMix02 }; // This determines where audio will be sent
	SFXSendList2 = { 1, &SFXSend2 };
	//ENDSUBMIX
	XAUDIO2_FILTER_PARAMETERS xfp;
	xfp.Frequency = .1f;
	xfp.OneOverQ = 1.0f;
	xfp.Type = HighPassFilter;
	subMix01->SetFilterParameters(&xfp);


	XAUDIO2_FILTER_PARAMETERS xfp2;
	xfp2.Frequency = .1f;
	xfp2.OneOverQ = 1.0f;
	xfp2.Type = HighPassFilter;
	subMix02->SetFilterParameters(&xfp2);






	LoadWAVAudioFromFileEx(L"c:/sound2.wav", waveFile, waveData);
	m_xAudio2->CreateSourceVoice(&pSourceVoice, waveData.wfx);
	pSourceVoice->GetVoiceDetails(&voiceDetails01);

	LoadWAVAudioFromFileEx(L"c:/sound1.wav", waveFile2, waveData2);
	m_xAudio2->CreateSourceVoice(&pSourceVoice2, waveData2.wfx);
	pSourceVoice2->GetVoiceDetails(&voiceDetails02);


}

IXAudio2MasteringVoice* Audio::CreateMasterVoice() {
	HRESULT hr;
	if (FAILED(hr = m_xAudio2->CreateMasteringVoice(&m_masterVoice, m_sampleRate, m_channels)))Error(L"Audio Error", L"mastering voice creation");
}

IXAudio2SubmixVoice* Audio::CreateSubmixVoice() {

	IXAudio2SubmixVoice* submixVoice;
	m_xAudio2->CreateSubmixVoice(&submixVoice, 1, m_sampleRate, 0, 0, 0, 0);

	return submixVoice;

}

IXAudio2SourceVoice* Audio::CreateSourceVoice() {

	IXAudio2SourceVoice* sourceVoice;
	m_xAudio2->CreateSourceVoice(&pSourceVoice2, waveData2.wfx);
	return sourceVoice;
}



void Audio::Exit()
{

	//m_masterVoice->DestroyVoice();
}
