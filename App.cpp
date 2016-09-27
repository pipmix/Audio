#include "stdafx.h"
#include "App.h"

App::App(){
}

void App::Create(){

	audio.Create();
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
	audio.Play(num);
}

void App::Stop(int num) {
	audio.Stop(num);

}

WAVEFORMATEX* App::GetWaveFormat(int i) {

	return audio.GetWaveFormat(i);
}