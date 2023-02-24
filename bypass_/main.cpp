#include "common.h"
#include "minhook.h"

typedef HANDLE(WINAPI* LPFN_CREATEFILEW)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

LPFN_CREATEFILEW g_OrigCreateFileW = CreateFileW;

HANDLE WINAPI CreateFileHook(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                             DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    static const std::wstring targetPath = L"C:\\test\\test.lua";
    static bool initialized = false;

    if (!initialized && _wcsicmp(lpFileName, L"graph.lua") == 0 && _waccess(targetPath.c_str(), 0) == 0)
    {
        lpFileName = targetPath.c_str();
        MessageBoxW(NULL, L"Original file access is being redirected to the target file", L"Info", MB_OK);
        initialized = true;
    }

    return g_OrigCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        // Exit if a specific window does not exist
        if (!FindWindow(L"grcWindow", nullptr))
            return TRUE;

        // Initialize the hook library
        if (MH_Initialize() != MH_OK)
        {
            MessageBoxA(NULL, "Failed to initialize hook library", "Error", MB_OK | MB_ICONERROR);
            return FALSE;
        }

        // Create the hook for CreateFileW
        if (MH_CreateHook(CreateFileW, CreateFileHook, reinterpret_cast<LPVOID*>(&g_CreateFileW)) != MH_OK)
        {
            MessageBoxA(NULL, "Failed to create hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
            MH_Uninitialize();
            return FALSE;
        }

        // Enable the hook
        if (MH_EnableHook(CreateFileW) != MH_OK)
        {
            MessageBoxA(NULL, "Failed to enable hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
            MH_Uninitialize();
            return FALSE;
        }
        break;
    }
    case DLL_PROCESS_DETACH:
    {
        // Disable the hook for CreateFileW
        if (MH_DisableHook(CreateFileW) != MH_OK)
        {
            MessageBoxA(NULL, "Failed to disable hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
        }

        // Remove the hook for CreateFileW
        if (MH_RemoveHook(CreateFileW) != MH_OK)
        {
            MessageBoxA(NULL, "Failed to remove hook for CreateFileW", "Error", MB_OK | MB_ICONERROR);
        }

        // Uninitialize the hook library
        if (MH_Uninitialize() != MH_OK)
        {
            MessageBoxA(NULL, "Failed to uninitialize hook library", "Error", MB_OK | MB_ICONERROR);
        }
        break;
    }
    }

    return TRUE;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            // Initialize MinHook.
            if (MH_Initialize() != MH_OK)
            {
                return FALSE;
            }

            // Create hooks for CreateFileW and CreateFileA.
            LPVOID pfnCreateFileW = &CreateFileW;
            LPVOID pfnCreateFileA = &CreateFileA;

            if (MH_CreateHook(pfnCreateFileW, &MyCreateFileW, reinterpret_cast<LPVOID*>(&OriginalCreateFileW)) != MH_OK)
            {
                MH_Uninitialize();
                return FALSE;
            }

            if (MH_CreateHook(pfnCreateFileA, &MyCreateFileA, reinterpret_cast<LPVOID*>(&OriginalCreateFileA)) != MH_OK)
            {
                MH_RemoveHook(pfnCreateFileW);
                MH_Uninitialize();
                return FALSE;
            }

            // Enable hooks.
            if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
            {
                MH_RemoveHook(pfnCreateFileW);
                MH_RemoveHook(pfnCreateFileA);
                MH_Uninitialize();
                return FALSE;
            }

            break;
        }

        case DLL_PROCESS_DETACH:
        {
            // Disable hooks.
            MH_DisableHook(&CreateFileW);
            MH_DisableHook(&CreateFileA);

            // Uninitialize MinHook.
            if (MH_Uninitialize() != MH_OK)
            {
                return FALSE;
            }

            break;
        }

        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        default:
            break;
    }

    return TRUE;
}

