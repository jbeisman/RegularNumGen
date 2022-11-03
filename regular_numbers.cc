#include <vector>
#include <array>
#include <set>
#include <utility>
#include <cmath>
#include <iostream>
#include <numeric>
#include "regular_numbers.hh"

/*
 This file contains several functions for calculating
 the Nth regular number.

 Regular numbers, also known as ugly numbers, Hamming
 numbers, and 5-smooth numbers, are numbers whose only
 prime divisors are 2, 3, and 5.

 They are described by
 2^i * 3^j * 5^k
 for non-negative i,j,k

 The first 15 regular numbers are
 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20, 24

 While that might make it look like regular numbers are
 densely distributed, they are not. After around 60, the
 ratio of regular numbers to non-regular (normal? irregular?)
 numbers decreases precipitously, and they are very sparse
 among larger integers.

 Because they are dependent on the distribution of primes,
 regular numbers are randomly distributed throughout
 number space, and cannot be predicted analytically.
 However, advanced geometric reasoning let's us compute
 deep into the series while only calculating a small
 fraction of the series.

 INCLUDES:
 get_regular_factor()
 get_regular_set()
 get_regular_log_set()
 get_regular_compact()
 get_regular_divide_conquer()
 get_regular_fast_geometric()
*/

// GLOBALS
const double lb3{std::log2(3.0)};
const double lb5{std::log2(5.0)};

// HELPER FUNCTIONS
double coef2log2(const std::array<size_t, 3>& arr) {
  return arr[0] + arr[1]*lb3 + arr[2]*lb5;
}

int factor(int val) {
  while (val % 2 == 0) { val /= 2; }
  while (val % 3 == 0) { val /= 3; }
  while (val % 5 == 0) { val /= 5; }
  return val;
}




// FUNCTIONS TO CALCULATE NTH REGULAR NUMBER

// simplest method to calculate Nth regular number
int get_regular_factor(const size_t n_series)
{
  // stop
  if (n_series > 1500) {
    std::cout << "Run with n <= 1500 or computer will be too hot.\n";
    return 0;
  }
  std::vector<int> series;
  series.push_back(1);
  int num{2};
  while (series.size() < n_series) {
    int n{num};
    int remainder = factor(n);
    if (remainder == 1) {
      series.push_back(num);
    }
    ++num;
  }
  // return last value placed into series
  return series.back();
}



// this method uses std::set to sort the series and filter duplicates
// start at an initial value (1) and multiply it by 2,3,5
// to create new values at every step
unsigned long long get_regular_set(size_t n) {
  
  // use std::set to filter duplicates and sort entries
  std::set<unsigned long long> series;
  series.insert(1);
  while (n != 1) {
    const auto smallest = *series.begin();
    series.erase(series.begin());
    series.insert(smallest*2);
    series.insert(smallest*3);
    series.insert(smallest*5);
    --n;
  }
  return *series.begin();
}



// this is similar to the previous method, but uses log2 values
double get_regular_log_set(size_t n)
{
  // custom compare function for FP values
  const auto cmp = [] (const auto n1, const auto n2) { 
    return (n2 - n1) > (1.0e-15 * n1);
  };

  std::set<double, decltype(cmp)> log_series(cmp);
  log_series.insert(0.0); // insert first value

  while (n != 1) {
    const auto smallest = *log_series.begin();
    log_series.erase(log_series.begin());
    log_series.insert(smallest + 1.0);
    log_series.insert(smallest + lb3);
    log_series.insert(smallest + lb5);
    --n;
  }
  return *log_series.begin();
}



// this is an improved method that uses a compact algorithm
// compared to other methods with similar or better performance
// single loop over N that launches an iteration over 2, 3, 5
// when a candidate leaves the queue
double get_regular_compact(size_t n)
{
  std::array<const double, 3> lg2{1.0, lb3, lb5};
  std::array<double, 3> candidates{1.0, lb3, lb5};
  std::array<int, 3> series_idx{0, 0, 0};
  std::vector<double> series;
  series.reserve(65536);
  size_t vec_cnt = 0;
  while (n != 1) {
    // manage memory
    if ((series.capacity()/2) < vec_cnt) {
      const auto min_i = *std::min_element(series_idx.begin(), series_idx.end());
      for (auto& el : series_idx) el -= min_i;
      series.erase(series.begin(), series.begin() + min_i);
      vec_cnt = 0;
    }
    // push minimum candidate into series and calculate new products of the pushed value  
    series.push_back(*std::min_element(candidates.begin(), candidates.end()));
    const auto current = series.back();
    for (int i = 0; i < 3; ++i) {
      if (std::abs(candidates[i] - current) < current * 1.0e-15) {
        // replace candidate if this value just went into series
        candidates[i] = series[series_idx[i]++] + lg2[i];
      }
    }
    vec_cnt++;
    n--;
  }
  return series.back();
}



