
#pragma once

#include <SDKDDKVer.h>


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <wrl.h>
#include <commctrl.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory>
#include <tchar.h>
#include <stdint.h>
#include <assert.h>

#include <objbase.h>
#include <mmreg.h>

#include <xaudio2.h>
#include <xapobase.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment (lib, "Xaudio2.lib")

