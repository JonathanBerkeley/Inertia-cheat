#pragma once
#include "memory.hpp"


/**
 * \brief Represents a player object in Inertia
 */
struct Player {
    std::int32_t* health{};
    std::int32_t* ammo{};
};

std::optional<Player> GetPlayer();
