#pragma once
#include "stdafx.h"


HWND CreateSlider(HWND parentHWnd,UINT minRange,UINT maxRange,UINT minSelect,UINT maxSelect, UINT def) {


	HWND hSlider = CreateWindowEx(0, TRACKBAR_CLASS, L"Slider", WS_CHILD | WS_VISIBLE  | TBS_ENABLESELRANGE,
		0, 0, 0, 0, parentHWnd, (HMENU)def, GetModuleHandle(NULL), NULL );

	SendMessage(hSlider, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(minRange, maxRange));

	SendMessage(hSlider, TBM_SETPAGESIZE, 0, (LPARAM)4);

	SendMessage(hSlider, TBM_SETSEL, (WPARAM)FALSE, (LPARAM)MAKELONG(minSelect, maxSelect));

	SendMessage(hSlider, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)minSelect);


	return hSlider;
}
