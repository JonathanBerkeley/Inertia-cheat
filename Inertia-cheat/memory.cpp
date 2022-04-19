// ReSharper disable CppClangTidyPerformanceNoIntToPtr
#include "pch.hpp"
#include "memory.hpp"

std::optional<std::uint32_t> TraverseChain(std::uint32_t start_point, const std::vector<std::uint32_t>& ptr_chain) {
    
    for (const auto offset : ptr_chain) {
        start_point = *reinterpret_cast<uintptr_t*>(start_point);

        if (!start_point) return std::nullopt;

        start_point += offset;
    }

    return start_point;
}
