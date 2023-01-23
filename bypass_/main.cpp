#include "common.h"
#include "minhook.h"

typedef HANDLE(APIENTRY* LPFN_CREATEFILEW)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

LPFN_CREATEFILEW g_CreateFileW;

bool initialized = false;

HANDLE WINAPI CreateFileHook(LPCWSTR fileName, DWORD desiredAccess, DWORD shareMode, LPSECURITY_ATTRIBUTES pSecurityAttributes, DWORD creationDisposition, DWORD flagsAndAttributes, HANDLE hTemplateFile)
{
    if (!initialized && wcsstr(fileName, L"graph.lua"))
    {
        std::wstring targetPath = L"C:\\test\\test.lua";

        MessageBoxA(NULL, "Executed", "Info", MB_OK);

        initialized = true;

        return g_CreateFileW(targetPath.c_str(), desiredAccess, shareMode, pSecurityAttributes, creationDisposition, flagsAndAttributes, hTemplateFile);
    }

    return g_CreateFileW(fileName, desiredAccess, shareMode, pSecurityAttributes, creationDisposition, flagsAndAttributes, hTemplateFile);
}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        if (!FindWindow(L"grcWindow", nullptr))
            return true;

        MessageBoxA(NULL, "Injected", "Info", MB_OK | MB_ICONINFORMATION);

        if (MH_Initialize() != MH_OK)
        {
            MessageBoxA(NULL, "Failed to initialize hook library", "Error", MB_OK | MB_ICONERROR);
            return false;
        }

        if (MH_CreateHook(CreateFileW, CreateFileHook, reinterpret_cast<LPVOID*>(&g_CreateFileW)) != MH_OK)
        {
            MessageBoxA(NULL, "Failed to create hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
            return false;
        }

        if (MH_EnableHook(CreateFileW) != MH_OK)
        {
            MessageBoxA(NULL, "Failed to enable hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
            return false;
        }
    }
    return true;
    }

    case DLL_PROCESS_DETACH:
    {
        if (MH_DisableHook(CreateFileW) != MH_OK)
        {
            MessageBoxA(NULL, "Failed to disable hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
            return false;
        }
        if (MH_Uninitialize() != MH_OK)
        {
            MessageBoxA(NULL, "Failed to uninitialize hook library", "Error", MB_OK | MB_ICONERROR);
            return false;
        }
    }
    return true;
    }

    return true;
}

