#include "pch.hpp"
#include "data.hpp"


namespace data {

    namespace proc {
        // Windows
        HMODULE self_module = nullptr;
    }

    namespace offsets {
        PointerChain player = {
            .start_point = 0x13A1340,
            .ptr_chain { 0xC2C, 0xDC8, 0xEA8, 0x18, 0x38 }
        };
    }
}
