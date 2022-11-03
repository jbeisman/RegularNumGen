#pragma once

#include <array>
#include <utility>

 int get_regular_factor(size_t N);
 unsigned long long get_regular_set(size_t N);
 double get_regular_log_set(size_t N);
 double get_regular_compact(size_t N);
 std::pair<double, std::array<size_t, 3>> get_regular_divide_conquer(size_t N);
 std::pair<double, std::array<size_t, 3>> get_regular_fast_geometric(size_t N);
