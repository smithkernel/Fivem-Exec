#include "common.h"
#include "minhook.h"

typedef HANDLE(APIENTRY* LPFN_CREATEFILEW)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

LPFN_CREATEFILEW g_CreateFileW;

bool intialized{ false };

HANDLE WINAPI CreateFileHook(LPCWSTR fileName, DWORD desiredAccess, DWORD shareMode, LPSECURITY_ATTRIBUTES pSecurityAttributes, DWORD creationDisposition, DWORD flagsAndAttributes, HANDLE hTemplateFile)
{
	if (!intialized)
	{
		if (wcsstr(fileName, (L"graph.lua")))
		{
			std::wstring targetPath = std::wstring(L"C:").
				append(L"\\").
				append(L"test").
				append(L"\\").
				append(L"test.lua");

			MessageBoxA(NULL, "Executed", "Info", NULL);

			intialized = true;

			return g_CreateFileW(targetPath.c_str(), desiredAccess, shareMode, pSecurityAttributes, creationDisposition, flagsAndAttributes, hTemplateFile);
		}
	}

	return g_CreateFileW(fileName, desiredAccess, shareMode, pSecurityAttributes, creationDisposition, flagsAndAttributes, hTemplateFile);
}

}

typedef HMODULE(WINAPI* LPFN_LOADLIBRARYW)(LPCWSTR);
{
    LPFN_LOADLIBRARYW g_LoadLibraryW;
    {
        g_LoadLibraryW = (LPFN_LOADLIBRARYW)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "LoadLibraryW");
        MH_Initialize();
        MH_CreateHook(g_LoadLibraryW, CreateFileHook, (void**)&g_LoadLibraryW);
        MH_EnableHook(g_LoadLibraryW);
        {
            HMODULE hModule = g_LoadLibraryW(L"graph.lua");
            if (hModule)
            {
                MessageBoxA(NULL, "Executed", "Info", NULL);
            }

        Process::Initialize();("C:\\test\\test.lua");
        injector::MakeCALL(0x00401000, (uintptr_t)CreateFileHook, true);

    }
}
	
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		if (!FindWindow(L"grcWindow", nullptr))
			return true;

		MessageBoxA(NULL, "Injected", "Info", NULL);

		MH_Initialize();
		MH_CreateHook(CreateFileW, CreateFileHook, &reinterpret_cast<PVOID&>(g_CreateFileW));
		MH_EnableHook(CreateFileW);
	}
	return true;
	}

	return true;
}
