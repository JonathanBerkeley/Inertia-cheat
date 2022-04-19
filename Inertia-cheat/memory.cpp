// ReSharper disable CppClangTidyPerformanceNoIntToPtr
#include "pch.hpp"
#include "memory.hpp"


/**
 * \brief Check if a pointer is valid
 *
 * Adapted from: https://guidedhacking.com/threads/testing-if-pointer-is-invalid.13222/#post-77709
 * \param ptr Pointer to check
 * \return True if pointer is valid
 */
bool PointerIsValid(const void* ptr) {
    MEMORY_BASIC_INFORMATION mbi{};

    if (VirtualQuery(ptr, &mbi, sizeof mbi)) {
        constexpr auto mask = PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
        bool protect = mbi.Protect & mask;

        if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
            protect = false;

        return protect;
    }

    return false;
}


/**
 * \brief Traverses a chain of pointers to find the final point
 * \param start_point Address to begin traversal
 * \param ptr_chain Chain of pointers to resolve final address of
 * \return Address the chain leads to on success, or std::nullopt on failure
 */
std::optional<std::uint32_t> TraverseChain(std::uint32_t start_point, const std::vector<std::uint32_t>& ptr_chain) {
    
    for (const auto offset : ptr_chain) {

        const auto ptr = reinterpret_cast<uintptr_t*>(start_point);

        if (!PointerIsValid(ptr))
            return std::nullopt;

        start_point = *ptr;

        if (!start_point)
            return std::nullopt;

        start_point += offset;
    }

    return start_point;
}
