// This file contains code from
// https://github.com/stevemk14ebr/PolyHook_2_0/blob/master/sources/IatHook.cpp
// which is licensed under the MIT License.
// See PolyHook_2_0-LICENSE for more information.

#pragma once
//#include <climits>
//#include <cstdint>
//#define WIN32_LEAN_AND_MEAN
//#define NOMINMAX
//#include <Windows.h>
//#include <CommCtrl.h>
//#include <Uxtheme.h>
//#include <WindowsX.h>
#include <Dwmapi.h>
//#include <Vssym32.h>
//#include <iostream>
//using std::cout; using std::cin;
//#pragma comment(lib, "Comctl32.lib")
//#pragma comment(lib, "Uxtheme.lib")
//#pragma comment(lib, "Dwmapi.lib")
//#define IDS_APP_TITLE			103
//
//#define IDR_MAINFRAME			128
//#define IDD_WIN32DARKMODE_DIALOG	102
//#define IDD_ABOUTBOX			103
//#define IDM_ABOUT				104
//#define IDM_EXIT				105
//#define IDI_WIN32DARKMODE			107
//#define IDI_SMALL				108
//#define IDC_WIN32DARKMODE			109
//#define IDC_MYICON				2
//
//template <typename T, typename T1, typename T2>
//constexpr T RVA2VA(T1 base, T2 rva);
//
//template <typename T>
//constexpr T DataDirectoryFromModuleBase(void* moduleBase, size_t entryID);
//
////PIMAGE_THUNK_DATA FindAddressByName(void* moduleBase, PIMAGE_THUNK_DATA impName, PIMAGE_THUNK_DATA impAddr, const char* funcName);
//
////PIMAGE_THUNK_DATA FindAddressByOrdinal(void* moduleBase, PIMAGE_THUNK_DATA impName, PIMAGE_THUNK_DATA impAddr, uint16_t ordinal);
//
////PIMAGE_THUNK_DATA FindIatThunkInModule(void* moduleBase, const char* dllName, const char* funcName);
//
////PIMAGE_THUNK_DATA FindDelayLoadThunkInModule(void* moduleBase, const char* dllName, const char* funcName);
//
////PIMAGE_THUNK_DATA FindDelayLoadThunkInModule(void* moduleBase, const char* dllName, uint16_t ordinal);
