#pragma once


bool PointerIsValid(const void* ptr);
std::optional<std::uint32_t> TraverseChain(std::uint32_t start_point, const std::vector<std::uint32_t>& ptr_chain);

