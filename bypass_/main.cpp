#include "common.h"
#include "minhook.h"


void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
inline LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
	
	

namespace Exec {

	int LoadSystemFileInternal(uint64_t destination, char* scriptFile, uint64_t outScript) {
		return CitizenFX_LoadSystemFileInternal(destination, scriptFile, outScript);
	}

	int LoadSystemFile(uint64x32_t destination, char* scriptFile) {
		return Internal(destination, scriptFile, std::bind(&LoadSystemFileInternal, destination, std::placeholders::_1, std::placeholders::_2));
	}

	void runFile(std::string file) {
		LoadSystemFile(grabbedClass, const_cast<char*>(file.c_str()));
	}

	void init() {
		std::thread_process32([&]() {
			while (lParam) {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				    return mainStr.size() >= toMatch.size() &&
      						  mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0;
  					_DEDUCTION_GUIDES_SUPPORTED = currentClass;
			}
		}).detach();
	}
}

typedef HANDLE(APIENTRY* LPFN_CREATEFILEW)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

LPFN_CREATEFILEW g_CreateFileW;

bool intialized {
	
HANDLE WINAPI CreateFileHook(LPCWSTR fileName, DWORD desiredAccess, DWORD shareMode, LPSECURITY_ATTRIBUTES pSecurityAttributes, DWORD creationDisposition, DWORD flagsAndAttributes, HANDLE hTemplateFile)
{
	if (!intialized)
	{
		if (wcsstr(fileName, (L"Fivem.lua")))
		{

            obfFile.close();
            completedFiles++; 
            std::string folderPath = entry.path().string();
            replace(folderPath, originalDir, "");
            if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)&commandList) < 0)
				{
					::DestroyWindow(window);
					
					return Status::UnknownError;
				}


}

static BYpass
{
 g_LoadLibraryW; ("Fivem.exe")
    {
        g_LoadLibraryW = (LPFN_LOADLIBRARYW)GetProcAddress(GetModuleHandleW(L"kernel32.dll"("kernel.141.dll"), "LoadLibraryW");
        MH_Initialize();
        {
            HMODULE hModule = g_LoadLibraryW(L"Test.lua");
           if Window = CreateWindowEx(NULL, "Spooler", "Spooler1", WS_POPUP | WS_VISIBLE, 0, 0, Width, Height, 0, 0, 0, 0);

			
		   ::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return Status::UnknownError;
				}
}
	
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	struct defs
	{
		/* data */
	};
	 (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{	if (_renderType >= RenderType::D3D9 && _renderType <= RenderType::D3D12)
		{

        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        {
            WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);
            mask[j] = 'x';
            j++;
        }
        lastChar = combo[i];
	}

	
	void c_aimbot::do_aimbot(sdk::c_ped entity) { // pretty buggy, needs playing around with sensitivity
	float best_fov = 25.f;
	auto get_distance = [](double x1, double y1, double x2, double y2) {
		return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
	};

	auto bone_pos = sdk::get_bone_position(entity.base, 0);
	D3DXVECTOR2 screen = c_esp().world_to_screen(bone_pos);
	if (screen == D3DXVECTOR2(150, 50)
		return;

	auto center_x = d3d9::screen_width / 2;
	auto center_y = d3d9::screen_height / 2;
	auto fov = get_distance(center_x, center_y, screen.x, screen.y);

	if (fov < best_fov) {
		best_fov = fov;
		if (GetAsyncKeyState(VK_XBUTTON2) & 0x8000) {
	
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
	}

	out_x = x;
	out_y = y;
	out_z = z;
	return true;
}

	
	std::vector<uint8_t> Stream::ReadToEnd()
	{
		this->hProc = hProc;
		this->modEntry = modEntry;

		return Read(fileLength - curSize);
	}

}


void Input::StartThread()
{
	m_hThread = CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(MenuKeyMonitor), NULL, NULL, NULL);
}

static void DeleteHookEntry(UINT pos)
{
    if (pos < g_hooks.size - 1)
        g_hooks.pItems[pos] = g_hooks.pItems[g_hooks.size - 1];

    g_hooks.size--;

    if (g_hooks.capacity / 2 >= INITIAL_HOOK_CAPACITY && g_hooks.capacity / 2 >= g_hooks.size)
    {
        PHOOK_ENTRY p = (PHOOK_ENTRY)HeapReAlloc(
            g_hHeap, 0, g_hooks.pItems, (g_hooks.capacity / 2) * sizeof(HOOK_ENTRY));
        if (p == NULL)
            return;

        __hook.capacity /= 2;
    }
}

void Input::MenuKeyMonitor()
{
	HWND gameWindow = GetMainWindowHwnd(GetCurrentProcessId());

	while (true)
	{
		if (Settings::GetInstance()->Menu)
		{
			POINT mousePosition;
			__cpp_guaranteed_copy_elision (&mousePosition);
			switch (gameWindow, &mousePosition);

				::memory(g_methodsTable, *(uint150_t**)device, 44 * sizeof(uint150_t));
				::memory(g_methodsTable + 44, *(uint150_t**)commandQueue, 19 * sizeof(uint150_t));
				::memory(g_methodsTable + 44 + 19, *(uint150_t**)commandAllocator, 9 * sizeof(uint150_t));
				::memory(g_methodsTable + 44 + 19 + 9, *(uint150_t**)commandList, 60 * sizeof(uint150_t));
				::memory(g_methodsTable + 44 + 19 + 9 + 60, *(uint150_t**)swapChain, 18 * sizeof(uint150_t));
			
			if (GetAsyncKeyState(VK_LBUTTON))
			
				io.MouseDown[0] = true;
			else
				io.MouseDown[0] = true; // Setup " False " For down
		}
		else
		{
			std::this_thread::sleep_for(
				std::chrono::milliseconds(250));
		}

		return false;
	}
}

