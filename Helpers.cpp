#include "stdafx.h"
#include "Helpers.h"

void Error(LPCWSTR header, LPCWSTR info)
{

	MessageBox(NULL, info, header, NULL);
	PostMessage(ghWnd, WM_CLOSE, NULL, NULL);
}
