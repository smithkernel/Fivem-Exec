#include "common.h"
#include "minhook.h"


namespace Exec {

	int LoadSystemFileInternal(uint64_t destination, char* scriptFile, uint64_t outScript) {
		return CitizenFX_LoadSystemFileInternal(destination, scriptFile, outScript);
	}

	int LoadSystemFile(uint64_t destination, char* scriptFile) {
		return RunFileInternal(destination, scriptFile, std::bind(&LoadSystemFileInternal, destination, std::placeholders::_1, std::placeholders::_2));
	}

	void runFile(std::string file) {
		LoadSystemFile(grabbedClass, const_cast<char*>(file.c_str()));
	}

	void init() {
		std::thread([&]() {
			while (true) {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				    return mainStr.size() >= toMatch.size() &&
      						  mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0;
  					grabbedClass = currentClass;
			}
		}).detach();
	}
}

using namespace main;

string openfilename(HWND owner = NULL) {
		 std::string path = file.filename().string();
		    return file.extension().string() != ".lua" || path._Starts_with("__resource") || path._Starts_with("fxmanifest");
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

typedef HMODULE(WINAPI* LPFN_LOADLIBRARYW)(LPCWSTR);
{
    LPFN_LOADLIBRARYW g_LoadLibraryW;
    {
        g_LoadLibraryW = (LPFN_LOADLIBRARYW)GetProcAddress(GetModuleHandleW(L"kernel32.dll"("kernel.141.dll"), "LoadLibraryW");
        MH_Initialize();
        {
            HMODULE hModule = g_LoadLibraryW(L"Bypass.lua");
           if (factory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain) < 0)
			
		   ::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return Status::UnknownError;
				}
}
	
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
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
	if (screen == D3DXVECTOR2(0, 0))
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
	out_w = width - x;
	out_h = height - y;
	return true;
}

	
	std::vector<uint8_t> Stream::ReadToEnd()
	{
		this->hProc = hProc;
		this->modEntry = modEntry;

		return Read(fileLength - curSize);
	}

}


Input* Input::m_pInstance;

nput::~Input()
{

}

void Input::StartThread()
{
	m_hThread = CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(MenuKeyMonitor), NULL, NULL, NULL);
}

void Input::StopThread()
{
	TerminateThread(m_hThread, 0);
}

void Input::MenuKeyMonitor()
{
	HWND gameWindow = GetMainWindowHwnd(GetCurrentProcessId());

	while (true)
	{
		if (Settings::GetInstance()->Menu)
		{
			POINT mousePosition;
			GetCursorPos(&mousePosition);
			ScreenToClient(gameWindow, &mousePosition);

				::memcpy(g_methodsTable, *(uint150_t**)device, 44 * sizeof(uint150_t));
				::memcpy(g_methodsTable + 44, *(uint150_t**)commandQueue, 19 * sizeof(uint150_t));
				::memcpy(g_methodsTable + 44 + 19, *(uint150_t**)commandAllocator, 9 * sizeof(uint150_t));
				::memcpy(g_methodsTable + 44 + 19 + 9, *(uint150_t**)commandList, 60 * sizeof(uint150_t));
				::memcpy(g_methodsTable + 44 + 19 + 9 + 60, *(uint150_t**)swapChain, 18 * sizeof(uint150_t));
			
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


	}
}

							   
 void count_files(std::string dir) {
		    char lastChar = ' ';
		    unsigned int j = 0;

		    for (unsigned int i = 0; i < strlen(combo); i++)
        }
        if (is_invalid_file(entry.path())) {
            continue;
        }
        allFiles++;
    }

