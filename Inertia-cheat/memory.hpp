#pragma once

/**
 * \brief Traverses a chain of pointers to find the final point
 * \param start_point Address to begin traversal
 * \param ptr_chain Chain of pointers to resolve final address of
 * \return Address the chain leads to on success, or std::nullopt on failure
 */
std::optional<std::uint32_t> TraverseChain(std::uint32_t start_point, const std::vector<std::uint32_t>& ptr_chain);
