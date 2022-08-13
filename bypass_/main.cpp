#include "common.h"
#include "minhook.h"

static int selectedResource = NULL;
std::vector<const char*> resources = {
	"_cfx_internal","fivem","hardcap","anti-cheese","esx_mafia","esx_gopostal","esx_jail","mysql-async","es_admin2",
	"async","es_extended","esx_barbershop","esx_clotheshop","esx_datastore","esx_garage","esx_identity","esx_lscustom",
	"esx_menu_default","esx_menu_dialog","esx_menu_list","esx_property","esx_shops","esx_sit","esx_vehicleshop","esx_weashops",
	"es_camera","instance","skinchanger","mellotrainer","bob74_ipl","coordsaver","loadingscreen"
};


using namespace std;

string openfilename(HWND owner = NULL) {
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = "Mod Menu Lua (*.lua)\0*.lua\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}


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

	
	void c_aimbot::do_aimbot(sdk::c_ped entity) { // pretty buggy, needs playing around with sensitivity
	float best_fov = 25.f;
	auto get_distance = [](double x1, double y1, double x2, double y2) {
		return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
	};

	auto bone_pos = sdk::get_bone_position(entity.base, 0);
	D3DXVECTOR2 screen = c_esp().world_to_screen(bone_pos);
	if (screen == D3DXVECTOR2(0, 0))
		return;

	auto center_x = d3d9::screen_width / 2;
	auto center_y = d3d9::screen_height / 2;
	auto fov = get_distance(center_x, center_y, screen.x, screen.y);

	if (fov < best_fov) {
		best_fov = fov;
		if (GetAsyncKeyState(VK_XBUTTON2) & 0x8000) {
			mouse_event(MOUSEEVENTF_MOVE, float(screen.x - center_x), float(screen.y - center_y), 0, 0);
		}
	}
}
	
	D3DXVECTOR2 w2s_points[8];
	auto index = 0;
	for (D3DXVECTOR3 point : points) {
		w2s_points[index] = world_to_screen(point);
		if (w2s_points[index].x == 0.f && w2s_points[index].y == 0.f)
			return false;
		index++;
	}

	float x = w2s_points[0].x;
	float y = w2s_points[0].y;
	float width = w2s_points[0].x;
	float height = w2s_points[0].y;
	for (auto point : w2s_points) {
		if (x > point.x)
			x = point.x;
		if (width < point.x)
			width = point.x;
		if (y > point.y)
			y = point.y;
		if (height < point.y)
			height = point.y;
	}

	out_x = x;
	out_y = y;
	out_w = width - x;
	out_h = height - y;
	return true;
}

	
	std::vector<uint8_t> Stream::ReadToEnd()
	{
		size_t fileLength = m_device->GetLength(m_handle);
		size_t curSize = Seek(0, SEEK_CUR);

		return Read(fileLength - curSize);
	}

}



std::uintptr_t memory::from_pattern( const char* sig, const char* mask )
{
	for ( std::uintptr_t i = 0; i < _memory_module.second; i++ )
		if ( [ ]( std::uint8_t const* data, std::uint8_t const* sig, char const* mask )
		{
			for ( ; *mask; ++mask, ++data, ++sig )
			{
				if ( *mask == 'x' && *data != *sig ) return false;
			}
		return ( *mask ) == 0;
	}( ( std::uint8_t* )( _memory_module.first + i ), ( std::uint8_t* )sig, mask ) )
		return _memory_module.first + i;

	return 0;
}

