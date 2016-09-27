#include "stdafx.h"
#include "App.h"

App::App(){
}

void App::Create(){

	gAudio.Create();
	//audio.CreateBuffer();
}

void App::Tick(){
	Update();
	Draw();
}

void App::Update(){
}

void App::Draw(){
}

void App::Play(int num) {
	gAudio.Play(num);
}

void App::Stop(int num) {
	gAudio.Stop(num);

}

WAVEFORMATEX* App::GetWaveFormat(int i) {

	return gAudio.GetWaveFormat(i);
}