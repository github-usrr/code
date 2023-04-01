#pragma once

template <typename... Args>
constexpr inline auto sum(Args &&...args)  { return (args + ...); }