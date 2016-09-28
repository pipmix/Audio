
#include "Osc.h"

Osc::Osc(){
	m_waveFormat = { 0 };
	m_buffer = { 0 };
}

void Osc::Create()
{
	HRESULT hr;
	
	m_waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	m_waveFormat.nChannels = 2;
	m_waveFormat.nSamplesPerSec = 44100;
	m_waveFormat.nAvgBytesPerSec = 264600;
	m_waveFormat.nBlockAlign = 6;
	m_waveFormat.wBitsPerSample = 24;
	m_waveFormat.cbSize = 0;

	hr = g_xAudio2->CreateSourceVoice(&m_SourceVoice, &m_waveFormat, 0, XAUDIO2_MAX_FREQ_RATIO);
	if (FAILED(hr)) Error(L"Audio Error", L"Osc voice creation");

	for (int sample = 0; sample < BUFFER_LENGTH; sample++)
		waveformBuffer[sample] =
		(short)(65535 * sample / BUFFER_LENGTH - 32768);
	// Submit the waveform buffer
	
	m_buffer.AudioBytes = 2 * BUFFER_LENGTH;
	m_buffer.pAudioData = (byte *)waveformBuffer;
	m_buffer.Flags = XAUDIO2_END_OF_STREAM;
	m_buffer.PlayBegin = 0;
	m_buffer.PlayLength = BUFFER_LENGTH;
	m_buffer.LoopBegin = 0;
	m_buffer.LoopLength = BUFFER_LENGTH;
	m_buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	hr = m_SourceVoice->SubmitSourceBuffer(&m_buffer);

	if (FAILED(hr))if (FAILED(hr)) Error(L"Audio Error", L"Osc source submit");
	m_SourceVoice->Start();


}

void Osc::SetPitch(float pitch)
{
	m_SourceVoice->SetFrequencyRatio(pitch / BASE_FREQ);
}

void Osc::SetVolume(float vol)
{
	m_SourceVoice->SetVolume(vol);
}
