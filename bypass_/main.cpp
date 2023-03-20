#include "common.h"
#include "minhook.h"

// Define a function pointer type for CreateFileW
typedef HANDLE(WINAPI* LPFN_CREATEFILEW)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

// Declare a global variable to store the address of the original CreateFileW function
static LPFN_CREATEFILEW g_OrigCreateFileW = NULL;

// Define the hook function for CreateFileW
HANDLE WINAPI CreateFileHook(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                             DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    static const std::wstring targetPath = L"C:\\test\\test.lua";
    static bool initialized = false;

    // If the original CreateFileW function has not been obtained yet, get its address
    if (g_OrigCreateFileW == NULL)
    {
        HMODULE hModule = GetModuleHandleW(L"kernel32.dll");
        g_OrigCreateFileW = (LPFN_CREATEFILEW)GetProcAddress(hModule, "CreateFileW");
    }

    // If the requested file is "graph.lua" and the target file exists, redirect the access to the target file
    if (!initialized && _wcsicmp(lpFileName, L"graph.lua") == 0 && _waccess(targetPath.c_str(), 0) == 0)
    {
        lpFileName = targetPath.c_str();
        MessageBoxW(NULL, L"Original file access is being redirected to the target file", L"Info", MB_OK);
        initialized = true;
    }

    // Call the original CreateFileW function with the modified arguments
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


#include <Windows.h>
#include <MinHook.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            MH_Initialize();
            MH_CreateHookApi(L"kernel32", "CreateFileW", MyCreateFileW, reinterpret_cast<LPVOID*>(&OriginalCreateFileW));
            MH_CreateHookApi(L"kernel32", "CreateFileA", MyCreateFileA, reinterpret_cast<LPVOID*>(&OriginalCreateFileA));
            MH_EnableHook(MH_ALL_HOOKS);
            break;

        case DLL_PROCESS_DETACH:
            MH_DisableHook(MH_ALL_HOOKS);
            MH_Uninitialize();
            break;
    }

    return TRUE;
}


bool InitHooks() {
    MH_STATUS status;
    LPVOID pOrigCreateFileW = NULL, pOrigCreateFileA = NULL;

    status = MH_Initialize();
    if (status != MH_OK) {
        fprintf(stderr, "Failed to initialize MinHook: %s\n", MH_StatusToString(status));
        return false;
    }

    status = MH_CreateHook(&CreateFileW, &MyCreateFileW, &pOrigCreateFileW);
    if (status != MH_OK) {
        fprintf(stderr, "Failed to create hook for CreateFileW: %s\n", MH_StatusToString(status));
        goto cleanup;
    }

    status = MH_CreateHook(&CreateFileA, &MyCreateFileA, &pOrigCreateFileA);
    if (status != MH_OK) {
        fprintf(stderr, "Failed to create hook for CreateFileA: %s\n", MH_StatusToString(status));
        goto cleanup_remove_w;
    }

    status = MH_EnableHook(&CreateFileW);
    if (status != MH_OK) {
        fprintf(stderr, "Failed to enable hook for CreateFileW: %s\n", MH_StatusToString(status));
        goto cleanup_remove_a;
    }

    status = MH_EnableHook(&CreateFileA);
    if (status != MH_OK) {
        fprintf(stderr, "Failed to enable hook for CreateFileA: %s\n", MH_StatusToString(status));
        goto cleanup_remove_w;
    }

    return true;

cleanup_remove_a:
    MH_RemoveHook(&CreateFileA);
cleanup_remove_w:
    MH_RemoveHook(&CreateFileW);
cleanup:
    MH_Uninitialize();
    return false;
}


// Disable hooks and uninitialize MinHook library
void UninitHooks() {
    if (MH_DisableHook(&CreateFileW) != MH_OK) {
        // Error handling for disabling CreateFileW hook
        // Log or display an error message, and take appropriate action
    }
    if (MH_DisableHook(&CreateFileA) != MH_OK) {
        // Error handling for disabling CreateFileA hook
        // Log or display an error message, and take appropriate action
    }
    if (MH_Uninitialize() != MH_OK) {
        // Error handling for uninitializing MinHook library
        // Log or display an error message, and take appropriate action
    }
}

HANDLE WINAPI MyCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    // Do something before calling the original function
    HANDLE hFile = OrigCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    // Do something after calling the original function
    return hFile;
}

HANDLE WINAPI MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    // Do something before calling the original function
    HANDLE hFile = OrigCreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    // Do something after calling the original function
    return hFile;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            // Disable thread notifications to improve performance and security
            DisableThreadLibraryCalls(hinstDLL);
            // Zero out the lpReserved parameter
            ZeroMemory(lpReserved, sizeof(lpReserved));
            try {
                // Perform security checks to prevent DLL injection attacks
                if (!IsProcessRunningInsideWindowsExplorer()) {
                    return FALSE;
                }
                if (!VerifyLoadedModuleIsSigned()) {
                    return FALSE;
                }
                if (!VerifyLoadedModulePath()) {
                    return FALSE;
                }
                // Initialize hooks
                InitHooks();
            } catch (...) {
                // Handle exceptions thrown by InitHooks
                return FALSE;
            }
            break;
        case DLL_PROCESS_DETACH:
            try {
                // Uninitialize hooks
                UninitHooks();
            } catch (...) {
                // Handle exceptions thrown by UninitHooks
                return FALSE;
            }
            break;
        default:
            // Handle unexpected fdwReason values
            return FALSE;
    }
    // Perform security checks to prevent unauthorized loading or unloading of the DLL
    if (!VerifyUserIsAdmin()) {
        return FALSE;
    }
    // Return TRUE to indicate successful processing of the function call
    return TRUE;
}

