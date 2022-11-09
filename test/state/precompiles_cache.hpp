// evmone: Fast Ethereum Virtual Machine implementation
// Copyright 2022 The evmone Authors.
// SPDX-License-Identifier: Apache-2.0

#include <evmc/evmc.hpp>
#include <array>
#include <cstdint>
#include <optional>
#include <unordered_map>

namespace evmone::state
{
using evmc::bytes;
using evmc::bytes_view;

class Cache
{
    static constexpr std::size_t NumPrecompiles = 10;

    std::array<std::unordered_map<uint64_t, std::optional<bytes>>, NumPrecompiles> m_cache;

public:
    Cache() noexcept;
    ~Cache() noexcept;

    /// Lookups the precompiles cache.
    ///
    /// @param id        The precompile ID.
    /// @param input     The input for precompile execution.
    /// @param gas_left  The amount of gas left _after_ execution,
    ///                  used for constructing the result for successful execution.
    /// @return          The cached execution result
    ///                  or std::nullopt if the matching cache entry is not found.
    std::optional<evmc::Result> find(uint8_t id, bytes_view input, int64_t gas_left) const;

    /// Inserts new precompiles cache entry.
    void insert(uint8_t id, bytes_view input, const evmc::Result& result);
};
}  // namespace evmone::state
