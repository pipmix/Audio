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
void WavFile::Load(std::wstring fileName) {


	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);


	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);



	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &m_waveFormat, dwChunkSize, dwChunkPosition);
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	
	m_wavData = new BYTE[dwChunkSize];
	//BYTE * pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, m_wavData, dwChunkSize, dwChunkPosition);
	m_buffer.AudioBytes = dwChunkSize;
	m_buffer.pAudioData = m_wavData;
	m_buffer.Flags = XAUDIO2_END_OF_STREAM; 


}