#pragma once
#include <cstdint>
#include <cstddef>

namespace murmur2 {
    using hash_t = std::uint32_t;

    inline constexpr std::uint32_t kSeed = 0x31415926u;

#define _tolower_u(c) (std::uint32_t)(((c) >= 'A' && (c) <= 'Z') ? (c) + 32 : (c))

    template <bool LowerCase = true, std::size_t N>
    [[nodiscard]] consteval hash_t hash_a1_const(const char (&text)[N], std::uint32_t seed) {
        constexpr std::uint32_t m = 0x5BD1E995u;
        constexpr int r = 24;

        std::uint32_t h = seed ^ (N - 1);
        std::size_t i = 0;

        while (i + 4 <= N - 1) {
            std::uint32_t k;
            if constexpr (LowerCase) {
                k = _tolower_u(text[i])
                  | (_tolower_u(text[i + 1]) << 8)
                  | (_tolower_u(text[i + 2]) << 16)
                  | (_tolower_u(text[i + 3]) << 24);
            } else {
                k = (std::uint32_t)text[i]
                  | ((std::uint32_t)text[i + 1] << 8)
                  | ((std::uint32_t)text[i + 2] << 16)
                  | ((std::uint32_t)text[i + 3] << 24);
            }
            k *= m; k ^= k >> r; k *= m;
            h *= m; h ^= k;
            i += 4;
        }

        if constexpr (LowerCase) {
            switch ((N - 1) - i) {
                case 3: h ^= _tolower_u(text[i + 2]) << 16; [[fallthrough]];
                case 2: h ^= _tolower_u(text[i + 1]) << 8;  [[fallthrough]];
                case 1: h ^= _tolower_u(text[i]); h *= m;
            }
        } else {
            switch ((N - 1) - i) {
                case 3: h ^= (std::uint32_t)text[i + 2] << 16; [[fallthrough]];
                case 2: h ^= (std::uint32_t)text[i + 1] << 8;  [[fallthrough]];
                case 1: h ^= (std::uint32_t)text[i]; h *= m;
            }
        }

        h ^= h >> 13;
        h *= m;
        h ^= h >> 15;
        return h;
    }

#undef _tolower_u
}
