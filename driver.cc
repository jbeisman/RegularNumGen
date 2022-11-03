
#include <array>
#include <utility>
#include <iostream>
#include <iomanip>
#include "regular_numbers.hh"

template <typename F>
auto test_wrapper(F&& function, size_t n)
{
  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  auto ans = function(n);
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
  std::chrono::duration<double> time_span = 
    std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  return std::make_pair(ans, time_span.count());
}

int main() {

  size_t n=1, x=-99;
  bool EXIT = false;

  while(!EXIT) {
    std::cout <<  "Functions to calculate the Nth regular number.\n";
    std::cout <<  "Please enter an integer greater than 0 to use as N:\n";
    std::cin >> n; // user input

    std::cout <<  "Please choose from the following functions to calculate the Nth regular number:\n" <<
                  "Press 1 -- get_regular_factor()\n" <<
                  "      2 -- get_regular_set()\n" <<
                  "      3 -- get_regular_log_set()\n" <<
                  "      4 -- get_regular_compact()\n" <<
                  "      5 -- get_regular_divide_conquer()\n" << 
                  "      6 -- get_regular_fast_geometric()\n" << 
                  "-OR-\n" <<
                  "      7 -- run all options\n" << 
                  "      any other key to quit\n\n";
    std::cin >> x; // user input

    bool RUN_ALL = (x == 7) ? true : false;
    EXIT = (x < 1 || x > 7) ? true : false;


    if (x == 1 || RUN_ALL) {
      std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"
                << "Running get_regular_factor(N) with N = "<< n <<".\n\n";
      size_t N = n;
      const auto func = [] (size_t N) { return get_regular_factor(N); };
      const auto [ans, time] = test_wrapper(func, N);
      std::cout << "Nth number:  " << ans << "\n";
      std::cout << "run time: " << time << " seconds.\n\n" << std::endl;
    }

    if (x == 2 || RUN_ALL) {
      std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"
                << "Running get_regular_set(N) with N = "<< n <<".\n\n";
      size_t N = n;
      const auto func = [] (size_t N) { return get_regular_set(N); };
      const auto [ans, time] = test_wrapper(func, N);
      std::cout << "Nth number:  " << ans << "\n";
      std::cout << "run time: " << time << " seconds.\n\n" << std::endl;
    }

    if (x == 3 || RUN_ALL) {
      std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"
                << "Running get_regular_log_set(N) with N = "<< n <<".\n\n";
      size_t N = n;
      const auto func = [] (size_t N) { return get_regular_log_set(N); };
      const auto [ans, time] = test_wrapper(func, N);
      std::cout << std::setprecision(15) << "log2 of Nth number:  " << ans << "\n";
      std::cout << "run time: " << time << " seconds.\n\n" << std::endl;
    }

    if (x == 4 || RUN_ALL) {
      std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"
                << "Running get_regular_compact(N) with N = "<< n <<".\n\n";
      size_t N = n;
      const auto func = [] (size_t N) { return get_regular_compact(N); };
      const auto [ans, time] = test_wrapper(func, N);
      std::cout << std::setprecision(15) << "log2 of Nth number:  " << ans << "\n";
      std::cout << "run time: " << time << " seconds.\n\n" << std::endl;
    }

    if (x == 5 || RUN_ALL) {
      std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"
                << "Running get_regular_divide_conquer(N) with N = "<< n <<".\n\n";
      size_t N = n;
      const auto func = [] (size_t N) { return get_regular_divide_conquer(N); };
      const auto [ans, time] = test_wrapper(func, N);
      const auto coeff = ans.second;
      std::cout << "powers of Nth number:  " << coeff[0] << "  " << coeff[1] << "  " << coeff[2] << "\n";
      std::cout << "log2 of Nth number:  " << std::setprecision(15) << ans.first << "\n";
      std::cout << "run time: " << time << " seconds.\n\n" << std::endl;
    }

    if (x == 6 || RUN_ALL) {
      std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"
                << "Running get_regular_fast_geometric(N) with N = "<< n <<".\n\n";
      size_t N = n;
      const auto func = [] (size_t N) { return get_regular_fast_geometric(N); };
      const auto [ans, time] = test_wrapper(func, N);
      const auto coeff = ans.second;
      std::cout << "powers of Nth number:  " << coeff[0] << "  " << coeff[1] << "  " << coeff[2] << "\n";
      std::cout << "log2 of Nth number:  " << std::setprecision(15) << ans.first << "\n";
      std::cout << "run time: " << time << " seconds.\n\n" << std::endl;
    }
  }
  return 0;
}
