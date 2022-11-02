# RegularNumGen
================================
A few functions for generating the Nth regular number


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
 However, geometric reasoning let's us compute
 deep into the series while only calculating a small
 fraction of the series.
 
 The functions contained here will calculate the Nth 
 regular number. In order from slowest to fastest:
 get_regular_factor(N)
 get_regular_set(N)
 get_regular_log_set(N)
 get_regular_compact(N)
 get_regular_divide_conquer(N)
 get_regular_fast_geometric(N)