// this algorithm uses a binary divide and conquer
// approach to minimize the number of operations 
// that must be performed to calculate series
std::pair<double, std::array<size_t, 3>>
get_regular_divide_conquer(size_t n)
{
  // containers to store problem state and series
  std::array<size_t, 3> coef_ijk{1,0,0};
  std::array<size_t, 3> coef_jk{0,2,0};
  std::array<size_t, 3> coef_k{0,0,1};
  std::array<size_t, 3> coef_minjk{0,1,0};
  std::vector<std::array<size_t, 3>> series;
  std::vector<std::array<size_t, 3>> jk_series;

  series.reserve(65536);
  jk_series.reserve(65536);
  // initial values of series in log2-space
  double log_ijk = 1.0;
  double log_jk = 2.0 * lb3;
  double log_k = lb5;
  double min_jk = lb3;

  size_t ii = 0, jj = 0;
  while (n != 1) {
    if ((series.capacity()/2) < ii) {
      series.erase(series.begin(), series.begin() + ii); ii = 0;
    }
    
    if (log_ijk < min_jk) {
      series.push_back(coef_ijk);
      coef_ijk = series[ii++];
      coef_ijk[0]++;
      log_ijk = coef2log2(coef_ijk);
    } else {
      series.push_back(coef_minjk);
      if (log_jk < log_k) {
        coef_minjk = coef_jk;
        coef_jk = jk_series[jj++];
        coef_jk[1]++;
        log_jk = coef2log2(coef_jk);
      } else {
        coef_minjk = coef_k;
        coef_k[2]++;
        log_k = coef2log2(coef_k);
      }
      if ((jk_series.capacity()/2) < jj) {
        jk_series.erase(jk_series.begin(), jk_series.begin() + jj); jj = 0;
      }
      jk_series.push_back(coef_minjk);
      min_jk = coef2log2(coef_minjk);
    }
    --n;
  } // end while
  return std::make_pair(coef2log2(series.back()), series.back());
}


/*
 this algorithm takes advantage of a formula that provides a finite limit
 on how many N exist beneath a given threshold

 Formula is:

       (log2( N * 30^0.5))^3
 n =  -----------------   
       6 log2(3) log2(5)

 where n indicates the nth position in the series
 and N is the threshold the nth series member must exist beneath

 we can solve this for N to obtain an estimate of the nth member's value

 log2(N) = estimated value ~= (n * 6 * lg2(3) * log2(5))^1/3 - log2(30^0.5)

 It has been reported that it is adequate to set the error bounds as:
 estimated value +- (1 / estimated value)
*/
std::pair<double, std::array<size_t, 3>>
get_regular_fast_geometric(const size_t n)
{
  // check for n too small
  if (n < 1) {
    std::cout << "Error: N must be an integer > 0\n";
    return std::make_pair<double,std::array<size_t, 3>>(-1.0, {0,0,0});
  }
  if (n < 2) {
    std::cout << "Special inclusion of 1 as first member of series\n";
    return std::make_pair<double,std::array<size_t, 3>>(0.0, {0,0,0});
  }
  if (n < 3) {
    return std::make_pair<double,std::array<size_t, 3>>(1.0, {1,0,0});
  }

  const double numerator = std::pow((6.0 * lb3 * lb5 * n), 1.0/3.0);
  const double denominator = std::log2(std::sqrt(30.0));
  const double estval = numerator - denominator;
  const double high = estval + 1.0 / estval;
  const double low = 2.0 * estval - high;

  size_t count{0};
  std::vector<double> series;
  std::vector<std::array<size_t, 3>> coeffs;
  const size_t kmax = static_cast<size_t>(high / lb5) + 1;
  for (size_t k = 0; k < kmax; k++) {
    const double fives = lb5 * k;
    const size_t jmax = static_cast<size_t>((high - fives) / lb3) + 1;
    for (size_t j = 0; j < jmax; j++) {
      const double threes = fives + static_cast<double>(j) * lb3;
      const double twos = high - threes;
      const double candidate = threes + std::floor(twos);
      count += static_cast<size_t>(twos) + 1;
      if (candidate >= low) {
        series.push_back(candidate);
        coeffs.push_back({static_cast<size_t>(twos), j, k});
      }
    }
  }

  // ensure value came from within search band
  if (n > count) {
   std::cout << "Error: high estimate needs to be higher\n";
   std::array<size_t, 3> out = {0, 0, 0};
   return std::make_pair(0.0, out);
  }

  // target index of solution when sorted in descending order
  const size_t target = static_cast<int>(count - n);
  if (target >= series.size()) {
    std::cout << "Error: low estimate needs to be lower\n";
    std::array<size_t, 3> out = {0, 0, 0};
    return std::make_pair(0.0, out);
  }

  // the data need to be sorted
  // use sort_idx to get index of series
  std::vector<size_t> sort_idx(series.size());
  std::iota(sort_idx.begin(), sort_idx.end(), 0);
  std::sort(sort_idx.begin(), sort_idx.end(),
    [&series] (const auto i1, const auto i2) {return series[i1] > series[i2];});

  return std::make_pair(series[sort_idx[target]], coeffs[sort_idx[target]]);
}

