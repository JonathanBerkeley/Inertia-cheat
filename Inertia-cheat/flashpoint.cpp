#include "pch.hpp"
#include "flashpoint.hpp"
#include "constants.hpp"
#include "data.hpp"

#include <vector>

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


void LogicLoop() {
    // Rename window to indicate cheat enabled
    RenameWindows(
        constants::HIJACK_TEXT.c_str()
    );

    // Main Logic Loop
    while (running) {
        if (GetAsyncKeyState(input::HK_UNLOAD) & 1) {
            // Uninject
            FreeLibraryAndExitThread(proc::self_module, 0x0);
        }

        Sleep(1);
    }
}
