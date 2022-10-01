#define	_CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "resource.h"
#include <CommCtrl.h> //���X�g�r���[�Ȃǂ̐V�����R���g���[��(1995�N���o��)���g�����ɕK�v
#pragma comment(lib, "comctl32")
#include <tchar.h>
#include <assert.h>
void �]��(HWND hDlg, double ���ϒl)
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
			m.pszText = _ttoi(buf) < ���ϒl ? TEXT("���ϖ���") : TEXT("���ψȏ�");
			m.iSubItem = 1;
			ListView_SetItem(hListView, &m);
			++m.iItem;
		}
		else
			break;
	}
}
void ���ϒl�̌v�Z(HWND hDlg)
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
		for (int ���v = _ttoi(buf); ; ) {
			++m.iItem;
			if (ListView_GetItem(hListView, &m))
				���v += _ttoi(buf);
			else {
				assert(m.iItem >= 1);
				const double ���ϒl = (double)���v / m.iItem;
				_stprintf(buf, _T("%f"), ���ϒl);
				SetDlgItemText(hDlg, IDC_EDIT_Average, buf);
				�]��(hDlg, ���ϒl);
				break;
			}
		}
	}
}
void �f�[�^�ǉ�(HWND hDlg)
{
	BOOL translated;
	const int value = GetDlgItemInt(hDlg, IDC_EDIT_Value, &translated, TRUE);
	if (translated) {
		//�l�����������͂���Ă����ꍇ
		TCHAR buf[128];

		const HWND hListView = GetDlgItem(hDlg, IDC_LIST1);
		LVITEM m;
		m.mask = LVIF_TEXT;
		wsprintf(buf, TEXT("%d"), value);
		m.pszText = buf;
		m.iItem = INT_MAX;//�����ɒǉ�
		m.iSubItem = 0;
		const int iItem = ListView_InsertItem(hListView, &m); //�f�[�^�s�̒ǉ�
		SetDlgItemText(hDlg, IDC_EDIT_Value, TEXT(""));
		ListView_EnsureVisible(hListView, iItem, FALSE);//�B��Ă���s��������悤��

		���ϒl�̌v�Z(hDlg);
	}
}
void ���X�g�r���[�̏���(HWND hDlg)
{
	const HWND hListView = GetDlgItem(hDlg, IDC_LIST1);
	LVCOLUMN col;
	col.mask = LVCF_TEXT | LVCF_WIDTH;
	col.pszText = TEXT("�f�[�^");//�񌩏o��������
	col.cx      = 100;//��
	ListView_InsertColumn(hListView, 0, &col);
	col.pszText = TEXT("�]��");//�񌩏o��������
	col.cx      = 300;//��
	ListView_InsertColumn(hListView, 1, &col);
	
}
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_INITDIALOG:
		���X�g�r���[�̏���(hDlg);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL: //�L�����Z���{�^���A����{�^���Ȃ�
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		case IDOK:
			�f�[�^�ǉ�(hDlg);
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
, _In_opt_ HINSTANCE hPrevInstance //�P�U�r�b�g����̖��c
, _In_     LPSTR     lpCmdLine     //�R�}���h���C������
, _In_     int       nCmdShow      //������ʕ\���̃��[�h
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
