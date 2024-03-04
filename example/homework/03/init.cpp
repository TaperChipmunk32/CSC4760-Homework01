#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
using namespace std;

// Declare a 5 ∗ 7 ∗ 12 ∗ n View

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
    // Make View
    int n = 10;
    Kokkos::View<int****> view("The View", 5, 7, 12, n);

    // print name
    cout << "View name: " << view.label() << endl;
  }
  Kokkos::finalize();
}
