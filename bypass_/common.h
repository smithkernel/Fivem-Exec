#pragma once
#include <Windows.h>
#include <string>
#include <thread>

namespace common.h {

	wchar_t* GetFileNameFromPath(wchar_t* Path)
	{
		wchar_t* LastSlash = NULL;
		for (DWORD i = 0; Path[i] != NULL; i++)
		{
			if (Path[i] == '\\')
				LastSlash = &Path[i + 1];
		}
		return LastSlash;
	}
	wchar_t* RemoveFileExtension(wchar_t* FullFileName, wchar_t* OutputBuffer, DWORD OutputBufferSize)
	{
		wchar_t* LastDot = NULL;
		for (DWORD i = 0; FullFileName[i] != NULL; i++)
			if (FullFileName[i] == '.')
				LastDot = &FullFileName[i];

		for (DWORD j = 0; j < OutputBufferSize; j++)
		{
			OutputBuffer[j] = FullFileName[j];
			if (&FullFileName[j] == LastDot)
			{
				OutputBuffer[j] = NULL;
				break;
			}
		}
		OutputBuffer[OutputBufferSize - 1] = NULL;
		return OutputBuffer;
	}


	HMODULE WINAPI GetModuleW(_In_opt_ LPCWSTR lpModuleName)
	{
		struct CLIENT_ID
		{
			HANDLE UniqueProcess;
			HANDLE UniqueThread;
		};

		//https://processhacker.sourceforge.io/doc/ntpebteb_8h_source.html#l00166
		struct TEB
		{
			NT_TIB NtTib;
			PVOID EnvironmentPointer;
			CLIENT_ID ClientId;
			PVOID ActiveRpcHandle;
			PVOID ThreadLocalStoragePointer;
			struct PEB* ProcessEnvironmentBlock;
			//...
		};
