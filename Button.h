#pragma once
#include "stdafx.h"
#include "Defines.h"


HWND CreateButton(HWND parentHWnd, WCHAR* label, UINT def) {

	HWND button = CreateWindowEx(0, L"Button", label, WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, parentHWnd, (HMENU)def, GetModuleHandle(NULL), NULL);
	//HWND button2 = CreateWindowEx(0, L"Edit", L"click", WS_VISIBLE | WS_CHILD | WS_BORDER, 30, 150, 160, 130, parentHWnd, (HMENU)0, GetModuleHandle(NULL), NULL);

	return button;
}