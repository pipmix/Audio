#include "Audio.h"


Audio::Audio(){
}

Audio::~Audio() {
	m_masterVoice->DestroyVoice();
}


void Audio::Create() {

	/*
	IUnknown* myXAPO;
	myXAPO = new EF_Gain();
	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	descriptor.InitialState = true;
	descriptor.OutputChannels = 1;
	descriptor.pEffect = myXAPO;
	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = 1;
	chain.pEffectDescriptors = &descriptor;
	pVoice->SetEffectChain(&chain);
	pXAPO->Release();
	XAPO_PARAMETERS XAPOParameters;
	XAPOParameters.Level = 0.75;
	hr = pVoice->SetEffectParameters(0, &XAPOParameters, sizeof(XAPO_PARAMETERS));
	*/

	HRESULT hr;


	hr = XAudio2Create(&g_xAudio2);
	if (FAILED(hr)) Error(L"Audio Error", L"xaudio2 device creation");


	hr = g_xAudio2->CreateMasteringVoice(&m_masterVoice);
	if (FAILED(hr)) Error(L"Audio Error", L"Mastering voice creation");



	hr = g_xAudio2->CreateSubmixVoice(&m_submixVoice, CHANNELS, SAMPLERATE);
	if (FAILED(hr)) Error(L"Audio Error", L"Submix voice creation");

	m_sendDesc = { 0, m_submixVoice };
	m_voiceSends = { 1, &m_sendDesc };

	

	wf1.Load(gAudioDir + L"s2.wav");
	wf2.Load(gAudioDir + L"s3.wav");


	/*
	XAUDIO2_FILTER_PARAMETERS xfp;
	xfp.Frequency = .1f;
	xfp.OneOverQ = 1.0f;
	xfp.Type = HighPassFilter;
	//m_submixVoice->SetFilterParameters(&xfp);


	hr = XAudio2CreateReverb(&m_XAPO1);;
	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	descriptor.InitialState = true;
	descriptor.OutputChannels = 2;
	descriptor.pEffect = m_XAPO1;

	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = 1;
	chain.pEffectDescriptors = &descriptor;


	// create source voice //         m_musicEngine->CreateSourceVoice(&m_musicSourceVoice, &waveFormat, 0, 1.0f, nullptr, nullptr, &chain));
	//m_submixVoice->SetEffectChain(&chain);
	//m_XAPO1->Release();

	XAUDIO2FX_REVERB_PARAMETERS reverbParameters;
	reverbParameters.ReflectionsDelay = XAUDIO2FX_REVERB_DEFAULT_REFLECTIONS_DELAY;
	reverbParameters.ReverbDelay = XAUDIO2FX_REVERB_DEFAULT_REVERB_DELAY;
	reverbParameters.RearDelay = XAUDIO2FX_REVERB_DEFAULT_REAR_DELAY;
	reverbParameters.PositionLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION;
	reverbParameters.PositionRight = XAUDIO2FX_REVERB_DEFAULT_POSITION;
	reverbParameters.PositionMatrixLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
	reverbParameters.PositionMatrixRight = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
	reverbParameters.EarlyDiffusion = XAUDIO2FX_REVERB_DEFAULT_EARLY_DIFFUSION;
	reverbParameters.LateDiffusion = XAUDIO2FX_REVERB_DEFAULT_LATE_DIFFUSION;
	reverbParameters.LowEQGain = XAUDIO2FX_REVERB_DEFAULT_LOW_EQ_GAIN;
	reverbParameters.LowEQCutoff = XAUDIO2FX_REVERB_DEFAULT_LOW_EQ_CUTOFF;
	reverbParameters.HighEQGain = XAUDIO2FX_REVERB_DEFAULT_HIGH_EQ_GAIN;
	reverbParameters.HighEQCutoff = XAUDIO2FX_REVERB_DEFAULT_HIGH_EQ_CUTOFF;
	reverbParameters.RoomFilterFreq = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_FREQ;
	reverbParameters.RoomFilterMain = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_MAIN;
	reverbParameters.RoomFilterHF = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_HF;
	reverbParameters.ReflectionsGain = XAUDIO2FX_REVERB_DEFAULT_REFLECTIONS_GAIN;
	reverbParameters.ReverbGain = XAUDIO2FX_REVERB_DEFAULT_REVERB_GAIN;
	reverbParameters.DecayTime = XAUDIO2FX_REVERB_DEFAULT_DECAY_TIME;
	reverbParameters.Density = XAUDIO2FX_REVERB_DEFAULT_DENSITY;
	reverbParameters.RoomSize = XAUDIO2FX_REVERB_DEFAULT_ROOM_SIZE;
	reverbParameters.WetDryMix = XAUDIO2FX_REVERB_DEFAULT_WET_DRY_MIX;

	hr = m_submixVoice->SetEffectParameters(0, &reverbParameters, sizeof(reverbParameters));

	//m_SourceVoice->DisableEffect(0);
	m_SourceVoice->EnableEffect(0);
	*/
}

// g_xAudio2->StopEngine();   on suspend
//g_xAudio2->StartEngine();  on resume


IXAudio2SubmixVoice* Audio::CreateSubmixVoice() {

	IXAudio2SubmixVoice* submixVoice;
	g_xAudio2->CreateSubmixVoice(&submixVoice, 1, SAMPLERATE, 0, 0, 0, 0);

	return submixVoice;

}

IXAudio2SourceVoice* Audio::CreateSourceVoice() {


}


void Audio::SetVolume(float v, int chan){

	m_submixVoice->SetVolume(v);


}

void Audio::SetVolumeLR(float lc, float rc, int chan) {

	float SourceVoiceChannelVolumes[2] = { lc, rc };
	//hr = pSourceVoice->SetChannelVolumes(1, SourceVoiceChannelVolumes);

}
void Audio::SetPitch(float freq, int chan) {
	
	m_SourceVoice->SetFrequencyRatio(freq);

}


void Audio::Play(int num) {
	HRESULT hr;

	if(num==2){

		hr = g_xAudio2->CreateSourceVoice(&m_SourceVoice, (WAVEFORMATEX*)wf1.GetWaveFormat());
		if (FAILED(hr))Error(L"Audio Error", L"Create Source Voice");

		hr = m_SourceVoice->SubmitSourceBuffer(wf1.GetBuffer());
		if (FAILED(hr))Error(L"Audio Error", L"Submit Source Voice");

		hr = m_SourceVoice->Start(0);
		if (FAILED(hr))Error(L"Audio Error", L"Source voice start");
	}

	if (num == 3) {


		hr = g_xAudio2->CreateSourceVoice(&m_SourceVoice, (WAVEFORMATEX*)wf2.GetWaveFormat());
		m_SourceVoice->SetOutputVoices(&m_voiceSends);
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