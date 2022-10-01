#define	_CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "resource.h"
#include <CommCtrl.h> //リストビューなどの新しいコントロール(1995年初登場)を使う時に必要
#pragma comment(lib, "comctl32")
#include <tchar.h>
#include <assert.h>
void 評価(HWND hDlg, double 平均値)
{
	const HWND hListView = GetDlgItem(hDlg, IDC_LIST1);
	LVITEM m;
	m.mask = LVIF_TEXT;
	for (m.iItem = 0;   ; ) {
		TCHAR buf[256];
		m.iSubItem = 0;
		m.pszText = buf;
		m.cchTextMax = _countof(buf);
		if (ListView_GetItem(hListView, &m)) {
			m.pszText = _ttoi(buf) < 平均値 ? TEXT("平均未満") : TEXT("平均以上");
			m.iSubItem = 1;
			ListView_SetItem(hListView, &m);
			++m.iItem;
		}
		else
			break;
	}
}
void 平均値の計算(HWND hDlg)
{
	const HWND hListView = GetDlgItem(hDlg, IDC_LIST1);
	LVITEM m;
	m.mask = LVIF_TEXT;
	TCHAR buf[256];
	m.pszText    =          buf ;
	m.cchTextMax = _countof(buf);
	m.iSubItem = 0;
	m.iItem = 0;
	if (ListView_GetItem(hListView, &m)) {
		for (int 合計 = _ttoi(buf); ; ) {
			++m.iItem;
			if (ListView_GetItem(hListView, &m))
				合計 += _ttoi(buf);
			else {
				assert(m.iItem >= 1);
				const double 平均値 = (double)合計 / m.iItem;
				_stprintf(buf, _T("%f"), 平均値);
				SetDlgItemText(hDlg, IDC_EDIT_Average, buf);
				評価(hDlg, 平均値);
				break;
			}
		}
	}
}
void データ追加(HWND hDlg)
{
	BOOL translated;
	const int value = GetDlgItemInt(hDlg, IDC_EDIT_Value, &translated, TRUE);
	if (translated) {
		//値が正しく入力されていた場合
		TCHAR buf[128];

		const HWND hListView = GetDlgItem(hDlg, IDC_LIST1);
		LVITEM m;
		m.mask = LVIF_TEXT;
		wsprintf(buf, TEXT("%d"), value);
		m.pszText = buf;
		m.iItem = INT_MAX;//末尾に追加
		m.iSubItem = 0;
		const int iItem = ListView_InsertItem(hListView, &m); //データ行の追加
		SetDlgItemText(hDlg, IDC_EDIT_Value, TEXT(""));
		ListView_EnsureVisible(hListView, iItem, FALSE);//隠れている行を見えるように

		平均値の計算(hDlg);
	}
}
void リストビューの準備(HWND hDlg)
{
	const HWND hListView = GetDlgItem(hDlg, IDC_LIST1);
	LVCOLUMN col;
	col.mask = LVCF_TEXT | LVCF_WIDTH;
	col.pszText = TEXT("データ");//列見出し文字列
	col.cx      = 100;//列幅
	ListView_InsertColumn(hListView, 0, &col);
	col.pszText = TEXT("評価");//列見出し文字列
	col.cx      = 300;//列幅
	ListView_InsertColumn(hListView, 1, &col);
	
}
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_INITDIALOG:
		リストビューの準備(hDlg);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL: //キャンセルボタン、閉じるボタンなど
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		case IDOK:
			データ追加(hDlg);
			return TRUE;
		default:
			return FALSE;
		}
	default:
		return FALSE;
	}
}
int WINAPI WinMain
( _In_     HINSTANCE hInstance
, _In_opt_ HINSTANCE hPrevInstance //１６ビット時代の名残
, _In_     LPSTR     lpCmdLine     //コマンドライン引数
, _In_     int       nCmdShow      //初期画面表示のモード
)
{
	InitCommonControls();
	(void)DialogBoxParamW
	( /*_In_opt_ HINSTANCE hInstance     */hInstance
	, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG1)
	, /*_In_opt_ HWND      hWndParent    */NULL
	, /*_In_opt_ DLGPROC   lpDialogFunc  */DialogProc
	, /*_In_     LPARAM    dwInitParam   */0
	);
}
