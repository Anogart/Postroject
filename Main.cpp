// Windows ��� ����:
#include <windows.h>
#include <CommCtrl.h>
#include <stdlib.h> // itoa. ?sprintf ..
#include <math.h>

#include "class.h"
#include "resource.h"

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
LPCTSTR szWindowClass = TEXT("PostProject1");   // �⺻ â Ŭ���� �̸��Դϴ�.

int wWidth = 500; int wHeight = 700;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


// WinMain
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg; // �޽��� ����ü
	HWND hWnd; // ������ �ڵ�
	WNDCLASSEXW wcex; 	// â Ŭ����

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//(COLOR_WINDOW);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);
	RegisterClassExW(&wcex);


	// â�� �����մϴ�.
	hWnd = CreateWindowW(
		szWindowClass, // Ŭ���� �̸�
		szWindowClass, // Ÿ��Ʋ �̸�
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // ������ ��Ÿ��
		((GetSystemMetrics(SM_CXSCREEN) / 2) - (wWidth / 2)), // ��
		((GetSystemMetrics(SM_CYSCREEN) / 2) - (wHeight / 2)), // ����
		wWidth, // ��
		wHeight, // ����
		nullptr, // �θ� �ڵ�
		nullptr, // �޴� �ڵ�
		hInstance, // ���� �ν��Ͻ� �ڵ�
		nullptr); // ������ ����

	ShowWindow(hWnd, nCmdShow); // ȭ�� ���

								// �⺻ �޽��� ť - �����Դϴ�. WM_QUIT ��� ����
	while (GetMessage(&msg, NULL, 0, 0)) { 
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


// WndProc
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WM_PAINT
	HDC hdc;
	PAINTSTRUCT ps;
	HFONT font, oldfont;
	RECT lpRect; // ������ ��ġ

	static Time Now;//�ð� üũ �� �� ..
	static Pawn here;
	static BOOL InvenNOW = TRUE; //On-Off
	static double SpeedSec;

	/*�ʱ�ȭ. Str, Sec, Min, Hour*/
	static TCHAR Str1[10], Str2[30];
	int Sec = 0; int Min = 59; int Hour = 0;

	switch (message) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL); //0.1��.

		//�ð� üũ
		Now.TimeSet(Sec, Min, Hour);
		Now.WriteTick(Str1);

		SpeedSec = 5000; //5�ʸ���
		SetTimer(hWnd, 2, SpeedSec, NULL);

		//Pawn ����
		here.SetPosition(0, 0);
		here.ToPosition(300, 300);
		here.SetSpeed(10);
		here.TestReading(Str2, 1);
		//Go.SetPosition(3, 3); ���� ������ 3, 3

		//���� ǥ��
		SendMessage(hWnd, WM_PAINT, 0, 0);
		return 0;

	case WM_CHAR:
		switch ((TCHAR)wParam) {

			// inventory
		case 'i':
		case 'I':
			if (InvenNOW == TRUE) {
				InvenNOW = FALSE;
				wWidth = wWidth + 500;
				
				GetWindowRect(hWnd, &lpRect);
				SetWindowPos(hWnd,NULL,
					lpRect.left, lpRect.top,
					wWidth,wHeight,SWP_NOZORDER);
			} else {
				InvenNOW = TRUE;
				wWidth = wWidth - 500;

				GetWindowRect(hWnd, &lpRect);
				SetWindowPos(hWnd, NULL,
					lpRect.left, lpRect.top,
					wWidth, wHeight,SWP_NOZORDER);
			}
			break;
		}

	case WM_TIMER:
		switch (wParam) {
		case 1:
			Now.CheckTick();
			Now.WriteTick(Str1);
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case 2:
			static int i = 0;
			here.MovePer();
			here.CheckChange(i);
			here.TestReading(Str2, i);
			i++;

		}


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		//��Ʈ ����
		font = CreateFont(15, 0,
			0, 0, 0, 0,
			0, 0, HANGEUL_CHARSET,
			0, 0, 0, 0,
			TEXT("�ü�"));
		oldfont = (HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);

		//���
		TextOut(hdc, 10, 10, Str1, lstrlen(Str1));
		TextOut(hdc, 10, 30, Str2, lstrlen(Str2));


		//TextOut(hdc, 10, 635, Str2, lstrlen(Str2));

		// inventory
		if (InvenNOW == FALSE) { 
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			GetWindowRect(hWnd, &lpRect);
			MoveToEx(hdc, wWidth / 2, 15, NULL);
			LineTo(hdc, wWidth / 2, wHeight - 50);

			TCHAR Str3[50];
			TCHAR Str4[50];
			int a = 3;
			int b = 4;
			int c = 5;
			wsprintf(Str3, TEXT("Inventory"));
			TextOut(hdc, (wWidth / 2) + 10, 10, Str3, lstrlen(Str3));
			//TextOut(hdc, (wWidth / 2) + 20, 35, Str2, lstrlen(Str2));
			//TextOut(hdc, (wWidth / 2) + 20, 50, Str2, lstrlen(Str2));
			//TextOut(hdc, (wWidth / 2) + 20, 65, Str2, lstrlen(Str2));

			// String Table testing
			LoadString(hInst, IDS_STRING101, Str3, 256);
			wsprintf(Str4, (LPCTSTR)Str3, a, b, c);
			TextOut(hdc, (wWidth / 2) + 20, 80, Str4, lstrlen(Str4));

			SelectObject(hdc, hOldPen);
			DeleteObject(hPen);
		}

		//����
		SelectObject(hdc, oldfont);
		DeleteObject(font);

		EndPaint(hWnd, &ps);
		return 0;


	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, message, wParam, lParam));
}