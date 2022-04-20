// ReSharper disable CppClangTidyPerformanceNoIntToPtr
#include "pch.hpp"
#include "player.hpp"
#include "data.hpp"

using namespace data; // For offset data


/**
 * \brief Try to get main Player object
 * \return Populated Player object on success, std::nullopt on failure
 */
std::optional<Player> GetPlayer() {
    auto start_point = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("UnityPlayer.dll"));
    start_point += offsets::player.start_point;

    // Get a pointer to health
    const auto health_ptr = TraverseChain(start_point, offsets::player.ptr_chain).value_or(0u);

    if (!health_ptr)
        return std::nullopt;
    
    const auto ammo_ptr = health_ptr - 0x4;

    const Player player{
        .health = reinterpret_cast<std::int32_t*>(health_ptr),
        .ammo = reinterpret_cast<std::int32_t*>(ammo_ptr)
    };

    return player;
}
