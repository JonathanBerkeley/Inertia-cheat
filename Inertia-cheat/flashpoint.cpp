#include "pch.hpp"
#include "flashpoint.hpp"
#include "constants.hpp"
#include "data.hpp"
#include "memory.hpp"
#include "player.hpp"

using namespace data; // Data is a namespace wrapper


/**
 * \brief Entry point for the cheat logic
 * \param lpParam Dummy parameter
 */
DWORD WINAPI Init(LPVOID lpParam) {
    LogicLoop();

    // ReSharper disable once CppUnreachableCode
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


/**
 * \brief Check cheat hotkeys
 * \param cheat_enabled Cheat_enabled status to be toggled if hotkey pressed
 */
void CheckHotkeys(bool& cheat_enabled) {

    if (GetAsyncKeyState(input::HK_UNLOAD) & 1)
        Uninject();

    if (GetAsyncKeyState(input::HK_E) & 1) {
        cheat_enabled = !cheat_enabled;

        // Set title to reflect cheat status
        const auto new_title = std::wstring{
            constants::HIJACK_TEXT + (cheat_enabled ? L" [ON]" : L" [OFF]")
        };

        RenameWindows(new_title.c_str());
    }
}


/**
 * \brief Set player's health and ammo to 100
 * \return True on success, false on failure
 */
bool StatsHack() {
    const auto [health, ammo] { GetPlayer().value_or(Player{}) };

    if (!health || !ammo)
        return false;

    if (PointerIsValid(health)) {
        *health = 100;
        *ammo = 100;
        return true;
    }

    return false;
}


/**
 * \brief Main program loop of the module
 *
 * Does not return
 */
[[noreturn]]
void LogicLoop() {
    // Rename window to indicate cheat enabled
    RenameWindows(
        constants::HIJACK_TEXT.c_str()
    );

    bool cheat_enabled = true;

    // Main Logic Loop
    for (;;) {

        CheckHotkeys(cheat_enabled);

        if (cheat_enabled) {
            // Sleep on failure to do hack functionality
            if (!StatsHack()) {
                Sleep(2);
                continue;
            }
        }

        Sleep(2);
    }
}
