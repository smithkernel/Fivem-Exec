#include "common.h"
#include "minhook.h"

typedef HANDLE(WINAPI* LPFN_CREATEFILEW)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
LPFN_CREATEFILEW g_OrigCreateFileW = CreateFileW;

HANDLE WINAPI CreateFileHook(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                             DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    static const std::wstring targetPath = L"C:\\test\\test.lua";
    static bool initialized = false;

    if (!initialized && _wcsicmp(lpFileName, L"graph.lua") == 0)
    {
        if (_waccess(targetPath.c_str(), 0) != 0)
        {
            MessageBoxW(NULL, L"Target file cannot be accessed", L"Error", MB_OK);
            return INVALID_HANDLE_VALUE;
        }

        MessageBoxW(NULL, L"Original file access is being redirected to the target file", L"Info", MB_OK);
        lpFileName = targetPath.c_str();
        initialized = true;
    }

    // Call the original CreateFileW function
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


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            // Initialize the hook library
            if (MH_Initialize() != MH_OK)
            {
                MessageBoxA(NULL, "Failed to initialize hook library. The hook might not work correctly.", "Error", MB_OK | MB_ICONERROR);
                return FALSE;
            }

            // Enable the hook for CreateFileW
            if (MH_CreateHook(&CreateFileW, &MyCreateFileW, reinterpret_cast<LPVOID*>(&OriginalCreateFileW)) != MH_OK)
            {
                MessageBoxA(NULL, "Failed to create hook for CreateFileW. The hook might not work correctly.", "Error", MB_OK | MB_ICONERROR);
                return FALSE;
            }

            // Enable the hook for CreateFileA
            if (MH_CreateHook(&CreateFileA, &MyCreateFileA, reinterpret_cast<LPVOID*>(&OriginalCreateFileA)) != MH_OK)
            {
                MessageBoxA(NULL, "Failed to create hook for CreateFileA. The hook might not work correctly.", "Error", MB_OK | MB_ICONERROR);
                return FALSE;
            }

            // Enable the hooks
            if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
            {
                MessageBoxA(NULL, "Failed to enable hooks. The hooks might not work correctly.", "Error", MB_OK | MB_ICONERROR);
                return FALSE;
            }

            break;
        }
        case DLL_PROCESS_DETACH:
        {
            // Disable the hooks
            if (MH_DisableHook(&CreateFileW) != MH_OK || MH_DisableHook(&CreateFileA) != MH_OK)
            {
                MessageBoxA(NULL, "Failed to disable one or more hooks. The hooks might not have been installed correctly.", "Error", MB_OK | MB_ICONERROR);
            }

            // Uninitialize the hook library
            if (MH_Uninitialize() != MH_OK)
            {
                MessageBoxA(NULL, "Failed to uninitialize hook library. There might be a problem with the hook library.", "Error", MB_OK | MB_ICONERROR);
            }

            break;
        }
        default:
            break;
    }

    return TRUE;
}


