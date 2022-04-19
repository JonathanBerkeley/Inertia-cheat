// ReSharper disable CppClangTidyPerformanceNoIntToPtr
#include "pch.hpp"
#include "flashpoint.hpp"
#include "constants.hpp"
#include "data.hpp"
#include "memory.hpp"

using namespace data;


/**
 * \brief Entry point for the cheat logic
 * \param lpParam Dummy parameter
 */
DWORD WINAPI Init(LPVOID lpParam) {
    LogicLoop();

    return DWORD{};
}


/**
 * \brief Enumerate a processes windows and set them to supplied string
 * \param lpString String to set names to
 */
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


/**
 * \brief Uninject this module from the game
 */
[[noreturn]]
void Uninject() {
    RenameWindows(L"Inertia");
    
    FreeLibraryAndExitThread(proc::self_module, 0x0);
}


#pragma region Player
struct Player {
    std::int32_t* health{};
    std::int32_t* ammo{};
};


/**
 * \brief Try to get main Player object
 * \return Populated Player object on success, std::nullopt on failure
 */
std::optional<Player> GetPlayer() {
    auto start_point = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("UnityPlayer.dll"));
    start_point += 0x13A1340;
    const auto health_ptr = TraverseChain(start_point, { 0xC2C, 0xDC8, 0xEA8, 0x18, 0x38 }).value_or(0u);

    if (!health_ptr)
        return std::nullopt;

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

    // Main Logic Loop
    while (running) {

        if (GetAsyncKeyState(input::HK_UNLOAD) & 1)
            Uninject();

        const auto [health, ammo]{ GetPlayer().value_or(Player{}) };

        if (!health || !ammo) {
            Sleep(3);
            continue;
        }

        if (PointerIsValid(health)) {
            *health = 100;
            *ammo = 100;
        }

        Sleep(3);
    }
}
