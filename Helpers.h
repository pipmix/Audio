#pragma once
#include "stdafx.h"

extern HWND ghWnd;

void Error(LPCWSTR header, LPCWSTR info);

#define SAMPLERATE 44100
#define CHANNELS 2

const std::wstring gAudioDir = L"C:/Box/Box Sync/Data/Audio/";