#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
using namespace std;
// Do simple parallel reduce to output the maximum element in a View

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
    // Make View and create values
    Kokkos::View<int*> values("values", 10);
    for (int i = 0; i < 10; i++) {
      values(i) = i;
    }
  
    // Do a parallel reduction
    int max_value = values(0);
    Kokkos::parallel_reduce("Max Reduction", 10, KOKKOS_LAMBDA(int i, int& local_max) {
      local_max = Kokkos::max(local_max, values(i));
    }, Kokkos::Max<int>(max_value));
  
    // Output the maximum element
    cout << "Max element: " << max_value << endl;
  }
  Kokkos::finalize();
}
