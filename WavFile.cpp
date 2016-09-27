#include "stdafx.h"
#include "WavFile.h"

WavFile::WavFile(){
	m_waveFormat = { 0 };
	m_buffer = { 0 };
	m_wavData = nullptr;

	m_voiceDetails = { 0 };
	m_voiceState = { 0 };

	m_wfx = { 0 };
}

WavFile::~WavFile() {
	delete[] m_wavData;
	m_wavData = nullptr;

}

void WavFile::Create()
{







}
void WavFile::Load(TCHAR* fileName) {


	//_TEXT("c:/s2.wav");


	HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);


	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);



	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &m_waveFormat, dwChunkSize, dwChunkPosition);
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	BYTE * pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);
	m_buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	m_buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	m_buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
	/*
	HRESULT hr;
	hr = m_xAudio2->CreateSourceVoice(&m_SourceVoice, (WAVEFORMATEX*)&m_waveFormat);
	if (FAILED(hr))Error(L"Audio Error", L"Create Source Voice");

	hr = m_SourceVoice->SubmitSourceBuffer(&buffer);
	if (FAILED(hr))Error(L"Audio Error", L"Submit Source Voice");

	hr = m_SourceVoice->Start(0);
	if (FAILED(hr))Error(L"Audio Error", L"Source voice start");
	*/

}