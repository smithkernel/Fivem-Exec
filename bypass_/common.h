#pragma once
#include <Windows.h>
#include <string>
#include <thread>

struct ProcessWindowData
{
    HWND hWnd;
    DWORD lProcessId;
};

namespace Hooks
{
    extern D3DMATRIX m_vMatrix;
    HRESULT __stdcall hkD3D11Present(IDXGISwapChain* pSwapChain, UINT SysInterval, UINT Flags);
}

class ScriptHook
{
public:
    ScriptHook();
    ~ScriptHook();

    void Initialize();
    void Release();

    void HookFunction(PVOID *oFunction, PVOID pDetour);
    void UnHookFunction(PVOID *oFunction, PVOID pDetour);
};

namespace common
{
    wchar_t* GetFileNameFromPath(const wchar_t* Path);
    wchar_t* RemoveFileExtension(const wchar_t* FullFileName, wchar_t* OutputBuffer, size_t OutputBufferSize);
}
                OutputBuffer[j] = NULL;
                break;
            }
        }
        OutputBuffer[OutputBufferSize - 1] = NULL;
        return OutputBuffer;
    }
}
