#include "common.h"
#include "minhook.h"

typedef HANDLE(WINAPI* LPFN_CREATEFILEW)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
LPFN_CREATEFILEW g_OrigCreateFileW = CreateFileW;

HANDLE WINAPI CreateFileHook(LPCWSTR fileName, DWORD desiredAccess, DWORD shareMode, LPSECURITY_ATTRIBUTES pSecurityAttributes, DWORD creationDisposition, DWORD flagsAndAttributes, HANDLE hTemplateFile)
{
    static const std::wstring targetPath = L"C:\\test\\test.lua";
    static bool initialized = false;

    if (!initialized && _wcsicmp(fileName, L"graph.lua") == 0)
    {
        if (_waccess(targetPath.c_str(), 0) == -1)
            return INVALID_HANDLE_VALUE;

        MessageBoxW(NULL, L"Original file access is redirecting to the target file", L"Info", MB_OK);
        fileName = targetPath.c_str();
        initialized = true;
    }
    return g_OrigCreateFileW(fileName, desiredAccess, shareMode, pSecurityAttributes, creationDisposition, flagsAndAttributes, hTemplateFile);
}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        // Exit if a specific window does not exist
        if (!FindWindow(L"grcWindow", nullptr))
            return true;

        // Initialize the hook library
        if (MH_Initialize() != MH_OK)
        {
            MessageBoxA(NULL, "Failed to initialize hook library", "Error", MB_OK | MB_ICONERROR);
            return false;
        }

        // Create the hook for CreateFileW
        if (MH_CreateHook(CreateFileW, CreateFileHook, reinterpret_cast<LPVOID*>(&g_CreateFileW)) != MH_OK)
        {
            MessageBoxA(NULL, "Failed to create hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
            MH_Uninitialize();
            return false;
        }

        // Enable the hook
        if (MH_EnableHook(CreateFileW) != MH_OK)
        {
            MessageBoxA(NULL, "Failed to enable hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
            MH_Uninitialize();
            return false;
        }
    }
    return true;
    }

    // Set the hook for CreateFileW
    if (MH_CreateHook(&CreateFileW, &CreateFileWHook, (LPVOID*)&pCreateFileW) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to set hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    // Enable the hook
    if (MH_EnableHook(&CreateFileW) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to enable hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }
}
break;

case DLL_PROCESS_DETACH:
{
    // Disable the hook
    if (MH_DisableHook(&CreateFileW) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to disable hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
    }
    else
    {
        // Uninitialize the hook library
        if (MH_Uninitialize() != MH_OK)
        {
            MessageBoxA(NULL, "Failed to uninitialize hook library", "Error", MB_OK | MB_ICONERROR);
        }
    }
}
break;

return TRUE;
