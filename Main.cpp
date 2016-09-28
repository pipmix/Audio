#include "stdafx.h"
#include "App.h"
#include "Button.h"
#include "Slider.h"
#include <string>
using namespace std;

#define MAX_LOADSTRING 100

int gColorDarkGrey = 50;
int gColG70 = 70;

Audio gAudio;
ComPtr<IXAudio2> g_xAudio2;

HFONT consoleFont;

HINSTANCE hInst;
HWND ghWnd;
App app;


HWND hBut1Play;
HWND hBut1Stop;
HWND hBut2Play;
HWND hBut2Stop;

HWND hButSet1;

HWND hEditBox;

HWND hSlider1, hSlider2;
void DrawButton(DRAWITEMSTRUCT *dis, HWND hwnd);
static TCHAR szWindowClass[] = _T("AudioWindowClass");
static TCHAR szTitle[] = _T("Audio");

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	MyRegisterClass(hInstance);
	ghWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


	ShowWindow(ghWnd, nCmdShow);
	UpdateWindow(ghWnd);

	INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX),
		ICC_BAR_CLASSES | ICC_DATE_CLASSES | ICC_LISTVIEW_CLASSES | ICC_STANDARD_CLASSES |
		ICC_TREEVIEW_CLASSES | ICC_USEREX_CLASSES | ICC_WIN95_CLASSES };
	InitCommonControlsEx(&icc);

	
	app.Create();

	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			app.Tick();

		}
	}

	return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(gColorDarkGrey, gColorDarkGrey, gColorDarkGrey));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	return RegisterClassExW(&wcex);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {

	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT *item = (DRAWITEMSTRUCT*)lParam;
		switch (item->CtlID) {
		case DEF_BUT1_PLAY: DrawButton(item, hBut1Play); break;
		case DEF_BUT1_STOP: DrawButton(item, hBut1Stop); break;
		case DEF_BUT2_PLAY: DrawButton(item, hBut2Play); break;
		case DEF_BUT2_STOP: DrawButton(item, hBut2Stop); break;
		case DEF_BUT_SET1: DrawButton(item, hButSet1); break;

		}
		return TRUE;
	}
	break;
		case WM_CREATE: {



			NONCLIENTMETRICS ncm;
			ncm.cbSize = sizeof(ncm);
			SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
			HFONT hFont = CreateFontIndirect(&ncm.lfMessageFont);

			// set the new font
			

			consoleFont = CreateFont(0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Arial"));

			hBut1Play = CreateButton(hWnd, L"S2 Play", DEF_BUT1_PLAY);
			hBut1Stop = CreateButton(hWnd, L"S2 Stop", DEF_BUT1_STOP);
			hBut2Play = CreateButton(hWnd, L"S3 Play", DEF_BUT2_PLAY);
			hBut2Stop = CreateButton(hWnd, L"S3 Stop", DEF_BUT2_STOP);
			hButSet1 = CreateButton(hWnd,  L"Set",		DEF_BUT_SET1);

			hEditBox = CreateWindowEx(0, L"Edit", L"c", WS_VISIBLE | WS_CHILD | WS_BORDER, 30, 400, 600, 200, hWnd, (HMENU)0, GetModuleHandle(NULL), NULL);
			//SendMessage(hEditBox, WM_SETFONT, (WPARAM)consoleFont, (LPARAM)MAKELONG(TRUE, 0));
			SendMessage(hEditBox, WM_SETFONT, (WPARAM)hFont, 0);
			SendMessage(hBut1Play, WM_SETFONT, (WPARAM)hFont, 0);
			SendMessage(hBut1Stop, WM_SETFONT, (WPARAM)hFont, 0);
			SendMessage(hBut2Play, WM_SETFONT, (WPARAM)hFont, 0);
			SendMessage(hBut2Stop, WM_SETFONT, (WPARAM)hFont, 0);
			SendMessage(hButSet1, WM_SETFONT, (WPARAM)hFont, 0);

			hSlider1 = CreateSlider(hWnd, 0, 100, 40, 50, DEF_SLI_1);
			hSlider2 = CreateSlider(hWnd, 0, 100, 40, 50, DEF_SLI_2);



		}
		break;


		case WM_COMMAND:{
			int wmId = LOWORD(wParam);

			switch (wmId){

				case DEF_BUT_SET1: {
					DWORD pos = SendMessageW(hSlider1, TBM_GETPOS, 0, 0);
					int pp = pos;
					//SendMessage(hEditBox, EM_SETSEL, -2, -2);
					//SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(pp).c_str());


					float vChange = (float)pp *0.01f;
					//gAudio.SetVolume(vChange, 1);
					gAudio.SetPitch(vChange, 1);
					SendMessage(hEditBox, EM_SETSEL, -2, -2);
					SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(vChange).c_str());

				}
								break;





				case DEF_BUT1_PLAY:
					app.Play(2);

					break;
				case DEF_BUT1_STOP:
					app.Stop(2);
					{
						int idx = GetWindowTextLength(hEditBox);
						//SendMessage(hEditBox, EM_SETSEL, idx, idx);

						WCHAR* buffer = L" ";
						WAVEFORMATEX* temp = app.GetWaveFormat(2);
						WCHAR* b1 = L" nChan ";
						int t1 = temp->nChannels;

						WCHAR* b2 = L" nSamp ";
						int t2 = temp->nSamplesPerSec;

						WCHAR* b3 = L" wbits ";
						int t3 = temp->wBitsPerSample;

						WCHAR* b4 = L" nblock ";
						int t4 = temp->nBlockAlign;

						WCHAR* b5 = L" cbsize ";
						int t5 = temp->cbSize;

						WCHAR* b6 = L" nAvgbytes ";
						int t6 = temp->nAvgBytesPerSec;

						WCHAR* b7 = L" wformat ";
						int t7 = temp->wFormatTag;


						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b1);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t1).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b2);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t2).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b3);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t3).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b4);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t4).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b5);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t5).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b6);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t6).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b7);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t7).c_str());
					}
						break;
				case DEF_BUT2_PLAY:
					app.Play(3);
						break;
				case DEF_BUT2_STOP:
					app.Stop(3);
					{
						
						int idx = GetWindowTextLength(hEditBox);
						//SendMessage(hEditBox, EM_SETSEL, idx, idx);

						WCHAR* buffer = L" ";
						WAVEFORMATEX* temp = app.GetWaveFormat(2);
						WCHAR* b1 = L" nChan ";
						int t1 = temp->nChannels;

						WCHAR* b2 = L" nSamp ";
						int t2 = temp->nSamplesPerSec;

						WCHAR* b3 = L" wbits ";
						int t3 = temp->wBitsPerSample;

						WCHAR* b4 = L" nblock ";
						int t4 = temp->nBlockAlign;

						WCHAR* b5 = L" cbsize ";
						int t5 = temp->cbSize;

						WCHAR* b6 = L" nAvgbytes ";
						int t6 = temp->nAvgBytesPerSec;

						WCHAR* b7 = L" wformat ";
						int t7 = temp->wFormatTag;


						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b1);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t1).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b2);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t2).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b3);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t3).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b4);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t4).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b5);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t5).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b6);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t6).c_str());

						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)b7);
						SendMessage(hEditBox, EM_SETSEL, -2, -2);
						SendMessage(hEditBox, EM_REPLACESEL, 0, (LPARAM)to_wstring(t7).c_str());
					}
						break;

			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;



		case WM_SIZE: {
			int butWidth = 100;
			int butHeight = 30;
			int ind = 5;

			MoveWindow(hBut1Play, ind, 30, butWidth, butHeight, 1);
			MoveWindow(hBut1Stop, ind, 90, butWidth, butHeight, 1);
			MoveWindow(hBut2Play, ind, 150, butWidth, butHeight, 1);
			MoveWindow(hBut2Stop, ind, 210, butWidth, butHeight, 1);
			MoveWindow(hButSet1, ind+100, 210, butWidth, butHeight, 1);

			MoveWindow(hSlider1, 300, 20, 200, 30, 1);
			MoveWindow(hSlider2, 300, 60, 200, 30, 1);

		}
					  break;

		case WM_PAINT:{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			SelectObject(ps.hdc, consoleFont);

			EndPaint(hWnd, &ps);
		}
		break;

		case WM_DESTROY: {
			PostQuitMessage(0);
		}
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void DrawButton(DRAWITEMSTRUCT *itemStruct, HWND hwnd) {
	SetBkColor(itemStruct->hDC, RGB(gColG70, gColG70, gColG70));
	HDC hdc = itemStruct->hDC;
	RECT rect = itemStruct->rcItem;        //Get button rect

	//FillRect(hdc, &rect, (HBRUSH)RGB(255, 0, 255));
	SetTextColor(hdc, (COLORREF)RGB(255, 255,255));



	//SetBkMode(hdc, OPAQUE);
	

	RECT rc;
	GetClientRect(hwnd, &rc);

	

	WCHAR buf[255];
	GetWindowText(hwnd, buf, 255);
	DrawText(hdc, buf, std::wcslen(buf), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	UINT state = itemStruct->itemState; //Get state of the button
	if ((state & ODS_SELECTED))            // If it is pressed
	{
		DrawEdge(hdc, &rect, EDGE_SUNKEN, BF_RECT);

	}
	else
	{
		DrawEdge(hdc, &rect, EDGE_RAISED, BF_RECT);

	}
	//SetTextColor(hdc, (COLORREF)RGB(255, 255, 0));


	if ((state & ODS_FOCUS))       // If the button is focused
	{

		int iChange = 3;
		rect.top += iChange;
		rect.left += iChange;
		rect.right -= iChange;
		rect.bottom -= iChange;
		DrawFocusRect(hdc, &rect);

	}

	SIZE size;
	GetTextExtentPoint32(hdc, buf, std::wcslen(buf), &size);
	ExtTextOut(hdc,

		((itemStruct->rcItem.right - itemStruct->rcItem.left) - size.cx) / 2,

		((itemStruct->rcItem.bottom - itemStruct->rcItem.top) - size.cy) / 2,

		ETO_OPAQUE | ETO_CLIPPED, &itemStruct->rcItem, buf, std::wcslen(buf), NULL);


	
}
