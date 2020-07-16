//// pch.cpp: source file corresponding to the pre-compiled header
//
//
#include "pch.h"
//#include <fstream>
//std::ofstream fout;
//template <typename T, typename T1, typename T2>
//constexpr T RVA2VA(T1 base, T2 rva) {
//	fout << "\t\tRVA2VA?" << std::endl;
//	fout.flush();
//	fout << "\t\tTouching rva: " << rva << std::endl;
//	fout.flush();
//	fout << "\t\tTouching base:" << base << std::endl;
//	fout.flush();
//	fout << "\t\tCasting " << base << " with offset " << rva << "\n";
//	fout.flush();
//	return reinterpret_cast<T>(reinterpret_cast<ULONG_PTR>(base) + rva);
//}
//
//template <typename T>
//constexpr T DataDirectoryFromModuleBase(void* moduleBase, size_t entryID) {
//	fout << "\tDDFMB: with a module base of " << std::hex << (unsigned long long)moduleBase << std::endl;
//	fout.flush();
//	auto dosHdr = reinterpret_cast<PIMAGE_DOS_HEADER>(moduleBase);
//	fout << "\tdosHdr recieved\n";
//	fout.flush();
//	fout << "\t&e_lfanew: " << std::hex << &(dosHdr->e_lfanew) << std::endl;
//	fout.flush();
//	fout << "\te_lfanew: " << std::hex << (long long)(dosHdr->e_lfanew) << std::endl;
//	fout.flush();
//	auto ntHdr = RVA2VA<PIMAGE_NT_HEADERS>(moduleBase, dosHdr->e_lfanew);
//	fout << "\tHdr recieved\n";
//	fout.flush();
//	auto dataDir = ntHdr->OptionalHeader.DataDirectory;
//	fout << "\tdataDir ptr: " << std::hex << &dataDir << std::endl;
//	fout.flush();
//	fout << "\tEntryID: " << entryID << std::endl;
//	fout.flush();
//	fout << "\td@e ptr: " << &(dataDir[entryID]) << std::endl;
//	fout.flush();
//	fout << "\tApplying...\n";
//	fout.flush();
//	return RVA2VA<T>(moduleBase, dataDir[entryID].VirtualAddress);
//}
//
//PIMAGE_THUNK_DATA FindAddressByName(void* moduleBase, PIMAGE_THUNK_DATA impName, PIMAGE_THUNK_DATA impAddr, const char* funcName) {
//	for (; impName->u1.Ordinal; ++impName, ++impAddr) {
//		if (IMAGE_SNAP_BY_ORDINAL(impName->u1.Ordinal))
//			continue;
//
//		auto import = RVA2VA<PIMAGE_IMPORT_BY_NAME>(moduleBase, impName->u1.AddressOfData);
//		if (strcmp(import->Name, funcName) != 0)
//			continue;
//		return impAddr;
//	}
//	return nullptr;
//}
//
//PIMAGE_THUNK_DATA FindAddressByOrdinal(void* moduleBase, PIMAGE_THUNK_DATA impName, PIMAGE_THUNK_DATA impAddr, uint16_t ordinal) {
//	for (; impName->u1.Ordinal; ++impName, ++impAddr) {
//		if (IMAGE_SNAP_BY_ORDINAL(impName->u1.Ordinal) && IMAGE_ORDINAL(impName->u1.Ordinal) == ordinal)
//			return impAddr;
//	}
//	return nullptr;
//}
//
////PIMAGE_THUNK_DATA FindIatThunkInModule(void* moduleBase, const char* dllName, const char* funcName) {
////	auto imports = DataDirectoryFromModuleBase<PIMAGE_IMPORT_DESCRIPTOR>(moduleBase, IMAGE_DIRECTORY_ENTRY_IMPORT);
////	for (; imports->Name; ++imports) {
////		if (_stricmp(RVA2VA<LPCSTR>(moduleBase, imports->Name), dllName) != 0)
////			continue;
////
////		auto origThunk = RVA2VA<PIMAGE_THUNK_DATA>(moduleBase, imports->OriginalFirstThunk);
////		auto thunk = RVA2VA<PIMAGE_THUNK_DATA>(moduleBase, imports->FirstThunk);
////		return FindAddressByName(moduleBase, origThunk, thunk, funcName);
////	}
////	return nullptr;
////}
//
////PIMAGE_THUNK_DATA FindDelayLoadThunkInModule(void* moduleBase, const char* dllName, const char* funcName) {
////	auto imports = DataDirectoryFromModuleBase<PIMAGE_DELAYLOAD_DESCRIPTOR>(moduleBase, IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT);
////	for (; imports->DllNameRVA; ++imports) {
////		if (_stricmp(RVA2VA<LPCSTR>(moduleBase, imports->DllNameRVA), dllName) != 0)
////			continue;
////
////		auto impName = RVA2VA<PIMAGE_THUNK_DATA>(moduleBase, imports->ImportNameTableRVA);
////		auto impAddr = RVA2VA<PIMAGE_THUNK_DATA>(moduleBase, imports->ImportAddressTableRVA);
////		return FindAddressByName(moduleBase, impName, impAddr, funcName);
////	}
////	return nullptr;
////}
//
////PIMAGE_THUNK_DATA FindDelayLoadThunkInModule(void* moduleBase, const char* dllName, uint16_t ordinal) {
////	fout = std::ofstream("FDLTIM.log");
////	if (!moduleBase) {
////		fout << "Base is null...\n";
////		fout.flush();
////		try {
////			fout << "Loading lib...\n";
////			fout.flush();
////			LoadLibraryExW(L"comctl32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
////			fout << "Retrying Module Base...\n";
////			fout.flush();
////			moduleBase = GetModuleHandleW(L"comctl32.dll");
////			if (!moduleBase) {
////				fout << "Still fucked\n";
////				fout.close();
////				return NULL;
////			}
////			fout << "Worked!\n";
////			fout.flush();
////			_CATCH_ALL
////				fout << "Crash...\n";
////			fout.close();
////			return NULL;
////		}
////	}
////	fout << "Finding Delay:\n";
////	fout.flush();
////	auto imports = DataDirectoryFromModuleBase<PIMAGE_DELAYLOAD_DESCRIPTOR>(moduleBase, IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT);
////	fout << "Got Imports\n";
////	fout.flush();
////	for (; imports->DllNameRVA; ++imports) {
////		fout << "\tCurrent \"" << std::hex << (long long)(imports->DllNameRVA) << "\"\n";
////
////		fout.flush();
////
////		if (_stricmp(RVA2VA<LPCSTR>(moduleBase, imports->DllNameRVA), dllName) != 0)
////			continue;
////
////		auto impName = RVA2VA<PIMAGE_THUNK_DATA>(moduleBase, imports->ImportNameTableRVA);
////		auto impAddr = RVA2VA<PIMAGE_THUNK_DATA>(moduleBase, imports->ImportAddressTableRVA);
////		fout << "Done! Getting Ordinal\n";
////		fout.close();
////		return FindAddressByOrdinal(moduleBase, impName, impAddr, ordinal);
////	}
////	fout << "Return null\n";
////	fout.close();
////	return nullptr;
////}
