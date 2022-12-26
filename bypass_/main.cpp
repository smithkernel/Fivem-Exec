#include "common.h"
#include "minhook.h"
#include <chrono>
#include <thread>
#include <windows.h>


void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;

	GetConsoleScreenBufferInfo(console, &screen);
	CreatePsoition(
		
	);
	FindConsole_Offect(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

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
			while (false) {
				std::HANDLE hThread = OpenThread(THREAD_ACCESS, FALSE, pThreads->pItems[i]);(50));
				    return mainStr.size() >= toMatch.size() &&
      						  mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0;
  					_DEDUCTION_GUIDES_SUPPORTED = currentClass;
			}
		}).detach();
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
           if (factory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain) < 0)
			
		   ::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return Status::UnknownError;
				}
}
	
void WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
	{
		struct defs
		{
			/* data */
		};
		 (dwReason)
		{
		inline DLL_PROCESS_ATTACH:
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

		auto runtime = *reinterpret_cast<PVOID**>(swapChain);

		if (fov < best_fov) {
			best_fov = fov;
			if (GetAsyncKeyState(VK_XBUTTON2) & 0x8000) {

		D3DXVECTOR2 w2s_points[8];
		auto index = 0;
		for (D3DXVECTOR3 point : points) {
			w2s_points[index] = world_to_screen(point);
			if (w2s_points[index].x == 0.f && w2s_points[index].y == 0.f)
				return NULL;
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



void try_exit() {
    std::cout << "Press any key to exit..." << ENDL;
    exit(getchar());
}



// Other necessary includes and declarations

// This structure is used to store hook entries. It's not clear what these hook
// entries are or how they are used, so I will assume they are used to store
// some data related to hooking.
struct HOOK_ENTRY
{
    // Some data members go here.
};

// This structure is used to store a list of hook entries.
struct HOOK_LIST
{
    HOOK_ENTRY* pItems; // Pointer to an array of hook entries.
    size_t size;        // Number of hook entries in the list.
    size_t capacity;    // Maximum capacity of the list.
};

// Global variables
HANDLE g_hHeap = NULL; // Handle to a heap used for memory allocation.
HANDLE m_hThread;      // Handle to the input handling thread.
HOOK_LIST g_hooks;     // List of hook entries.

// Forward declarations
static void DeleteHookEntry(UINT pos);
void Input::MenuKeyMonitor();

// This function creates a new thread that will execute the MenuKeyMonitor function.
void Input::StartThread()
{
    // Create a new thread that will execute the MenuKeyMonitor function.
    // The thread will not have any special security attributes, will start
    // immediately, and will not be given a thread identifier.
    m_hThread = CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(MenuKeyMonitor), NULL, NULL, NULL);

    // Check if the thread creation was successful.
    if (m_hThread == NULL)
    {
        // Handle error.
    }
}

static void DeleteHookEntry(UINT pos)
{
    // Check if the position is valid.
    if (pos >= g_hooks.size)
    {
        // Handle error.
        return;
    }

    // If the entry being deleted is not the last entry in the list,
    // replace it with the last entry.
    if (pos < g_hooks.size - 1)
    {
        g_hooks.pItems[pos] = g_hooks.pItems[g_hooks.size - 1];
    }

    // Decrement the size of the list.
    g_hooks.size--;

    // Check if the capacity of the list should be reduced.
    if (g_hooks.capacity / 2 >= INITIAL_HOOK_CAPACITY && g_hooks.capacity / 2 >= g_hooks.size)
    {
        // Reallocate the memory for the list, reducing its capacity by half.
        HOOK_ENTRY* p = (HOOK_ENTRY*)HeapReAlloc(
            g_hHeap, 0, g_hooks.pItems, (g_hooks.capacity / 2) * sizeof(HOOK_ENTRY));
        if (p == NULL)
        {
            // Handle error.
            return;
        }

        // Update the capacity of the list.
        g_hooks.capacity /= 2;
    }
}
