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
                MH_RemoveHook(reinterpret_cast<LPVOID>(OriginalCreateFileW));
                MH_Uninitialize();
                return FALSE;
            }

            // Enable hooks.
            if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
            {
                MH_RemoveHook(reinterpret_cast<LPVOID>(OriginalCreateFileW));
                MH_RemoveHook(reinterpret_cast<LPVOID>(OriginalCreateFileA));
                MH_Uninitialize();
                return FALSE;
            }

            break;
        }
        case DLL_PROCESS_DETACH:
        {
            // Disable and remove hooks.
            if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
            {
                return FALSE;
            }

            if (MH_RemoveHook(reinterpret_cast<LPVOID>(OriginalCreateFileW)) != MH_OK)
            {
                return FALSE;
            }

            if (MH_RemoveHook(reinterpret_cast<LPVOID>(OriginalCreateFileA)) != MH_OK)
            {
                return FALSE;
            }

            // Uninitialize MinHook.
            if (MH_Uninitialize() != MH_OK)
            {
                return FALSE;
            }

            break;
        }
        default:
        {
            break;
        }
    }

    return TRUE;
}

bool InitHooks() {
    MH_STATUS status;

    status = MH_Initialize();
    if (status != MH_OK) {
        fprintf(stderr, "Failed to initialize MinHook: %s\n", MH_StatusToString(status));
        return false;
    }

    LPVOID pOrigCreateFileW, pOrigCreateFileA;
    status = MH_CreateHook(&CreateFileW, &MyCreateFileW, &pOrigCreateFileW);
    if (status != MH_OK) {
        fprintf(stderr, "Failed to create hook for CreateFileW: %s\n", MH_StatusToString(status));
        MH_Uninitialize();  // Uninitialize MinHook on error
        return false;
    }

    status = MH_CreateHook(&CreateFileA, &MyCreateFileA, &pOrigCreateFileA);
    if (status != MH_OK) {
        fprintf(stderr, "Failed to create hook for CreateFileA: %s\n", MH_StatusToString(status));
        MH_RemoveHook(&CreateFileW);  // Remove previously created hook
        MH_Uninitialize();  // Uninitialize MinHook on error
        return false;
    }

    status = MH_EnableHook(&CreateFileW);
    if (status != MH_OK) {
        fprintf(stderr, "Failed to enable hook for CreateFileW: %s\n", MH_StatusToString(status));
        MH_RemoveHook(&CreateFileA);  // Remove previously created hooks
        MH_RemoveHook(&CreateFileW);
        MH_Uninitialize();  // Uninitialize MinHook on error
        return false;
    }

    status = MH_EnableHook(&CreateFileA);
    if (status != MH_OK) {
        fprintf(stderr, "Failed to enable hook for CreateFileA: %s\n", MH_StatusToString(status));
        MH_RemoveHook(&CreateFileA);
        MH_RemoveHook(&CreateFileW);
        MH_Uninitialize();  // Uninitialize MinHook on error
        return false;
    }

    return true;
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
            InitHooks();
            break;
        case DLL_PROCESS_DETACH:
            UninitHooks();
            break;
    }
    return TRUE;
}
