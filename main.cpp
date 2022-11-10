#include<windows.h>
#include<tchar.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hBoxArr[11], hRadioArr[24], hPicture, hEdit1, hEdit2;

HBITMAP hBmp;

int	WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPTSTR lpszCmdLine, int nCmdShow) {
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
	switch (uMessage) {
		case WM_INITDIALOG:
			for (int i = 0; i < 11; i++) {
				hBoxArr[i] = GetDlgItem(hWnd, IDC_CHECK1 + i);
			}
			hPicture = GetDlgItem(hWnd, IDC_PICTURE);
			hBmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
			SendMessage(hPicture, STM_SETIMAGE, 0, LPARAM(hBmp));
			hEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
			hEdit2 = GetDlgItem(hWnd, IDC_EDIT2);
			return TRUE;
		
		case WM_CLOSE:
			EndDialog(hWnd,0);
			return TRUE;
		
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK) {
				INT nAnswersRadio[7] = {IDC_RADIO1, IDC_RADIO5, IDC_RADIO8, IDC_RADIO12, IDC_RADIO14, IDC_RADIO16, IDC_RADIO22};
				INT nAnswersCheckB1[2]= { IDC_CHECK1, IDC_CHECK3};
				INT nAnswersCheckB2[3] = { IDC_CHECK5, IDC_CHECK6, IDC_CHECK8 };
				INT nAnswersCheckB3[3] = { IDC_CHECK9, IDC_CHECK10, IDC_CHECK11 };
				INT nMaxMark = 12, nErrors = nMaxMark;
				for (int i = 0; i < 7; i++) {
					if (BST_CHECKED == SendDlgItemMessage(hWnd, nAnswersRadio[i], BM_GETCHECK, 0, 0)) nErrors--;
				}
				INT CheckBoxPoints = 0;
				for (int i = 0; i < 4; i++) {//первый блок
					if (IDC_CHECK1 + i == nAnswersCheckB1[0] || IDC_CHECK1 + i == nAnswersCheckB1[1]) {
						if (BST_CHECKED == SendMessage(hBoxArr[i], BM_GETCHECK, 0, 0)) CheckBoxPoints++;
					}
					if (CheckBoxPoints == 2) {
						nErrors--;
						
						break;
					}
				}
				CheckBoxPoints = 0;
				for (int i = 4; i < 8; i++) {//второй блок
					if (IDC_CHECK1 + i == nAnswersCheckB2[0] || IDC_CHECK1 + i == nAnswersCheckB2[1] || IDC_CHECK1 + i == nAnswersCheckB2[2]) {
						if (BST_CHECKED == SendMessage(hBoxArr[i], BM_GETCHECK, 0,0)) CheckBoxPoints++;
					}
					if (CheckBoxPoints == 3) {
						nErrors--;
						
						break;
					}
				}
				CheckBoxPoints = 0;
				for (int i = 8; i < 11; i++) {//третий блок
					if (IDC_CHECK1 + i == nAnswersCheckB3[0] || IDC_CHECK1 + i == nAnswersCheckB3[1] || IDC_CHECK1 + i == nAnswersCheckB3[2]) {
						if (BST_CHECKED == SendMessage(hBoxArr[i], BM_GETCHECK, 0, 0)) CheckBoxPoints++;
					}
					if (CheckBoxPoints == 3) {
						nErrors--;
						
						break;
					}
				}
				CheckBoxPoints = 0;
				TCHAR Edit1[20], Edit2[20];
				GetWindowText(hEdit1, Edit1, 20);
				GetWindowText(hEdit2, Edit2, 20);
				BOOL bResEdit1 = 0, bResEdit2 = 0;
				if (!lstrcmp(Edit1, TEXT("Берестя"))) nErrors--;
				if (!lstrcmp(Edit2, TEXT("Третій"))) nErrors--;
				INT mark = nMaxMark - nErrors;
				DOUBLE result = (double)mark/nMaxMark*100;
				
				TCHAR str[50];
				_stprintf_s(str, TEXT("Ваш результат %d. Точність %f %%"), mark, result);
				MessageBox(hWnd, str, TEXT("Result"), MB_OK);
			}
			return TRUE;
		}
	}
	return FALSE;
}