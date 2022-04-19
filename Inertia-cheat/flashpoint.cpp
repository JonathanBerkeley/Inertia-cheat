// ReSharper disable CppClangTidyPerformanceNoIntToPtr
#include "pch.hpp"
#include "flashpoint.hpp"
#include "constants.hpp"
#include "data.hpp"
#include "memory.hpp"

using namespace data;


DWORD WINAPI Init(LPVOID lpParam) {
    LogicLoop();

    // ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
    return 0;
}


void RenameWindows(LPCWSTR lpString) {
    HWND window = nullptr;
    const auto pid = GetCurrentProcessId();
    do {
        window = FindWindowEx(
            nullptr,
            window,
            nullptr,
            nullptr
        );
        DWORD check_pid = 0;
        GetWindowThreadProcessId(window, &check_pid);

        if (check_pid == pid) SetWindowText(window, lpString);
    }
	while (window != nullptr);
}


[[noreturn]]
void Uninject() {
    RenameWindows(L"Inertia");
    // Uninject
    FreeLibraryAndExitThread(proc::self_module, 0x0);
}


#pragma region Player
struct Player {
    std::int32_t* health;
    std::int32_t* ammo;
};


Player GetPlayer() {
    auto start_point = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("UnityPlayer.dll"));
    start_point += 0x13A1340;
    const auto health_ptr = TraverseChain(start_point, { 0xC2C, 0xDC8, 0xEA8, 0x18, 0x38 }).value_or(0u);

    if (!health_ptr)
        Uninject();

    const auto ammo_ptr = health_ptr - 0x4;

    const Player player{
        .health = reinterpret_cast<std::int32_t*>(health_ptr),
        .ammo = reinterpret_cast<std::int32_t*>(ammo_ptr)
    };

    return player;
}
#pragma endregion


void LogicLoop() {
    // Rename window to indicate cheat enabled
    RenameWindows(
        constants::HIJACK_TEXT.c_str()
    );

    const auto [health, ammo] = GetPlayer();
    

    // Main Logic Loop
    while (running) {
        if (GetAsyncKeyState(input::HK_UNLOAD) & 1) {
            Uninject();
        }
        
        *health = std::numeric_limits<std::int32_t>::max();
        *ammo = std::numeric_limits<std::int32_t>::max();

        Sleep(3);
    }
}
