#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
    int n = 10;

    Kokkos::View<int*> input("input", n);
    Kokkos::View<double**> output("output", n, 2);
    for(int i = 0; i < 10; i++) {
      cout << "Iteration " << i << endl;
      Kokkos::parallel_for("init", n, KOKKOS_LAMBDA(const int i) {
        input(i) = i + 1;
      });

      Kokkos::parallel_scan("prefix_sum", n, KOKKOS_LAMBDA(const int i, int& sum, bool final) {
        Kokkos::Timer timer;
        sum += input(i);
        if (final) {
          output(i, 0) = sum;
          output(i, 1) = timer.seconds();
        }
      });
      
      Kokkos::fence();
      
      cout << "Partial sums:" << endl;
      for(int i = 0; i < n; i++) {
        cout << output(i, 0) << " (time: " << output(i, 1) << " seconds)" << endl;
      }
    }
  }
  Kokkos::finalize();
}
