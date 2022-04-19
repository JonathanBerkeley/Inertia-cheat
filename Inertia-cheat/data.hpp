#pragma once
#include "pch.hpp"

namespace data {
    // Used for looping, setting to false will deactivate continued module functionality
    extern bool running;

    namespace proc {
        // Windows
        extern HMODULE self_module;
    }
    
    namespace input {
        // Hot-keys
        constexpr int8_t HK_MENU = VK_INSERT;
        constexpr int8_t HK_UNLOAD = VK_END;

        constexpr int8_t HK_Q = 0x51;
        constexpr int8_t HK_E = 0x45;
        constexpr int8_t HK_R = 0x52;
    }

    namespace offset {
    }
}
