// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <SDKDDKVer.h>


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <wrl.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory>
#include <tchar.h>
#include <stdint.h>
#include <assert.h>

#include <objbase.h>
#include <mmreg.h>

#include <xaudio2.h>
#pragma comment (lib, "Xaudio2.lib")


// TODO: reference additional headers your program requires here
