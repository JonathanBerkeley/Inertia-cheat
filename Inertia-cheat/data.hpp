#pragma once
#include "pch.hpp"


namespace data {

    /**
     * \brief Represents a chain of pointers that begins at start_point and can be navigated by ptr_chain
     */
    struct PointerChain {
        std::uintptr_t start_point{};
        std::vector<std::uint32_t> ptr_chain{};
    };

    /**
     * \brief Contains details of this process
     */
    namespace proc {
        // Windows
        extern HMODULE self_module;
    }
    
    /**
     * \brief Keys that can be used to interact with cheat functionality
     */
    namespace input {
        // Hot-keys
        constexpr int8_t HK_UNLOAD = VK_END;

        constexpr int8_t HK_Q = 0x51;
        constexpr int8_t HK_E = 0x45;
    }

    /**
     * \brief Contains offset information to reach a specific location in memory, to get around ASLR
     */
    namespace offsets {
        extern PointerChain player;
    }
}
