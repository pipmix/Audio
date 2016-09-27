#include "stdafx.h"
#include "App.h"

App::App(){
}

void App::Create(){

	audio.Create();
	audio.CreateBuffer();
}

void App::Tick(){
	Update();
	Draw();
}

void App::Update(){
}

void App::Draw(){
}
