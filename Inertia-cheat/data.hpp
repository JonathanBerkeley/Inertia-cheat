#pragma once
#include "pch.hpp"


namespace data {

    struct PointerChain {
        std::uintptr_t start_point{};
        std::vector<std::uint32_t> ptr_chain{};
    };

    namespace proc {
        // Windows
        extern HMODULE self_module;
    }
    
    namespace input {
        // Hot-keys
        constexpr int8_t HK_UNLOAD = VK_END;

        constexpr int8_t HK_Q = 0x51;
        constexpr int8_t HK_E = 0x45;
    }

    namespace offsets {
        extern PointerChain player;
    }
}
