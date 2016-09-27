#include "stdafx.h"
#include "AudioChannel.h"

AudioChannel::AudioChannel(){

}

void AudioChannel::Create(){
	HRESULT hr;

	hr = g_xAudio2->CreateSubmixVoice(&m_submixVoice, CHANNELS, SAMPLERATE);
	if (FAILED(hr)) Error(L"Audio Error", L"Submix voice creation");

	m_sendDesc = { 0, m_submixVoice };
	m_voiceSends = { 1, &m_sendDesc };

}

void AudioChannel::SetToChannel(IXAudio2SourceVoice * srcVoice)
{
	//m_SourceVoice->SetOutputVoices(&m_voiceSends);
}

IXAudio2SubmixVoice * AudioChannel::GetChannel()
{
	return nullptr;
}
