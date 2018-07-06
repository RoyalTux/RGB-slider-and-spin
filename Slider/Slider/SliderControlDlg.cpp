#include "SliderControlDlg.h"

CSliderControlDlg* CSliderControlDlg::ptr = NULL;

CSliderControlDlg::CSliderControlDlg(void)
{
	ptr = this;
}

void CSliderControlDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CSliderControlDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;
	hSpin1 = GetDlgItem(hDialog, IDC_SPIN1);
	hSpin2 = GetDlgItem(hDialog, IDC_SPIN2);
	hSpin3 = GetDlgItem(hDialog, IDC_SPIN3);
	hEdit1 = GetDlgItem(hDialog, IDC_EDIT1);
	hEdit2 = GetDlgItem(hDialog, IDC_EDIT2);
	hEdit3 = GetDlgItem(hDialog, IDC_EDIT3);
	//
	UDACCEL pAcceleration_1[2] = { { 1,10 },{ 3,100 }};
	SendMessage(hSpin1, UDM_SETACCEL, 2, LPARAM(pAcceleration_1));
	UDACCEL pAcceleration_2[2] = { { 1,10 },{ 3,100 } };
	SendMessage(hSpin2, UDM_SETACCEL, 2, LPARAM(pAcceleration_2));
	UDACCEL pAcceleration_3[2] = { { 1,10 },{ 3,100 } };
	SendMessage(hSpin3, UDM_SETACCEL, 2, LPARAM(pAcceleration_3));
	//
	SendMessage(hSpin1, UDM_SETBUDDY, WPARAM(hEdit1), 0);
	SetWindowText(hEdit1, TEXT("0"));
	SendMessage(hSpin2, UDM_SETBUDDY, WPARAM(hEdit2), 0);
	SetWindowText(hEdit2, TEXT("0"));
	SendMessage(hSpin3, UDM_SETBUDDY, WPARAM(hEdit3), 0);
	SetWindowText(hEdit3, TEXT("0"));
	//
	hRed2 = GetDlgItem(hDialog, IDC_SPIN1);
	hGreen2 = GetDlgItem(hDialog, IDC_SPIN2);
	hBlue2 = GetDlgItem(hDialog, IDC_SPIN3);
	SendMessage(hRed2, UDM_SETRANGE32, 0, 255);
	SendMessage(hGreen2, UDM_SETRANGE32, 0, 255);
	SendMessage(hBlue2, UDM_SETRANGE32, 0, 255);
	////
	hRed1 = GetDlgItem(hDialog, IDC_SLIDER1);
	hGreen1 = GetDlgItem(hDialog, IDC_SLIDER2);
	hBlue1 = GetDlgItem(hDialog, IDC_SLIDER3);
	hResult = GetDlgItem(hDialog, IDC_PROGRESS1);
	SendMessage(hRed1, TBM_SETRANGE, TRUE, MAKELPARAM(MIN, MAX));
	SendMessage(hGreen1, TBM_SETRANGE, TRUE, MAKELPARAM(MIN, MAX));
	SendMessage(hBlue1, TBM_SETRANGE, TRUE, MAKELPARAM(MIN, MAX));
	return TRUE;
}

void CSliderControlDlg::Cls_OnSpin(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BUTTON1)
	{
		static int red = 0, green = 0, blue = 0;
		int nCurrentPos1 = SendMessage(hSpin1, UDM_GETPOS32, 0, 0);
		int nCurrentPos2 = SendMessage(hSpin2, UDM_GETPOS32, 0, 0);
		int nCurrentPos3 = SendMessage(hSpin3, UDM_GETPOS32, 0, 0);
		if (hSpin1 == hRed2)
			red = nCurrentPos1;
		if (hSpin2 == hGreen2)
			green = nCurrentPos2;
		if (hSpin3 == hBlue2)
			blue = nCurrentPos3;
		SendMessage(hResult, PBM_SETBKCOLOR, 0, RGB(red, green, blue));
	}
}

void CSliderControlDlg::Cls_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{
	static int red = 0, green = 0, blue = 0;
	int nCurrentPos = SendMessage(hwndCtl, TBM_GETPOS, 0, 0);
	if (hwndCtl == hRed1)
		red = nCurrentPos;
	else if (hwndCtl == hGreen1)
		green = nCurrentPos;
	else if (hwndCtl == hBlue1)
			blue = nCurrentPos;
	SendMessage(hResult, PBM_SETBKCOLOR, 0, RGB(red, green, blue));
}

BOOL CALLBACK CSliderControlDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_HSCROLL, ptr->Cls_OnHScroll);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnSpin);
	}
	return FALSE;
}