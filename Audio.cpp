#include "Audio.h"


Audio::Audio(){
}

void Audio::Create() {


	HRESULT hr;


	hr = XAudio2Create(&m_xAudio2);
	if (FAILED(hr)) Error(L"Audio Error", L"xaudio2 device creation");


	hr = m_xAudio2->CreateMasteringVoice(&m_masterVoice);
	if (FAILED(hr)) Error(L"Audio Error", L"Mastering voice creation");

	hr = m_xAudio2->CreateSubmixVoice(&m_submixVoice, CHANNELS, SAMPLERATE);
	if (FAILED(hr)) Error(L"Audio Error", L"Submix voice creation");

	m_sendDesc = { 0, m_submixVoice };
	m_voiceSends = { 1, &m_sendDesc };



	wf1.Load(L"c:/s2.wav");
	wf2.Load(L"c:/s3.wav");


	//hr = m_xAudio2->CreateSourceVoice(&m_SourceVoice, (WAVEFORMATEX*)wf1.GetWaveFormat());
	//if (FAILED(hr))Error(L"Audio Error", L"Create Source Voice");

	//hr = m_SourceVoice->SubmitSourceBuffer(wf1.GetBuffer());
	//if (FAILED(hr))Error(L"Audio Error", L"Submit Source Voice");

	//hr = m_SourceVoice->Start(0);
	//if (FAILED(hr))Error(L"Audio Error", L"Source voice start");

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

	HRESULT hr;
	//IXAudio2SourceVoice* sourceVoice;
	//m_xAudio2->CreateSourceVoice(&pSourceVoice2, waveData2.wfx);
	//return sourceVoice;

	byte soundData[5 * 2 * 44100];

	WAVEFORMATEX waveformat;
	waveformat.wFormatTag = WAVE_FORMAT_PCM;
	waveformat.nChannels = 1;
	waveformat.nSamplesPerSec = 44100;
	waveformat.wBitsPerSample = 16;
	waveformat.nBlockAlign = ((waveformat.nChannels  *  waveformat.wBitsPerSample) / 8);
	waveformat.nAvgBytesPerSec = waveformat.nSamplesPerSec * waveformat.nBlockAlign;
	
	waveformat.cbSize = 0;

	m_xAudio2->CreateSourceVoice(&m_SourceVoice, &waveformat);

	m_SourceVoice->Start();

	for (int index = 0, second = 0; second < 5; second++)
	{
		for (int cycle = 0; cycle < 441; cycle++)
		{
			for (int sample = 0; sample < 100; sample++)
			{
				short value = sample < 50 ? 32767 : -32768;
				soundData[index++] = value & 0xFF;
				soundData[index++] = (value >> 8) & 0xFF;
			}
		}
	}

	XAUDIO2_BUFFER buffer = { 0 };
	buffer.AudioBytes = 2 * 5 * 44100;
	buffer.pAudioData = soundData;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.PlayBegin = 0;
	buffer.PlayLength = 5 * 44100;

	hr = m_SourceVoice->SubmitSourceBuffer(&buffer);
	if (FAILED(hr))Error(L"Audio Error", L"Buffer creation");

	

	return nullptr;
	// if (!playing) source->start
	//else {
	//	source->stop()
	//	source->start()
	//}



}

XAUDIO2_BUFFER*	Audio::CreateBuffer() {

	WAVEFORMATEXTENSIBLE wfx = { 0 };
	XAUDIO2_BUFFER buffer = { 0 };


	TCHAR * strFileName = _TEXT("c:/s2.wav");


	HANDLE hFile = CreateFile(strFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);


	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourccWAVE)return nullptr;


	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	BYTE * pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);
	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

	HRESULT hr;
	hr = m_xAudio2->CreateSourceVoice(&m_SourceVoice, (WAVEFORMATEX*)&wfx); 
	if (FAILED(hr))Error(L"Audio Error", L"Create Source Voice");

	hr = m_SourceVoice->SubmitSourceBuffer(&buffer);
	if (FAILED(hr))Error(L"Audio Error", L"Submit Source Voice");

	hr = m_SourceVoice->Start(0);
	if (FAILED(hr))Error(L"Audio Error", L"Source voice start");




}



void Audio::Exit()
{

	//m_masterVoice->DestroyVoice();
}


void Audio::Play(int num) {
	HRESULT hr;

	//WavFile* tmp = &wf1;

	if(num==2){
	
		hr = m_xAudio2->CreateSourceVoice(&m_SourceVoice, (WAVEFORMATEX*)wf1.GetWaveFormat());
		if (FAILED(hr))Error(L"Audio Error", L"Create Source Voice");

		hr = m_SourceVoice->SubmitSourceBuffer(wf1.GetBuffer());
		if (FAILED(hr))Error(L"Audio Error", L"Submit Source Voice");

		hr = m_SourceVoice->Start(0);
		if (FAILED(hr))Error(L"Audio Error", L"Source voice start");
	}

	if (num == 3) {

		hr = m_xAudio2->CreateSourceVoice(&m_SourceVoice, (WAVEFORMATEX*)wf2.GetWaveFormat());
		if (FAILED(hr))Error(L"Audio Error", L"Create Source Voice");

		hr = m_SourceVoice->SubmitSourceBuffer(wf2.GetBuffer());
		if (FAILED(hr))Error(L"Audio Error", L"Submit Source Voice");

		hr = m_SourceVoice->Start(0);
		if (FAILED(hr))Error(L"Audio Error", L"Source voice start");
	}







}

void Audio::Stop(int num) {

}

WAVEFORMATEX* Audio::GetWaveFormat(int i) {

	if (i == 2)return wf1.GetWaveFormat();
	else if (i == 3)return wf2.GetWaveFormat();
	
}