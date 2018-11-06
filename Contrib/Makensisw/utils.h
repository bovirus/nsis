/* 
  Copyright (c) 2002 Robert Rainwater
  Copyright (c) 2002 Robert Rainwater
  Contributors: Justin Frankel, Fritz Elfert, and Sunil Kamath

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Unicode support by Jim Park -- 08/20/2007

*/
#ifndef UTILS_H
#define UTILS_H
#include "resource.h"
#include "toolbar.h"

#ifdef COUNTOF
#undef COUNTOF
#endif
#define COUNTOF(a) (sizeof(a)/sizeof(a[0]))

#define MRU_LIST_SIZE 5
#define MRU_DISPLAY_LENGTH 40
#define SYMSETNAME_MAXLEN 40

template<class T> inline T API_cast(INT_PTR(CALLBACK*p1)(HWND,UINT,WPARAM,LPARAM)) { return (DLGPROC) p1; } // DLGPROC in really old SDKs return BOOL

void* MemAllocZI(SIZE_T cb);
void MemSafeFree(void*mem);
#define MemAlloc MemAllocZI
#define MemFree MemSafeFree
bool WriteUTF16LEBOM(HANDLE hFile);

void FreeSpawn(PROCESS_INFORMATION *pPI, HANDLE hRd, HANDLE hWr);
BOOL InitSpawn(STARTUPINFO &si, HANDLE &hRd, HANDLE &hWr);

int SetArgv(const TCHAR *cmdLine, TCHAR ***argv);
void SetTitle(HWND hwnd,const TCHAR *substr);
void CopyToClipboard(HWND hwnd);
void ClearLog(HWND hwnd);
void LogMessage(HWND hwnd,const TCHAR *str);
void ErrorMessage(HWND hwnd,const TCHAR *str);
void CenterOnParent(HWND hwnd);
void SetDialogFocus(HWND hDlg, HWND hCtl); // Use this and not SetFocus()!
HWND GetComboEdit(HWND hCB);
#define DisableItems(hwnd) EnableDisableItems(hwnd, 0)
#define EnableItems(hwnd) EnableDisableItems(hwnd, 1)
void EnableDisableItems(HWND hwnd, int on);
bool OpenRegSettingsKey(HKEY &hKey, bool create = false);
#define CreateRegSettingsKey(refhkey) OpenRegSettingsKey((refhkey), true)
DWORD ReadRegSettingDW(LPCTSTR name, const DWORD defval);
void RestoreWindowPos(HWND hwnd);
void SaveWindowPos(HWND hwnd);
void ResetObjects();
void ResetSymbols();
int InitBranding();
void InitTooltips(HWND h);
void DestroyTooltips();
void AddTip(HWND hWnd,LPCTSTR lpszToolTip);
void ShowDocs();
void RestoreCompressor();
void SaveCompressor();
void SetCompressorStats();

BOOL PopMRUFile(TCHAR* fname);
void PushMRUFile(TCHAR* fname);
void BuildMRUMenus();
void LoadMRUFile(int position);
void ClearMRUList();

bool FileExists(const TCHAR *fname);
bool OpenUrlInDefaultBrowser(HWND hwnd, LPCSTR Url);

HMENU FindSubMenu(HMENU hMenu, UINT uId);

typedef enum { CFF_RAWSIZE = 0x00, CFF_DPIPT = 0x01, CFF_DPIFROMHWND = 0x02 } CREATEFONTFLAGS;
HFONT CreateFontHelper(INT_PTR Data, int Height, DWORD p1, LPCTSTR Face);
inline HFONT CreateFont(INT_PTR Data, WORD Flags, int Height, WORD Weight, BYTE PitchAndFamily, BYTE CharSet, LPCTSTR Face)
{
  DWORD packed = MAKELONG(MAKEWORD(Weight>>2, Flags), MAKEWORD(CharSet, PitchAndFamily));
  return CreateFontHelper(Data, Height, packed, Face);
}
inline HFONT CreateFontPt(HWND hWndDPI, int Height, WORD Weight, BYTE PitchAndFamily, BYTE CharSet, LPCTSTR Face)
{
  return CreateFont((INT_PTR) hWndDPI, CFF_DPIFROMHWND|CFF_DPIPT, Height, Weight, PitchAndFamily, CharSet, Face);
}
BOOL DrawHorzGradient(HDC hDC, LONG l, LONG t, LONG r, LONG b, COLORREF c1, COLORREF c2);
inline long RectW(const RECT&r) { return r.right - r.left; }
inline long RectH(const RECT&r) { return r.bottom - r.top; }
long DlgUnitToPixelX(HWND hDlg, long x);
long DlgUnitToPixelY(HWND hDlg, long y);
UINT DpiGetForWindow(HWND hWnd);
int DpiScaleY(HWND hWnd, int Val);

void DrawGripper(HWND hWnd, HDC hDC, const RECT&r);
static inline void GetGripperPos(HWND hwnd, RECT&r)
{
  GetClientRect(hwnd, &r);
  r.left = r.right - GetSystemMetrics(SM_CXVSCROLL);
  r.top = r.bottom - GetSystemMetrics(SM_CYVSCROLL);
}

#endif
