#ifndef CPP_TETRIS_UTILS_H
#define CPP_TETRIS_UTILS_H

#include <type_traits>

template <typename E>
constexpr auto to_underlying(E e) noexcept
{
    return static_cast<std::underlying_type_t<E>>(e);
}

#endif CPP_TETRIS_UTILS_H