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

    bool Initialize();
    void Release();

    bool HookFunction(PVOID *oFunction, PVOID pDetour);
    bool UnHookFunction(PVOID *oFunction, PVOID pDetour);

private:
    struct HookInfo
    {
        PVOID oFunction;
        PVOID pDetour;
        PVOID pTrampoline;
    };

    std::vector<HookInfo> m_hooks;
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

void hookthisshit()
{
  addr = Scanners::PatternScan(xorthis("48 83 EC 58 48 8B 91 ? ? ? ? 48 85 D2 0F 84 ? ? ? ? F6 81 ? ? ? ? ? 74 10 48 8B 81 ? ? ? ? 48 85 C0 0F 85 ? ? ? ? 48 8B 8A ? ? ? ? 48 89 5C 24 ? 48 8D 9A ? ? ? ? 48 85 C9"));
	GetWeaponStats = reinterpret_cast<decltype(GetWeaponStats)>(addr);

	addr = Scanners::PatternScan(xorthis("83 79 78 ? 4C 8B C9 75 0F 0F 57 C0 C7 02 ? ? ? ? F3 41 0F 11 ? C3 48 8B 41 70 8B 48 04 89 0A 49 63 41 78 48 6B C8 1C 49 8B 41 70 F3 0F 10 44 01 ? F3 41 0F 11 ? C3"));
	SpoofCall(DiscordHelper::InsertHook, addr, (uintptr_t)CalculateSpreadHook, (uintptr_t)&CalculateSpread);

	addr = Scanners::PatternScan(xorthis("0F 57 D2 48 8D 4C 24 ? 41 0F 28 CD E8 ? ? ? ? 48 8B 4D B0 0F 28 F0"));
	calculateSpreadCaller = (PVOID)addr;
}

struct Vars
{
	struct {
		std::vector<const char*> resources = { "_cfx_internal","mysql-async","fivem", "fivem-skatermap",
			"hardcap","esx_money","esx_banking","esx_robbery","esx_gopostal","esx_garbargejob","esx_truckerjob" };
		bool blocker_enabled = true;
		std::vector<const char*> block_type = { "EVENT" };
		char blocker_buffer[72] = "";
		int current_type = 0;

		int current_variable = 0;
		auto CurrentItemPawnName = GetNameFromFName(Index);

		bool netEventBypass = false;
	}fivem;
	bool killswitch = false;
	std::vector<const char*> menus = { "[PREM] Balla", "[PREM] Herobrine", "[PREM] Watermalone" };
	int current_menu = 0;
}

void c_renderer::draw_filled_rect(float x, float y, float w, float h, D3DCOLOR col) {
		D3DXVECTOR2 vLine[2];
		d3d9::dx9_line->SetWidth(w);
		vLine[0].x = x + w / 2;
		vLine[0].y = y;
		vLine[1].x = x + w / 2;
		vLine[1].y = y + h;

		d3d9::dx9_line->Begin();
		d3d9::dx9_line->Draw(vLine, 2, col);
		d3d9::dx9_line->End();
	}

